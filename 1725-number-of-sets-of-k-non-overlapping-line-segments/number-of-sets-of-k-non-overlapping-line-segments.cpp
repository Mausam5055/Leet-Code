class Solution {
    int mod = 1e9 + 7;
    
    // Function to calculate (base^exp) % mod
    long long modPow(long long base, long long exp) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }
    
    // Function to find modular inverse of n modulo 10^9 + 7
    long long modInverse(long long n) {
        return modPow(n, mod - 2);
    }
    
public:
    int numberOfSets(int n, int k) {
        int N = n + k - 1;
        int K = 2 * k;
        
        // If we need to pick more points than available (though constraints guarantee this won't happen)
        if (K > N) return 0;
        
        long long numerator = 1;
        long long denominator = 1;
        
        // Calculate N C K  (which is N! / (K! * (N-K)!))
        // We only need to multiply K terms
        for (int i = 0; i < K; i++) {
            numerator = (numerator * (N - i)) % mod;
            denominator = (denominator * (i + 1)) % mod;
        }
        
        // (numerator / denominator) % mod is equivalent to (numerator * modInverse(denominator)) % mod
        return (numerator * modInverse(denominator)) % mod;
    }
};