import os
import re
import json
import argparse
import subprocess
import time
import urllib.request
import urllib.error
import sys

# Constants
BASE_URL = "https://leetcode.com"
GRAPHQL_URL = "https://leetcode.com/graphql"

def run_command(command, cwd=None):
    """Run a shell command."""
    try:
        result = subprocess.run(
            command, 
            cwd=cwd, 
            shell=True, 
            capture_output=True, 
            text=True
        )
        return result.returncode == 0, result.stdout, result.stderr
    except Exception as e:
        return False, "", str(e)

def git_commit_folder(folder_path, message):
    """
    Stage and commit a specific folder with the given message.
    """
    # 1. Add specific files (more robust than adding folder)
    files_to_add = ["README.md", "desktop.ini"]
    added_something = False
    
    for filename in files_to_add:
        file_path = os.path.join(folder_path, filename)
        if os.path.exists(file_path):
            # Use relative path for git add to avoid path separator issues
            # Git on Windows prefers relative paths or forward slashes
            try:
                rel_path = os.path.relpath(file_path, os.getcwd())
            except ValueError:
                rel_path = file_path # Fallback if on different drive
                
            success, out, err = run_command(f'git add "{rel_path}"')
            if not success:
               print(f"    ⚠ Git add failed for {filename}: {err.strip()} {out.strip()}")
            else:
               added_something = True

    # Also add the solution file if possible (heuristic)
    # We can just try 'git add folder' as a fallback/catch-all
    try:
        rel_folder = os.path.relpath(folder_path, os.getcwd())
    except ValueError:
        rel_folder = folder_path

    success, out, err = run_command(f'git add "{rel_folder}"')
    
    # 2. Commit with message
    # escape double quotes in message just in case
    safe_message = message.replace('"', '\\"')
    success, out, err = run_command(f'git commit -m "{safe_message}"')
    
    if success:
        return True
    else:
        if "nothing to commit" in out or "nothing to commit" in err:
            print("    ○ Nothing to commit")
        else:
            print(f"    ⚠ Git commit failed: OUT=[{out.strip()}] ERR=[{err.strip()}]")
        return False

def git_push():
    """
    Push changes to remote repository.
    """
    print("\n⬆ Pushing changes to remote...")
    success, out, err = run_command('git push')
    
    if success:
        print("  ✓ Push successful")
        return True
    else:
        print(f"  ✗ Push failed: {err.strip()}")
        return False

def get_headers(leetcode_session, csrf_token):
    return {
        "Cookie": f"LEETCODE_SESSION={leetcode_session}; csrftoken={csrf_token}",
        "X-CSRFToken": csrf_token,
        "Referer": BASE_URL,
        "Content-Type": "application/json",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
    }

def make_request(url, method="GET", headers=None, data=None):
    if data:
        data = json.dumps(data).encode("utf-8")
    
    req = urllib.request.Request(url, data=data, headers=headers, method=method)
    try:
        with urllib.request.urlopen(req) as response:
            return json.loads(response.read().decode("utf-8"))
    except urllib.error.HTTPError as e:
        print(f"Error making request to {url}: {e}")
        try:
            print(f"Response body: {e.read().decode('utf-8')}")
        except:
            pass
        return None

def get_all_problems(headers):
    print("Fetching list of all problems...")
    url = f"{BASE_URL}/api/problems/all/"
    data = make_request(url, headers=headers)
    if not data:
        print("Failed to fetch problems list. Check your cookies.")
        return []
    
    solved_problems = []
    for stat in data["stat_status_pairs"]:
        if stat["status"] == "ac":
            solved_problems.append({
                "id": stat["stat"]["frontend_question_id"],
                "slug": stat["stat"]["question__title_slug"],
                "title": stat["stat"]["question__title"]
            })
    
    return solved_problems

def get_latest_submission(headers, slug):
    query = """
    query Submissions($offset: Int!, $limit: Int!, $questionSlug: String!) {
        submissionList(offset: $offset, limit: $limit, questionSlug: $questionSlug) {
            submissions {
                id
                statusDisplay
                lang
                timestamp
            }
        }
    }
    """
    data = make_request(
        GRAPHQL_URL, 
        method="POST", 
        headers=headers, 
        data={"query": query, "variables": {"offset": 0, "limit": 20, "questionSlug": slug}}
    )
    
    if data and "data" in data and "submissionList" in data["data"]:
        submissions = data["data"]["submissionList"]["submissions"]
        for sub in submissions:
            if sub["statusDisplay"] == "Accepted":
                return sub
    return None

def get_submission_details(headers, submission_id):
    query = """
    query submissionDetails($submissionId: Int!) {
        submissionDetails(submissionId: $submissionId) {
            runtime
            runtimeDisplay
            runtimePercentile
            memory
            memoryDisplay
            memoryPercentile
        }
    }
    """
    data = make_request(
        GRAPHQL_URL, 
        method="POST", 
        headers=headers, 
        data={"query": query, "variables": {"submissionId": submission_id}}
    )
    if data and "data" in data and "submissionDetails" in data["data"]:
        return data["data"]["submissionDetails"]
    return None

def update_readme_with_stats(readme_path, time_ms, time_percent, memory_mb, memory_percent):
    """
    Update or create README.md with LeetSync stats at the top.
    """
    stats_line = f"Time: {time_ms} ms ({time_percent}%) | Memory: {memory_mb} MB ({memory_percent}%) - LeetSync\n\n"
    
    try:
        # Read existing README if it exists
        existing_content = ""
        if os.path.exists(readme_path):
            with open(readme_path, 'r', encoding='utf-8') as f:
                existing_content = f.read()
            
            # Remove old LeetSync line if present
            existing_content = re.sub(
                r'^Time:.*?-\s*LeetSync\s*\n+',
                '',
                existing_content,
                flags=re.MULTILINE
            )
        
        # Write new content with stats at the top
        with open(readme_path, 'w', encoding='utf-8') as f:
            f.write(stats_line)
            if existing_content:
                f.write(existing_content)
        
        return True
    except Exception as e:
        print(f"  ✗ Error updating README: {e}")
        return False

def create_desktop_ini(folder_path, description):
    """
    Create a desktop.ini file to set folder tooltip in Windows Explorer.
    """
    desktop_ini_path = os.path.join(folder_path, 'desktop.ini')
    
    try:
        # Check if file exists and try to make it writable first if needed
        if os.path.exists(desktop_ini_path):
             os.system(f'attrib -h -s "{desktop_ini_path}" >nul 2>&1')
        
        with open(desktop_ini_path, 'w', encoding='utf-8') as f:
            f.write('[.ShellClassInfo]\n')
            f.write(f'InfoTip={description}\n')
        
        # Set hidden and system attributes
        os.system(f'attrib +h +s "{desktop_ini_path}" >nul 2>&1')
        os.system(f'attrib +r "{folder_path}" >nul 2>&1')
        
        return True
    except Exception as e:
        # Silently fail for permission errors as this is optional candy
        # print(f"  ⚠ Could not create desktop.ini: {e}")
        return False

def process_folders(stats_dict=None, use_placeholder=True, do_commit=False, headers=None, solved_map=None):
    """
    Process all problem folders and update them with stats.
    """
    current_dir = os.getcwd()
    print(f"\nProcessing folders in: {current_dir}\n")
    print("="*70)
    
    updated_count = 0
    committed_count = 0
    skipped_count = 0
    
    # Get all directories
    items = os.listdir(current_dir)
    # Filter for problem folders (starting with digits)
    folders = [item for item in items if os.path.isdir(item) and re.match(r'^\d+', item)]
    # Sort numerically
    folders.sort(key=lambda x: int(re.match(r'^(\d+)', x).group(1)))
    
    for folder in folders:
        folder_path = os.path.join(current_dir, folder)
        
        # Extract ID and Slug from folder name
        match = re.match(r'^(\d+)-(.*)$', folder)
        if not match:
            continue
            
        prob_id = match.group(1)
        prob_slug = match.group(2)
        
        print(f"📁 {folder}")
        
        time_ms = "X"
        time_percent = "XX.XX"
        memory_mb = "XX.X"
        memory_percent = "XX.XX"
        
        has_stats = False

        # 1. Try to get stats from API if headers provided
        if headers and solved_map:
            # Check if this problem is in solved list
            # The folder slug might not exactly match the API slug, but usually close.
            # We can try to match by ID if possible, but solved_map from get_all_problems matches ID.
            
            # solved_map keys should be string ID
            if prob_id in solved_map:
                api_slug = solved_map[prob_id]['slug']
                
                # Fetch latest submission
                try:
                    # Rate limit slightly
                    time.sleep(1.0) # Increased delay to 1s
                    sub = get_latest_submission(headers, api_slug)
                    if sub:
                        details = get_submission_details(headers, sub['id'])
                        if details:
                            # Parse runtime "3 ms" -> 3
                            curr_time = details.get('runtimeDisplay', '')
                            time_match = re.search(r'(\d+)', curr_time)
                            time_ms = time_match.group(1) if time_match else "0"
                            
                            # Parse percentile
                            time_percent = "{:.2f}".format(details.get('runtimePercentile', 0) or 0)
                            
                            # Parse memory "42.5 MB" -> 42.5
                            curr_mem = details.get('memoryDisplay', '')
                            mem_match = re.search(r'(\d+(?:\.\d+)?)', curr_mem)
                            memory_mb = mem_match.group(1) if mem_match else "0"
                            
                            memory_percent = "{:.2f}".format(details.get('memoryPercentile', 0) or 0)
                            
                            has_stats = True
                            print(f"  ✓ Fetched stats: Time {time_ms}ms ({time_percent}%) | Mem {memory_mb}MB ({memory_percent}%)")
                        else:
                            print(f"  ⚠ No details found for submission {sub['id']}")
                    else:
                        print(f"  ⚠ No accepted submission found for {api_slug}")
                except Exception as e:
                    print(f"  ⚠ API Error for {folder}: {e}")
            else:
                print(f"  ⚠ Problem ID {prob_id} not found in solved list")

        # 2. Fallback to local stats file
        if not has_stats and stats_dict and folder in stats_dict:
            stats = stats_dict[folder]
            time_ms = stats.get('time', 'N/A')
            time_percent = stats.get('time_percent', 'N/A')
            memory_mb = stats.get('memory', 'N/A')
            memory_percent = stats.get('memory_percent', 'N/A')
            has_stats = True
        
        # 3. Fallback to placeholder
        if not has_stats and not use_placeholder and not headers:
            print(f"  ⚠ No stats available, skipping")
            skipped_count += 1
            print()
            continue
        
        # Create description string
        description = f"Time: {time_ms} ms ({time_percent}%) | Memory: {memory_mb} MB ({memory_percent}%) - LeetSync"
        
        # Update README.md
        readme_path = os.path.join(folder_path, 'README.md')
        if update_readme_with_stats(readme_path, time_ms, time_percent, memory_mb, memory_percent):
            print(f"  ✓ Updated README.md")
        else:
            skipped_count += 1
            print()
            continue
        
        # Create desktop.ini for Windows Explorer tooltip
        create_desktop_ini(folder_path, description)
        
        # Git Commit
        if do_commit:
            if git_commit_folder(folder, description):
                print(f"  ✓ Committed changes")
                committed_count += 1
        
        updated_count += 1
        print()
    
    print("="*70)
    print(f"\n📊 Summary:")
    print(f"   ✓ Updated:   {updated_count} folders")
    if do_commit:
        print(f"   ✓ Committed: {committed_count} folders")
    if skipped_count > 0:
        print(f"   ⚠ Skipped:   {skipped_count} folders")
    print(f"   📂 Total:     {updated_count + skipped_count} folders\n")

def create_sample_stats_file():
    """
    Create a sample stats.json file with placeholder data.
    """
    current_dir = os.getcwd()
    items = os.listdir(current_dir)
    folders = [item for item in items if os.path.isdir(item) and re.match(r'^\d+', item)]
    
    sample_stats = {}
    for folder in folders[:5]:  # Just first 5 as examples
        sample_stats[folder] = {
            "time": "X",
            "time_percent": "XX.XX",
            "memory": "XX.X",
            "memory_percent": "XX.XX"
        }
    
    with open('stats_sample.json', 'w', encoding='utf-8') as f:
        json.dump(sample_stats, f, indent=4)
    
    print("\n✓ Created 'stats_sample.json' with sample data.")
    print("  Edit this file with your actual stats, then run:")
    print("  python add_leetsync_stats.py --stats stats_sample.json\n")

def main():
    parser = argparse.ArgumentParser(
        description='Add LeetSync timing and memory statistics to problem folders',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument(
        '--stats',
        type=str,
        help='JSON file containing stats for each folder'
    )
    parser.add_argument(
        '--placeholder',
        action='store_true',
        default=True,
        help='Use placeholder values if stats not found (default: True)'
    )
    parser.add_argument(
        '--create-sample',
        action='store_true',
        help='Create a sample stats.json file'
    )
    parser.add_argument(
        '--commit',
        action='store_true',
        help='Git commit each folder with the stats message'
    )
    parser.add_argument(
        '--push',
        action='store_true',
        help='Git push changes after committing'
    )
    parser.add_argument(
        '--session',
        type=str,
        help='LEETCODE_SESSION cookie'
    )
    parser.add_argument(
        '--csrftoken',
        type=str,
        help='csrftoken cookie'
    )
    
    args = parser.parse_args()
    
    print("\n" + "="*70)
    print(" "*20 + "LeetSync Stats Updater")
    print("="*70)
    
    if args.create_sample:
        create_sample_stats_file()
        return
    
    # 1. Load local stats if provided
    stats_dict = None
    if args.stats:
        try:
            with open(args.stats, 'r', encoding='utf-8') as f:
                stats_dict = json.load(f)
            print(f"\n✓ Loaded {len(stats_dict)} folder stats from '{args.stats}'")
        except Exception as e:
            print(f"\n✗ Error loading stats file: {e}")
            return
    
    # 2. Setup API if cookies provided
    headers = None
    solved_map = None
    
    session = args.session
    csrf = args.csrftoken
    
    # If not provided via args, maybe prompt? Or just skip if not doing interactive
    if not session and not args.stats:
        print("\nInput LeetCode Cookies to fetch real stats (Optional if using --stats file)")
        session = input("Enter LEETCODE_SESSION (press Enter to skip): ").strip()
        if session:
            csrf = input("Enter csrftoken: ").strip()
    
    if session and csrf:
        headers = get_headers(session, csrf)
        print("\nFetching solved problems from LeetCode...")
        solved_list = get_all_problems(headers)
        if solved_list:
            print(f"✓ Found {len(solved_list)} solved problems")
            # Create map by ID for easier lookup
            solved_map = {str(p['id']): p for p in solved_list}
        else:
            print("⚠ Failed to fetch problems or none found.")
            headers = None # Disable API usage
    
    
    if not stats_dict and not headers and not args.placeholder:
        print("\n⚠ No source of stats (file or API) and placeholder disabled.")
        return
    
    print("\nThis script will:")
    print("  1. Update README.md files with LeetSync stats header")
    print("  2. Create desktop.ini files for folder tooltips (Windows)")
    if args.commit:
        print("  3. git add & commit each folder with stats message")
    if args.push:
        print("  4. push changes to remote repository")
    
    print("\nSources:")
    if headers: print("  • LeetCode API (Real-time)")
    if stats_dict: print(f"  • Stats File '{args.stats}'")
    if args.placeholder: print("  • Placeholder values (fallback)")
    
    response = input("\n❓ Continue? (y/n): ").strip().lower()
    if response == 'y':
        process_folders(stats_dict, args.placeholder, args.commit, headers, solved_map)
        
        if args.push:
            git_push()
            
        print("✅ Done!\n")
    else:
        print("\n❌ Aborted.\n")

if __name__ == "__main__":
    main()
