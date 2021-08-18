#include <bits/stdtr1c++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

/*** Needs C++11 or C++14 ***/

/// Treap supporting duplicating values in set
/// Maximum value of treap * ADD must fit in int64_t

struct Treap { /// hash = 96814
  int len;
  const int ADD = 1000010;
  const int MAXVAL = 1000000010;
  tr1::unordered_map<int64_t, int> mp; /// Change to int if only int in treap
  tree<int64_t, null_type, less<int64_t>, rb_tree_tag,
       tree_order_statistics_node_update>
      T;

  Treap() {
    len = 0;
    T.clear(), mp.clear();
  }

  inline void clear() {
    len = 0;
    T.clear(), mp.clear();
  }

  inline void insert(int64_t x) {
    len++, x += MAXVAL;
    int c = mp[x]++;
    T.insert((x * ADD) + c);
  }

  inline void erase(int64_t x) {
    x += MAXVAL;
    int c = mp[x];
    if (c) {
      c--, mp[x]--, len--;
      T.erase((x * ADD) + c);
    }
  }

  /// 1-based index, returns the K'th element in the treap, -1 if none exists
  inline int64_t kth(int k) {
    if (k < 1 || k > len)
      return -1;
    auto it = T.find_by_order((size_t)--k);
    return ((*it) / ADD) - MAXVAL;
  }

  /// Count of value < x in treap
  inline int count(int64_t x) {
    x += MAXVAL;
    int c = mp[--x];
    return int(T.order_of_key((x * ADD) + c));
  }

  /// Number of elements in treap
  inline int size() { return len; }
};

int main() {}
