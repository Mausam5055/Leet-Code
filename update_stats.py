import os
import re
import sys

def extract_stats_from_code(file_path):
    """
    Extract runtime and memory statistics from code comments.
    Looks for patterns like:
    - Runtime: 3 ms, faster than 96.57%
    - Memory Usage: 42.5 MB, less than 62.53%
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Pattern to match runtime statistics
        runtime_pattern = r'(?:Runtime|Time):\s*(\d+(?:\.\d+)?)\s*ms.*?(\d+(?:\.\d+)?)%'
        memory_pattern = r'Memory(?:\s+Usage)?:\s*(\d+(?:\.\d+)?)\s*MB.*?(\d+(?:\.\d+)?)%'
        
        runtime_match = re.search(runtime_pattern, content, re.IGNORECASE)
        memory_match = re.search(memory_pattern, content, re.IGNORECASE)
        
        stats = {}
        if runtime_match:
            stats['time'] = runtime_match.group(1)
            stats['time_percent'] = runtime_match.group(2)
        
        if memory_match:
            stats['memory'] = memory_match.group(1)
            stats['memory_percent'] = memory_match.group(2)
        
        return stats
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return {}

def create_desktop_ini(folder_path, description):
    """
    Create a desktop.ini file to set folder description (Windows Explorer tooltip).
    """
    desktop_ini_path = os.path.join(folder_path, 'desktop.ini')
    
    try:
        with open(desktop_ini_path, 'w', encoding='utf-8') as f:
            f.write('[.ShellClassInfo]\n')
            f.write(f'InfoTip={description}\n')
        
        # Set hidden and system attributes on the desktop.ini file
        os.system(f'attrib +h +s "{desktop_ini_path}"')
        
        # Set read-only attribute on the folder (required for desktop.ini to work)
        os.system(f'attrib +r "{folder_path}"')
        
        return True
    except Exception as e:
        print(f"Error creating desktop.ini in {folder_path}: {e}")
        return False

def update_readme_with_stats(readme_path, stats):
    """
    Update or create README.md with stats at the top.
    """
    stats_line = "Time: {} ms ({}%) | Memory: {} MB ({}%) - LeetSync\n\n".format(
        stats.get('time', 'N/A'),
        stats.get('time_percent', 'N/A'),
        stats.get('memory', 'N/A'),
        stats.get('memory_percent', 'N/A')
    )
    
    try:
        # Read existing README if it exists
        existing_content = ""
        if os.path.exists(readme_path):
            with open(readme_path, 'r', encoding='utf-8') as f:
                existing_content = f.read()
            
            # Remove old LeetSync line if present
            existing_content = re.sub(
                r'^Time:.*?LeetSync\s*\n\n?',
                '',
                existing_content,
                flags=re.MULTILINE
            )
        
        # Write new content with stats at the top
        with open(readme_path, 'w', encoding='utf-8') as f:
            f.write(stats_line)
            f.write(existing_content)
        
        return True
    except Exception as e:
        print(f"Error updating README at {readme_path}: {e}")
        return False

def find_solution_file(folder_path):
    """
    Find the solution file in the folder (any code file).
    """
    code_extensions = ['.java', '.py', '.cpp', '.c', '.js', '.ts', '.go', 
                      '.scala', '.kt', '.rs', '.php', '.rb', '.swift', '.cs', '.dart', '.ex']
    
    for file in os.listdir(folder_path):
        file_path = os.path.join(folder_path, file)
        if os.path.isfile(file_path):
            _, ext = os.path.splitext(file)
            if ext.lower() in code_extensions:
                return file_path
    
    return None

def process_all_folders():
    """
    Process all problem folders and update them with stats.
    """
    current_dir = os.getcwd()
    print(f"Processing folders in: {current_dir}\n")
    
    updated_count = 0
    skipped_count = 0
    
    # Get all directories
    items = os.listdir(current_dir)
    folders = [item for item in items if os.path.isdir(item) and not item.startswith('.')]
    
    # Sort folders
    folders.sort()
    
    for folder in folders:
        folder_path = os.path.join(current_dir, folder)
        
        # Skip non-problem folders
        if not re.match(r'^\d+', folder):
            continue
        
        print(f"Processing: {folder}")
        
        # Find solution file
        solution_file = find_solution_file(folder_path)
        
        if not solution_file:
            print(f"  ⚠ No solution file found")
            skipped_count += 1
            continue
        
        # Extract stats from solution file
        stats = extract_stats_from_code(solution_file)
        
        if not stats or 'time' not in stats or 'memory' not in stats:
            print(f"  ⚠ No stats found in code comments")
            skipped_count += 1
            continue
        
        # Create description string
        description = f"Time: {stats['time']} ms ({stats['time_percent']}%) | Memory: {stats['memory']} MB ({stats['memory_percent']}%) - LeetSync"
        
        # Update README.md
        readme_path = os.path.join(folder_path, 'README.md')
        if update_readme_with_stats(readme_path, stats):
            print(f"  ✓ Updated README with stats")
        
        # Create desktop.ini for Windows Explorer tooltip
        if create_desktop_ini(folder_path, description):
            print(f"  ✓ Created desktop.ini with folder description")
        
        updated_count += 1
        print()
    
    print("\n" + "="*60)
    print(f"Summary:")
    print(f"  Updated: {updated_count}")
    print(f"  Skipped: {skipped_count}")
    print(f"  Total:   {updated_count + skipped_count}")
    print("="*60)

if __name__ == "__main__":
    print("="*60)
    print("LeetSync Statistics Update Script")
    print("="*60)
    print("\nThis script will:")
    print("1. Scan all problem folders")
    print("2. Extract timing/memory stats from code comments")
    print("3. Update README.md with stats at the top")
    print("4. Create desktop.ini for folder tooltips (Windows)")
    print("\n" + "="*60 + "\n")
    
    response = input("Continue? (y/n): ").strip().lower()
    if response == 'y':
        process_all_folders()
    else:
        print("Aborted.")
