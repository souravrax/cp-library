#include <bits/stdc++.h>
using namespace std;

template <typename T = int> class Fenwick {
private:
  vector<T> bit;
  int n;

public:
  Fenwick() = default;
  Fenwick(int _n) : n(_n) { bit.assign(_n + 1, 0); }
  void resize(int _n) {
    n = _n + 1;
    bit.assign(_n + 1);
  }
  void upd(int x, T val) {
    for (x++; x <= n; x += (x & -x))
      bit[x] += val;
  }
  T qry(int x) {
    T ans = 0;
    for (x++; x > 0; x -= (x & -x))
      ans += bit[x];
    return ans;
  }
  T operator[](int idx) {
    assert(idx < n && "Index out of bound");
    return this->qry(idx) - this->qry(idx - 1);
  }
  T bit_search(int);
};


template <typename T> T Fenwick<T>::bit_search(int v) {
  // This is equivalent to calculating lower_bound on prefix sums array
  int sum = 0;
  int pos = 0;
  for (int i = 19; i >= 0; i--) {
    if (pos + (1 << i) < n && sum + bit[pos + (1 << i)] < v) {
      sum += bit[pos + (1 << i)];
      pos += (1 << i);
    }
  }
  return pos + 1;
  // +1 because 'pos' will have position of largest value less than 'v'
}