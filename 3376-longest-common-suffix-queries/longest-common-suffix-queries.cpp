class Solution {
public:

    struct Node {
        int child[26];
        int idx;

        Node() {
            memset(child, -1, sizeof(child));
            idx = -1;
        }
    };

    vector<Node> trie;

    int better(int a, int b, vector<string>& words) {
        if (a == -1) return b;
        if (b == -1) return a;

        if (words[a].size() != words[b].size())
            return words[a].size() < words[b].size() ? a : b;

        return min(a, b);
    }

    void insert(string &word, int id, vector<string>& words) {
        int node = 0;

        trie[node].idx = better(trie[node].idx, id, words);

        for (int i = word.size() - 1; i >= 0; i--) {
            int c = word[i] - 'a';

            if (trie[node].child[c] == -1) {
                trie[node].child[c] = trie.size();
                trie.push_back(Node());
            }

            node = trie[node].child[c];

            trie[node].idx = better(trie[node].idx, id, words);
        }
    }

    int query(string &word) {
        int node = 0;

        for (int i = word.size() - 1; i >= 0; i--) {
            int c = word[i] - 'a';

            if (trie[node].child[c] == -1)
                break;

            node = trie[node].child[c];
        }

        return trie[node].idx;
    }

    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        trie.push_back(Node());

        for (int i = 0; i < wordsContainer.size(); i++) {
            insert(wordsContainer[i], i, wordsContainer);
        }

        vector<int> ans;

        for (auto &q : wordsQuery) {
            ans.push_back(query(q));
        }

        return ans;
    }
};