#include <bits/stdc++.h>
using namespace std;

template<typename T, typename Compare = less<T>>
class sparse_table {
    Compare comp;
    const int MAXLOG = 20;
    int n;
    vector<int> pre_log;
    vector<vector<T>> dp;
    inline T f(T& a, T& b) { return comp(a, b) ? a : b; }
public:
    sparse_table(const vector<T>& nums) {
        this->n = (int)nums.size();
        pre_log.assign(n + 1, 0);
        dp.assign(n, vector<T>(MAXLOG));
        for (int i = 2; i <= n; i++) pre_log[i] = pre_log[i / 2] + 1;
        for (int j = 0; j < MAXLOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                if (j == 0) dp[i][j] = nums[i];
                else dp[i][j] = f(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]); 
    }

    inline T operator[](int idx) { return dp[idx][0]; }

    T qry(int l, int r) {
        int k = pre_log[r - l + 1];
        return f(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
};