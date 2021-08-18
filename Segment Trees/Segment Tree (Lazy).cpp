#include <bits/stdc++.h>
using namespace std;
const int MAX = 1 << 19;

class SegtreeLazySum {
public:
  int a[MAX + 7], tree[4 * MAX + 7], lazy[4 * MAX + 7];
  void build(int node, int l, int r) {
    if (l == r) {
      tree[node] = a[l];
      return;
    }
    if (l >= r)
      return;
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }
  void upd(int node, int l, int r, int v) {
    lazy[node] += v;
    tree[node] += (r - l + 1) * x;
  }
  void pushDown(int node, int l,
                int r) // passing update information to the children
  {
    int mid = (l + r) / 2;
    upd(node * 2, l, mid, lazy[node]);
    upd(node * 2 + 1, mid + 1, r, lazy[node]);
    lazy[node] = 0;
  }
  void update(int node, int l, int r, int x, int y, int v) {
    if (x > r || y < l)
      return;
    if (x >= l && r <= y) {
      upd(node, l, r, v);
      return;
    }
    pushDown(node, l, r);
    int mid = (l + r) / 2;
    update(node * 2, l, mid, x, y, v);
    update(node * 2 + 1, mid + 1, r, x, y, v);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }
};

template <typename T = int64_t> class SegmentTreeLazyMax {
public:
  T Tree[4 * MAX], Lazy[4 * MAX];
  void push(int node) {
    if (Lazy[node]) {
      Lazy[lc] += Lazy[node];
      Lazy[rc] += Lazy[node];
      Tree[lc] += Lazy[node];
      Tree[rc] += Lazy[node];
      Lazy[node] = 0;
    }
  }

  void build(int node, int l, int r) {
    Lazy[node] = 0;
    if (l == r) {
      Tree[node] = in[l];
      return;
    }
    int mid = (l + r) / 2;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    Tree[node] = max(Tree[lc], Tree[rc]);
    Lazy[node] = 0;
  }
  void upd(int node, int l, int r, int x, int y, T val) {
    if (x > r || y < l)
      return;
    if (x <= l && r <= y) {
      Tree[node] += val;
      Lazy[node] += val;
      return;
    }

    if (l != r)
      push(node);

    int mid = (l + r) / 2;
    upd(lc, l, mid, x, y, val);
    upd(rc, mid + 1, r, x, y, val);
    Tree[node] = max(Tree[lc], Tree[rc]);
  }

  T qry(int node, int l, int r, int x, int y) {
    if (x > r || y < l)
      return -INF;
    if (x <= l && r <= y)
      return Tree[node];
    if (l != r)
      push(node);

    int mid = (l + r) / 2;
    return max(qry(lc, l, mid, x, y), qry(rc, mid + 1, r, x, y));
  }
};
