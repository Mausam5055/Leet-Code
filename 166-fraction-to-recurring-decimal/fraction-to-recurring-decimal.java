class Solution {
    public String fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";

        StringBuilder result = new StringBuilder();

        // Sign
        if ((numerator < 0) ^ (denominator < 0)) {
            result.append("-");
        }

        // Use long to prevent overflow
        long num = Math.abs((long) numerator);
        long den = Math.abs((long) denominator);

        // Integer part
        result.append(num / den);

        long remainder = num % den;
        if (remainder == 0) return result.toString();

        result.append(".");

        // Map: remainder -> index in result
        Map<Long, Integer> map = new HashMap<>();

        while (remainder != 0) {

            // If repeating remainder found
            if (map.containsKey(remainder)) {
                int index = map.get(remainder);
                result.insert(index, "(");
                result.append(")");
                break;
            }

            map.put(remainder, result.length());

            remainder *= 10;
            result.append(remainder / den);
            remainder %= den;
        }

        return result.toString();
    }
}
