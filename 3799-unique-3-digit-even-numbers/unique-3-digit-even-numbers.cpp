class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> digitCount(10, 0);
        for (int digit : digits) {
            digitCount[digit]++;
        }
        
        int uniqueCount = 0;
        
        // Iterate through all possible 3-digit even numbers (100 to 998)
        for (int num = 100; num < 1000; num += 2) {
            int currentCount[10] = {0};
            int temp = num;
            
            // Extract each digit and count its frequency
            while (temp > 0) {
                currentCount[temp % 10]++;
                temp /= 10;
            }
            
            // Check if we have enough of each digit to form this number
            bool canForm = true;
            for (int i = 0; i < 10; i++) {
                if (currentCount[i] > digitCount[i]) {
                    canForm = false;
                    break;
                }
            }
            
            if (canForm) {
                uniqueCount++;
            }
        }
        
        return uniqueCount;
    }
};