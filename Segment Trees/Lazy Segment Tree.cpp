#include <bits/stdc++.h>
using namespace std;

struct Node {
	int val;
	int lazy;
	Node() {
		val = 0;
		lazy = 0;
	}
};

class SegmentTree {
private:
	vector<Node> tree;
	int N;
public:
	SegmentTree(vector<int> a) {
		int n = (int)a.size();
		N = 1;
		while (N < n) N <<= 1;
		tree.resize(2 * N);
		build(a);
	}

	void build(vector<int> a) {
		for (int i = 0; i < (int)a.size(); ++i) {
			tree[i + N].val = a[i];
		}
		for (int i = N - 1; i > 0; i--) {
			tree[i].val = tree[i<<1].val + tree[i<<1|1].val;
		}
	}

	int upd(int pos, int val) {
		update(0, N - 1, pos, val, 1);
	}

	void update(int l, int r, int pos, int val, int idx) {
		if (l == r) {
			tree[idx].val = val;
			return;
		}
		int mid = l + (r - l) / 2;
		if (pos <= mid) {
			update(l, mid, pos, val, idx<<1);
		} else {
			update(mid + 1, r, pos, val, idx<<1|1);
		}
		tree[idx].val = tree[idx<<1].val + tree[idx<<1|1].val;
	}

	void range_update(int l, int r, int lx, int rx, int idx, int val) {
		if (r < lx || l > rx) return;
		if (l >= lx && r <= rx) {
			tree[idx].lazy += (r - l + 1) * val;
			return tree[idx].lazy + tree[idx].val;
		}
	}

	int range_add(int l, int r, int val) {
		range_update(0, N - 1, l, r, 0, val);
	}

	
};

int32_t main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& i : a) cin >> i;

}