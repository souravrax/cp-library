#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
using namespace std;

const int mod = (int)1e9 + 7;

template <typename T = int> T poww(T a, T p) {
  // modular power
  T ans = 1;
  while (p) {
    if (p & 1)
      ans = (ans * a) % mod;
    a = (a * a) % mod;
    p >>= 1;
  }
  return ans;
}

template <typename T = int> T inv(T a) {
  // find modular inverse
  T ans = 1;
  T p = mod - 2;
  while (p) {
    if (p & 1)
      ans = (ans * a) % mod;
    a = (a * a) % mod;
    p >>= 1;
  }
  return ans;
}

using int64 = long long;

const int MAXN = 100'000;
int64 fact[MAXN], invs[MAXN];

void generate() {
  fact[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    fact[i] = fact[i - 1] * i;
    invs[i] = inv(fact[i]);
  }
}

template <typename T = int> T nck(T n, T k) {
  // n choose k
  if (n < k)
    return 0;
  return (fact[n] * invs[k] % mod) * invs[n - k] % mod;
}

int dp[1005][1005];
template <typename T = int> T ncr(T n, T r) {
  // n choose r (dp version)
  if (r > n)
    return 0;
  if (n == r)
    return 1;
  if (r == 0)
    return 1;
  return ~dp[n][r] ? dp[n][r] : dp[n][r] = ncr(n - 1, r) + ncr(n - 1, r - 1);
}

template <typename T = int> T npk(T n, T k) {
  // n permute k
  if (n < k)
    return 0;
  return fact[n] * invs[n - k] % mod;
}

// pascals
vector<int64_t> pascal[1005];
void pascal_nck() {
  for (int i = 1; i < 1005; i++) {
    pascal[i].push_back(1);
    for (int j = 1; j < (int)pascal[i - 1].size(); j++) {
      pascal[i].push_back(pascal[i - 1][j] + pascal[i - 1][j - 1]);
    }
    pascal[i].push_back(1);
  }
}