class Solution {
    public long minTime(int[] skill, int[] mana) {

        int n = skill.length;
        int m = mana.length;

        long[] prefix = new long[n];
        prefix[0] = skill[0];

        for(int i = 1; i < n; i++)
            prefix[i] = prefix[i-1] + skill[i];

        long prevStart = 0;

        for(int j = 1; j < m; j++) {

            long start = Long.MIN_VALUE;

            for(int i = 0; i < n; i++) {

                long prevFinish = prevStart + (long)mana[j-1] * prefix[i];
                long arrival;

                if(i == 0)
                    arrival = 0;
                else
                    arrival = (long)mana[j] * prefix[i-1];

                start = Math.max(start, prevFinish - arrival);
            }

            prevStart = start;
        }

        return prevStart + (long)mana[m-1] * prefix[n-1];
    }
}