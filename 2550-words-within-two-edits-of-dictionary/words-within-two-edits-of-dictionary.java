class Solution {
    public List<String> twoEditWords(String[] queries, String[] dictionary) {
        List<String> result = new ArrayList<>();
        
        for (String q : queries) {
            for (String d : dictionary) {
                
                int diff = 0;
                
                for (int i = 0; i < q.length(); i++) {
                    if (q.charAt(i) != d.charAt(i)) {
                        diff++;
                    }
                    if (diff > 2) break; // early stop
                }
                
                if (diff <= 2) {
                    result.add(q);
                    break; // no need to check more dictionary words
                }
            }
        }
        
        return result;
    }
}