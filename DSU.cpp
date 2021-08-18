#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> parent, rank;
	int n;
	DSU(int _n) {
		n = _n;
		parent.resize(_n);
		rank.assign(_n, 1);
		iota(parent.begin(), parent.end(), 0);
	}
	void join(int u, int v) {
		u = find(u), v = find(v);
		if (rank[u] < rank[v]) swap(u, v);
		parent[v] = u;
		if (u != v)
			rank[u] += rank[v];
	} 
	int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }
};