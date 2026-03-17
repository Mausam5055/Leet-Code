import java.util.*;

class Solution {
    public String findLexSmallestString(String s, int a, int b) {

        Queue<String> q = new LinkedList<>();
        Set<String> visited = new HashSet<>();

        String ans = s;

        q.offer(s);
        visited.add(s);

        while(!q.isEmpty()){

            String cur = q.poll();

            if(cur.compareTo(ans) < 0)
                ans = cur;

            // Operation 1: Add to odd indices
            char[] arr = cur.toCharArray();

            for(int i = 1; i < arr.length; i += 2){
                int digit = (arr[i] - '0' + a) % 10;
                arr[i] = (char)(digit + '0');
            }

            String add = new String(arr);

            if(!visited.contains(add)){
                visited.add(add);
                q.offer(add);
            }

            // Operation 2: Rotate
            String rotate = cur.substring(cur.length() - b) +
                            cur.substring(0, cur.length() - b);

            if(!visited.contains(rotate)){
                visited.add(rotate);
                q.offer(rotate);
            }
        }

        return ans;
    }
}