#include <vector>
#include <string>

using namespace std;

class Solution {
    struct TrieNode {
        int children[26];
        int best_idx;
        
        TrieNode() {
            for (int i = 0; i < 26; ++i) {
                children[i] = -1;
            }
            best_idx = -1;
        }
    };
    
    vector<TrieNode> trie;
    
    void updateBest(int u, int index, const vector<string>& container) {
        if (trie[u].best_idx == -1) {
            trie[u].best_idx = index;
        } else {
            int cur_best = trie[u].best_idx;
            // Update if the new string is strictly shorter
            // (Tie-breakers for earlier index are naturally handled because 
            // we insert in ascending order of indices, and only update on < )
            if (container[index].length() < container[cur_best].length()) {
                trie[u].best_idx = index;
            }
        }
    }
    
    void insert(const string& word, int index, const vector<string>& container) {
        int u = 0;
        updateBest(u, index, container); // Update the root for cases with 0 common suffix matches
        
        for (int i = word.length() - 1; i >= 0; --i) {
            int c = word[i] - 'a';
            if (trie[u].children[c] == -1) {
                trie[u].children[c] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].children[c];
            updateBest(u, index, container);
        }
    }
    
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        // Initialize the root of the Trie
        trie.emplace_back();
        
        // Build the reverse Trie
        for (int i = 0; i < wordsContainer.size(); ++i) {
            insert(wordsContainer[i], i, wordsContainer);
        }
        
        vector<int> ans;
        ans.reserve(wordsQuery.size());
        
        // Process each query
        for (const string& q : wordsQuery) {
            int u = 0;
            // Trace the query backwards through the Trie
            for (int i = q.length() - 1; i >= 0; --i) {
                int c = q[i] - 'a';
                if (trie[u].children[c] == -1) {
                    break;
                }
                u = trie[u].children[c];
            }
            // The node we stop at holds the pre-computed best index
            ans.push_back(trie[u].best_idx);
        }
        
        return ans;
    }
};