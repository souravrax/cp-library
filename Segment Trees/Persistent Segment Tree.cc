#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll predicate(ll a, ll b) {
    return a + b;
}

ll default_value() {
    return 0;
}

struct Node {
	ll val;
	Node *l, *r;

	Node(ll x) : val(x), l(nullptr), r(nullptr) {}
	Node(Node *ll, Node *rr) {
		l = ll, r = rr;
		val = predicate(l ? l->val : 0, r ? r->val : 0);
	}
	Node(Node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
};

class PST {
public:
    PST(vector<int> a) {
        this->n = a.size();
        roots.push_back(build(a));
    }
    void update(int pos, int val) {
        roots.push_back(update(roots.back(), pos, val));
    }
    int qry(int l, int r, int idx = n - 1) {
        return query(roots[idx], l, r);
    }
private:
    int n;
    vector<Node*> roots;
    
    Node* build(vector<int>& a, int l = 0, int r = n - 1) {
        if (l == r) return new Node(a[l]);
        int mid = l + (r - l) / 2;
        return new Node(build(a, l, mid), build(a, mid + 1, r));
    }
    
    Node* update(Node* ref, int val, int pos, int l = 0, int r = n - 1) {
    	if (l == r) return new Node(val);
    	int mid = l + (r - l) / 2;
    	if (pos > mid) return new Node(ref->l, update(ref->r, val, pos, mid + 1, r));
    	else return new Node(update(ref->l, val, pos, l, mid), ref->r);
    }
    
    ll query(Node* node, int ql, int qr, int l = 0, int r = n - 1) {
        if (node == nullptr) return default_value();
        if (r < ql || l > qr) return default_value();
        if (l >= ql && r <= qr) return node->val;
        int mid = l + (r - l) / 2;
        return predicate(query(node->left, ql, qr, l, mid), query(node->right, ql, qr, mid + 1, r));
    }
};

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    PST st(a);
}