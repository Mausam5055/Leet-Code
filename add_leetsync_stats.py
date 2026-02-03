"""
LeetSync Stats Updater
This script adds timing and memory statistics to README.md files in all problem folders.

Usage:
1. Default mode - adds placeholder stats to all folders:
   python add_leetsync_stats.py

2. With stats file - reads stats from a JSON file:
   python add_leetsync_stats.py --stats stats.json

Stats file format (stats.json):
{
    "152-maximum-product-subarray": {
        "time": "3",
        "time_percent": "96.57",
        "memory": "42.5",
        "memory_percent": "62.53"
    },
    ...
}
"""

import os
import re
import json
import argparse
import subprocess

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
    # 1. Add the folder
    success, _, err = run_command(f'git add "{folder_path}"')
    if not success:
        print(f"    ⚠ Git add failed: {err.strip()}")
        return False

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
            print(f"    ⚠ Git commit failed: {err.strip()}")
        return False

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
        with open(desktop_ini_path, 'w', encoding='utf-8') as f:
            f.write('[.ShellClassInfo]\n')
            f.write(f'InfoTip={description}\n')
        
        # Set hidden and system attributes
        os.system(f'attrib +h +s "{desktop_ini_path}" >nul 2>&1')
        os.system(f'attrib +r "{folder_path}" >nul 2>&1')
        
        return True
    except Exception as e:
        print(f"  ⚠ Could not create desktop.ini: {e}")
        return False

def process_folders(stats_dict=None, use_placeholder=True, do_commit=False):
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
    folders = [item for item in items if os.path.isdir(item) and re.match(r'^\d+', item)]
    folders.sort(key=lambda x: int(re.match(r'^(\d+)', x).group(1)))
    
    for folder in folders:
        folder_path = os.path.join(current_dir, folder)
        
        print(f"📁 {folder}")
        
        # Get stats for this folder
        if stats_dict and folder in stats_dict:
            stats = stats_dict[folder]
            time_ms = stats.get('time', 'N/A')
            time_percent = stats.get('time_percent', 'N/A')
            memory_mb = stats.get('memory', 'N/A')
            memory_percent = stats.get('memory_percent', 'N/A')
        elif use_placeholder:
            # Use placeholder values
            time_ms = "X"
            time_percent = "XX.XX"
            memory_mb = "XX.X"
            memory_percent = "XX.XX"
        else:
            print(f"  ⚠ No stats available for {folder}, skipping")
            skipped_count += 1
            print()
            continue
        
        # Create description string
        description = f"Time: {time_ms} ms ({time_percent}%) | Memory: {memory_mb} MB ({memory_percent}%) - LeetSync"
        
        # Update README.md
        readme_path = os.path.join(folder_path, 'README.md')
        if update_readme_with_stats(readme_path, time_ms, time_percent, memory_mb, memory_percent):
            print(f"  ✓ Updated README.md")
            print(f"    {description}")
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
        help='Use placeholder values (default: True)'
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
    
    args = parser.parse_args()
    
    print("\n" + "="*70)
    print(" "*20 + "LeetSync Stats Updater")
    print("="*70)
    
    if args.create_sample:
        create_sample_stats_file()
        return
    
    stats_dict = None
    if args.stats:
        try:
            with open(args.stats, 'r', encoding='utf-8') as f:
                stats_dict = json.load(f)
            print(f"\n✓ Loaded {len(stats_dict)} folder stats from '{args.stats}'")
        except FileNotFoundError:
            print(f"\n✗ Error: Stats file '{args.stats}' not found!")
            return
        except json.JSONDecodeError as e:
            print(f"\n✗ Error: Invalid JSON in stats file: {e}")
            return
    
    if not stats_dict and not args.placeholder:
        print("\n⚠ No stats file provided and placeholder mode disabled.")
        print("  Use --stats <file> or enable --placeholder")
        return
    
    print("\nThis script will:")
    print("  1. Update README.md files with LeetSync stats header")
    print("  2. Create desktop.ini files for folder tooltips (Windows)")
    if args.commit:
        print("  3. git add & commit each folder with stats message")
    
    if stats_dict:
        print(f"  Using stats from '{args.stats}'")
    else:
        print("  Using placeholder values (you can manually update later)")
    
    response = input("\n❓ Continue? (y/n): ").strip().lower()
    if response == 'y':
        process_folders(stats_dict, args.placeholder, args.commit)
        print("✅ Done!\n")
    else:
        print("\n❌ Aborted.\n")

if __name__ == "__main__":
    main()
