#include <bits/stdc++.h>
using namespace std;

template <typename T = int> struct SegmentTree {
    vector<int> tree;
    int N;
    SegmentTree(const vector<T>& a) {
        int n = (int)a.size();
        this->N = 1;
        while (N < n) N <<= 1;
        tree.resize(N << 1);
        for (int i = 0; i < n; i++) {
            tree[i + N] = a[i];
        }
        for (int i = N - 1; i; --i) {
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
        }
    }
    T query(int l, int r) {
        return query(l, r, 0, N, 1);
    }

    T query(const int l, const int r, int lx, int rx, int idx) {
        if (lx >= l && rx <= r) {
            return tree[idx];
        }
        if (rx < l || lx > r) return 0;
        int mid = lx + (rx - lx) / 2;
        return query(l, r, lx, mid, idx << 1) + query(l, r, mid + 1, rx, idx << 1 | 1);
    }
    void update(int x, int val) {
        x += N;
        tree[x] = val;
        for (x >>= 1; x; x >>= 1) {
            tree[x] = tree[x << 1] + tree[x << 1 | 1];
        }
    }
};

template <typename T = int> struct BIT {
    vector<T> tree;
    int n;
    BIT(int n) {
        this->n = n;
        tree.resize(this->n);
    }
    void upd(int idx, int val) {
        idx++;
        for (; idx <= n; idx += (idx & -idx)) {
            tree[idx] += val;
        }
    }

    T qry(int idx) {
        int ans = 0;
        for (++idx; idx > 0; idx -= (idx & -idx)) {
            ans += tree[idx];
        }
        return ans;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    SegmentTree st(a);
}
