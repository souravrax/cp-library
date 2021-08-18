#include <bits/stdc++.h>
using namespace std;

/* ------------- Segment Tree 2D -------------- */

template <typename T> class Segtree2D {
private:
  void build_row(const vector<T> &a, vector<T> &tree) {
    for (int i = 0; i < (int)a.size(); i++)
      tree[i + M] = a[i];
    for (int i = M - 1; i > 0; i--)
      tree[i] = comp(tree[i << 1], tree[i << 1 | 1]);
  }

  void bulid(vector<vector<T>> &grid) {
    for (int i = 0; i < (int)grid.size(); i++) {
      build_row(grid[i], parent_tree[i + N]);
    }
    for (int i = N - 1; i > 0; i--) {
      for (int j = 1; j < 2 * M; j++) { // merging two child trees
        T _left = parent_tree[i << 1][j];
        T _right = parent_tree[i << 1 | 1][j];
        parent_tree[i][j] = comp(_left, _right);
      }
    }
  }

  void upd_row(int idx, T val, vector<T> &tree) {
    idx += M;
    tree[idx] = val;
    for (idx >>= 1; idx > 0; idx >>= 1) {
      tree[idx] = comp(tree[idx << 1], tree[idx << 1 | 1]);
    }
  }

  T qry_row(int l, int r, int lx, int rx, int idx, const vector<T> &tree) {
    if (r < lx || l > rx)
      return default_value;
    if (l >= lx && r <= rx)
      return tree[idx];
    int mid = l + (r - l) / 2;
    return comp(qry_row(l, mid, lx, rx, idx << 1, tree),
                qry_row(mid + 1, r, lx, rx, idx << 1 | 1, tree));
  }

  T qry_main(int l, int r, int lx, int rx, int ly, int ry, int idx) {
    if (r < lx || l > rx)
      return default_value;
    if (l >= lx && r <= rx)
      return qry_row(0, M - 1, ly, ry, 1, parent_tree[idx]);
    int mid = l + (r - l) / 2;
    return comp(qry_main(l, mid, lx, rx, ly, ry, idx << 1),
                qry_main(mid + 1, r, lx, rx, ly, ry, idx << 1 | 1));
  }
  inline T comp(const T &a, const T &b) { return a + b; };

public:
  Segtree2D(vector<vector<T>> &grid, T _default_value = 0) {
    int n = (int)grid.size();
    int m = (int)grid[0].size();
    N = M = 1;
    while (N < n)
      N <<= 1;
    while (M < m)
      M <<= 1;
    default_value = _default_value;
    parent_tree.assign((size_t)N << 1, vector<T>((size_t)M << 1, default_value));
    bulid(grid);
  }
  inline T qry(int x1, int y1, int x2, int y2) {
    return qry_main(0, N - 1, x1, x2, y1, y2, 1);
  }
  void upd(int x, int y, T val) {
    x += N;
    upd_row(y, val, parent_tree[x]);
    for (x >>= 1; x > 0; x >>= 1) {
      auto &left = parent_tree[x << 1];
      auto &right = parent_tree[x << 1 | 1];
      for (int idx = y + M; idx > 0; idx >>= 1) {
        parent_tree[x][idx] = comp(left[idx], right[idx]);
      }
    }
  }

private:
  int N, M;
  vector<vector<T>> parent_tree;
  T default_value;
};

/* ---------------- Main Here --------------- */

int main() {
  size_t n, m;
  cin >> n >> m;
  vector grid(n, vector(m, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; ++j)
      cin >> grid[i][j];

  Segtree2D<int> st(grid, -1);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = i; k < n; k++) {
        for (int l = j; l < m; l++) {
          cout << st.qry(i, j, k, l) << '\n';
        }
      }
    }
  }
  cout << flush;
}
