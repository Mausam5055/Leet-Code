#pragma GCC optimize("O2")
#include <vector>

using namespace std;

class Solution {
    int MOD = 1e9 + 7;
    typedef vector<vector<long long>> Matrix;

    // Helper function to multiply two matrices modulo 10^9 + 7
    Matrix multiply(Matrix& A, Matrix& B, int size) {
        Matrix C(size, vector<long long>(size, 0));
        for(int i = 0; i < size; ++i) {
            for(int k = 0; k < size; ++k) {
                if (A[i][k] == 0) continue; // Optimization for sparse properties
                for(int j = 0; j < size; ++j) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    // Helper function for matrix exponentiation
    Matrix power(Matrix A, long long p, int size) {
        Matrix res(size, vector<long long>(size, 0));
        for(int i = 0; i < size; ++i) res[i][i] = 1; // Identity matrix

        while (p > 0) {
            if (p % 2 == 1) res = multiply(res, A, size);
            A = multiply(A, A, size);
            p /= 2;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int k = r - l + 1;
        
        // Base Cases
        if (n == 1) return k;
        if (n == 2) return (1LL * k * (k - 1)) % MOD;

        // Create the transition matrix M
        Matrix M(k, vector<long long>(k, 0));
        for (int u = 0; u < k; ++u) {
            for (int w = 0; w < k; ++w) {
                // The mathematical condition derived from DP symmetry
                if (w >= k - u) {
                    M[u][w] = 1;
                }
            }
        }

        // Raise Matrix to the power of (n - 2)
        Matrix M_n_minus_2 = power(M, n - 2, k);

        // Base state vector for length 2 (0-indexed, so S2[u] = u)
        vector<long long> S2(k, 0);
        for (int u = 0; u < k; ++u) {
            S2[u] = u;
        }

        // Compute Sn = M^(n-2) * S2
        vector<long long> Sn(k, 0);
        long long sum_Sn = 0;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                Sn[i] = (Sn[i] + M_n_minus_2[i][j] * S2[j]) % MOD;
            }
            sum_Sn = (sum_Sn + Sn[i]) % MOD;
        }

        // Total sequences = 2 * (Sum of sequences ending in UP step)
        return (2LL * sum_Sn) % MOD;
    }
}; // <-- This is the closing brace the compiler was looking for!