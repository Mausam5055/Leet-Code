class Solution {
    public List<String> readBinaryWatch(int turnedOn) {
        List<String> result = new ArrayList<>();

        for (int h = 0; h < 12; h++) {
            for (int m = 0; m < 60; m++) {

                int bits = Integer.bitCount(h) + Integer.bitCount(m);

                if (bits == turnedOn) {
                    result.add(h + ":" + String.format("%02d", m));
                }
            }
        }

        return result;
    }
}
