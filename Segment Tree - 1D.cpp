#include <bits/stdc++.h>
using namespace std;

template <typename T> class SegmentTree {
private:
    T comp(T a, T b) { return a + b; }
public:
    SegmentTree(int n, T default_value = 0) {
        this->N = 1;
        while (N < n)
            N <<= 1;
        this->default_value = default_value;
        tree.assign(N << 1, default_value);
    }
    inline void build(vector<int> &a) {
        int n = a.size();
        for (int i = 0; i < n; i++)
            tree[i + N] = a[i];
        for (int i = N - 1; i > 0; i--)
            tree[i] = comp(tree[i << 1], tree[i << 1 | 1]);
    }
    inline void upd(int idx, T val) {
        idx += N;
        tree[idx] = val;
        for (idx >>= 1; idx > 0; idx >>= 1)
            tree[idx] = comp(tree[idx << 1], tree[idx << 1 | 1]);
    }
    T qry(int l, int r, int lx, int rx, int idx) {
        if (r < lx || l > rx)
            return default_value;
        if (l >= lx && r <= rx)
            return tree[idx];
        int mid = l + (r - l) / 2;
        return comp(qry(l, mid, lx, rx, idx << 1),
            qry(mid + 1, r, lx, rx, idx << 1 | 1));
    }
    inline T qry(int l, int r) const { return qry(0, N - 1, l, r, 1); }
private:
    int N;
    vector<T> tree;
    T default_value;
};

int N;
int tree[100005];
int qry(int l, int r) {
    int ans = 0;
    l += N;
    r += N;
    while (l < r) {
        if (l & 1) ans += tree[l++];
        if ((r & 1) ^ 1) ans += tree[r--];
        l >>= 1, r >>= 1;
    }
    return ans;
}