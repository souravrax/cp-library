#include <bits/stdc++.h>
using namespace std;

int p[100'005], c[100'005], lcp[100'005];

// Note: Pass the string apped with '$' at the end, else it won't work (suffix array needs a special character at the end)

void build_suffix_array(string s) {
	int n = (int)s.length();
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++) v.emplace_back(s[i], i);
	sort(v.begin(), v.end());

	for (int i = 0; i < n; i++) p[i] = v[i].second;
	c[p[0]] = 0;
	for (int i = 1; i < n; i++)
		c[p[i]] = c[p[i - 1]] + (v[i].first != v[i - 1].first);


	for (int k = 0; (1 << k) < n; k++) {
		vector<pair<pair<int, int>, int>> v;
		for (int i = 0; i < n; i++) v.push_back({{c[i], c[i + (1 << k)]}, i});
		sort(v.begin(), v.end());
		for (int i = 0; i < n; i++) p[i] = v[i].second;
		c[p[0]] = 0;
		for (int i = 1; i < n; i++)
			c[p[i]] = c[p[i - 1]] + (v[i].first != v[i - 1].first);	
	}
}


void build_lcp_array(string s) {
	int k = 0;
	int n = (int)s.size();
	for (int pi = 0; pi < n - 1; pi++) { // till (n - 2) because (n - 1'th char is a special character '$', and is always smaller)
		int pj = p[c[pi] - 1];
		while (pi + k < n && pj + k < n && s[pi + k] == s[pj + k]) k++;
		lcp[pi] = k;
		k = max(0, k - 1);
	}
}

bool search_substring(string s, string t) {
	int n = (int)s.length();
	int m = (int)t.length();

	int lo = 0, hi = n - 1;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		int pi = p[mid];
		int substr_size = min(n - pi, m);
		string sub = s.substr(pi, substr_size);
		if (sub == t) return true;
		else if (sub < t) lo = mid + 1;
		else hi = mid - 1;
	}
	return false;
}

int string_upper_bound(string s, string t) {
	int n = (int)s.length();
	int m = (int)t.length();

	int lo = 0, hi = n - 1;
	int ans = n;

	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		int pi = p[mid];
		int substr_size = min(n - pi, m);
		string sub = s.substr(pi, substr_size);
		if (sub > t) {
			ans = mid;
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	return n;
}

int string_lower_bound(string s, string t) {
	int n = (int)s.length();
	int m = (int)t.length();

	int lo = 0, hi = n - 1;
	int ans = n;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		int pi = p[mid];
		int substr_size = min(n - pi, m);
		string sub = s.substr(pi, substr_size);
		if (sub >= t) {
			ans = mid;
			hi = mid - 1;
		} else {
			lo = mid - 1;
		}
	}
	return ans;
}


