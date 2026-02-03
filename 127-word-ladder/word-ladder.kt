class Solution {
    fun ladderLength(beginWord: String, endWord: String, wordList: List<String>): Int {

        val wordSet = wordList.toMutableSet()
        if (!wordSet.contains(endWord)) return 0

        val queue: ArrayDeque<String> = ArrayDeque()
        queue.add(beginWord)

        var level = 1

        while (queue.isNotEmpty()) {
            val size = queue.size

            repeat(size) {
                val word = queue.removeFirst()
                val chars = word.toCharArray()

                for (i in chars.indices) {
                    val original = chars[i]

                    for (c in 'a'..'z') {
                        if (c == original) continue
                        chars[i] = c
                        val newWord = String(chars)

                        if (newWord == endWord) return level + 1

                        if (wordSet.contains(newWord)) {
                            queue.add(newWord)
                            wordSet.remove(newWord)
                        }
                    }
                    chars[i] = original
                }
            }
            level++
        }
        return 0
    }
}
