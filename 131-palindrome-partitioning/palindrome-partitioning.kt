class Solution {
    fun partition(s: String): List<List<String>> {
        val result = mutableListOf<List<String>>()
        val path = mutableListOf<String>()
        
        fun backtrack(start: Int) {
            // Base case: reached end of string
            if (start == s.length) {
                result.add(ArrayList(path))
                return
            }
            
            // Try all possible substrings
            for (end in start until s.length) {
                if (isPalindrome(s, start, end)) {
                    path.add(s.substring(start, end + 1))
                    backtrack(end + 1)
                    path.removeAt(path.size - 1) // backtrack
                }
            }
        }
        
        backtrack(0)
        return result
    }
    
    private fun isPalindrome(s: String, left: Int, right: Int): Boolean {
        var l = left
        var r = right
        while (l < r) {
            if (s[l] != s[r]) return false
            l++
            r--
        }
        return true
    }
}
