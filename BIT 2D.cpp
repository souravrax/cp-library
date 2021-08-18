#include <bits/stdc++.h>
using namespace std;
// Call with size of the grid
// Example: BIT<int> Tree(n+1,m+1) for n x m grid indexed from 1

template <typename T = int> struct BIT {
  vector<vector<T>> bit;
  int n, m;
  BIT(int _n, int _m) : bit(_n, vector<T>(_m)), n(_n), m(_m) {}
  void upd(int r, int c, int val) { // x[k] += a
    for (; r < n; r |= (r + 1))
      for (int col = c; col < m; col |= (col + 1))
        bit[r][col] += val;
  }
  T sum(int r, int c) { // return x[0] + ... + x[k]
    T ans = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      for (int col = c; col >= 0; c = (col & (col + 1)) - 1)
        ans += bit[r][col];
    return ans;
  }
};