class Solution {

    fun findLadders(
        beginWord: String,
        endWord: String,
        wordList: List<String>
    ): List<List<String>> {

        val wordSet = wordList.toHashSet()
        if (!wordSet.contains(endWord)) return emptyList()

        val parents = HashMap<String, MutableList<String>>()
        val distance = HashMap<String, Int>()

        bfs(beginWord, endWord, wordSet, parents, distance)

        val result = mutableListOf<List<String>>()
        if (!distance.containsKey(endWord)) return result

        dfs(endWord, beginWord, parents, mutableListOf(), result)
        return result
    }

    // ---------- BFS ----------
    private fun bfs(
        begin: String,
        end: String,
        wordSet: Set<String>,
        parents: HashMap<String, MutableList<String>>,
        distance: HashMap<String, Int>
    ) {
        val queue: ArrayDeque<String> = ArrayDeque()
        queue.add(begin)
        distance[begin] = 0

        while (queue.isNotEmpty()) {
            val size = queue.size
            for (i in 0 until size) {
                val word = queue.removeFirst()
                val currDist = distance[word]!!

                for (next in getNextWords(word, wordSet)) {
                    if (!distance.containsKey(next)) {
                        distance[next] = currDist + 1
                        parents[next] = mutableListOf(word)
                        queue.add(next)
                    } else if (distance[next] == currDist + 1) {
                        parents[next]!!.add(word)
                    }
                }
            }
        }
    }

    // ---------- DFS ----------
    private fun dfs(
        word: String,
        begin: String,
        parents: HashMap<String, MutableList<String>>,
        path: MutableList<String>,
        result: MutableList<List<String>>
    ) {
        path.add(word)

        if (word == begin) {
            result.add(path.reversed())
        } else {
            for (p in parents[word] ?: emptyList()) {
                dfs(p, begin, parents, path, result)
            }
        }

        path.removeAt(path.size - 1)
    }

    // ---------- Generate neighbors ----------
    private fun getNextWords(word: String, wordSet: Set<String>): List<String> {
        val res = mutableListOf<String>()
        val chars = word.toCharArray()

        for (i in chars.indices) {
            val original = chars[i]
            for (c in 'a'..'z') {
                if (c == original) continue
                chars[i] = c
                val newWord = String(chars)
                if (wordSet.contains(newWord)) {
                    res.add(newWord)
                }
            }
            chars[i] = original
        }
        return res
    }
}
