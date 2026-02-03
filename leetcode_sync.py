import json
import os
import time
import urllib.request
import urllib.error
import sys

# Constants
BASE_URL = "https://leetcode.com"
GRAPHQL_URL = "https://leetcode.com/graphql"

# Extension mapping
EXTENSIONS = {
    "java": "java",
    "python": "py",
    "python3": "py",
    "cpp": "cpp",
    "c": "c",
    "javascript": "js",
    "typescript": "ts",
    "golang": "go",
    "scala": "scala",
    "kotlin": "kt",
    "rust": "rs",
    "php": "php",
    "ruby": "rb",
    "swift": "swift",
    "csharp": "cs",
    "dart": "dart",
    "elixir": "ex",
}

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
    
    solved_problems.sort(key=lambda x: int(x["id"]) if str(x["id"]).isdigit() else float('inf'))
    return solved_problems

def get_submission_code(headers, submission_id):
    query = """
    query submissionDetails($submissionId: Int!) {
        submissionDetails(submissionId: $submissionId) {
            code
            lang {
                name
                verboseName
            }
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

def get_problem_description(headers, slug):
    query = """
    query questionContent($titleSlug: String!) {
        question(titleSlug: $titleSlug) {
            content
        }
    }
    """
    data = make_request(
        GRAPHQL_URL, 
        method="POST", 
        headers=headers, 
        data={"query": query, "variables": {"titleSlug": slug}}
    )
    if data and "data" in data and "question" in data["data"]:
        return data["data"]["question"]
    return None

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

def save_problem(problem, code_data, description_data, submission_meta):
    # Directory name structure: ID-Slug
    dir_name = f"{problem['id']}-{problem['slug']}"
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
    
    # Save README.md
    content = description_data["content"] if description_data and "content" in description_data else None
    if content:
        with open(os.path.join(dir_name, "README.md"), "w", encoding="utf-8") as f:
            f.write(content)
    
    # Save Code file
    lang_slug = submission_meta["lang"]
    ext = EXTENSIONS.get(lang_slug, "txt")
    file_name = f"{problem['slug']}.{ext}"
    file_path = os.path.join(dir_name, file_name)
    
    with open(file_path, "w", encoding="utf-8") as f:
        f.write(code_data["code"])
        
    print(f"Synced: {dir_name}")

def main():
    print("=== LeetCode Sync Script ===")
    print("Please input your LeetCode cookies. You can find them in your browser dev tools.")
    
    session_id = input("Enter LEETCODE_SESSION: ").strip()
    csrf_token = input("Enter csrftoken: ").strip()
    
    if not session_id or not csrf_token:
        print("Cookies are required.")
        return

    headers = get_headers(session_id, csrf_token)
    
    solved = get_all_problems(headers)
    print(f"\nFound {len(solved)} solved problems.")
    
    if not solved:
        print("No solved problems found (or auth failed).")
        return

    count = 0
    for problem in solved:
        try:
            # Simple rate limiting
            time.sleep(1) 
            
            sub_meta = get_latest_submission(headers, problem["slug"])
            if not sub_meta:
                print(f"Skipping {problem['slug']} (no accepted submission found via API)")
                continue
                
            sub_id = sub_meta["id"]
            code_data = get_submission_code(headers, int(sub_id))
            
            # Fetch description separately
            description_data = get_problem_description(headers, problem["slug"])
            
            if code_data:
                save_problem(problem, code_data, description_data, sub_meta)
                count += 1
            else:
                print(f"Failed to get code for {problem['slug']}")
                
        except Exception as e:
            print(f"Error processing {problem['slug']}: {e}")
            import traceback
            traceback.print_exc()

    print(f"\nSync complete! {count} problems synced.")

if __name__ == "__main__":
    main()
