#include <bits/stdc++.h>
using namespace std;

struct UF {
private:
	vector<int> parent, rank;
	size_t n;
	int comp;
public:
	UF(size_t _n) : n(_n), comp(_n) {
		parent.resize(n);
		rank.assign(n, 1);
		iota(parent.begin(), parent.end(), 0);
	}
	void join(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return;
		if (rank[u] < rank[v]) swap(u, v);
		comp--;
		parent[v] = u;
		rank[u] += rank[v];
	} 
	int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }
	inline int size(const int& x) { return rank[(size_t)find(x)]; }
	inline int get_comp() const { return comp; }
};