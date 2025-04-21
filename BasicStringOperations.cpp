#include <bits/stdc++.h>
using namespace std;

string trimmed(string s) {
	const int n = int(size(s));
	int i = 0, j = n - 1;
	while (i < n && s[i] == ' ') i++;
	while (j > i && s[j] == ' ') j--;
	return s.substr(i, j - i + 1);
}

template<typename T = char>
string join(const vector<string>& v, T delim) {
	string ans;
	int n = (int)v.size();
	if (n == 0) return ans;
	ans += v[0];
	for (int i = 1; i < n; i++) {
		ans += delim;
		ans += v[i];
	}
	return ans;
}

vector<string> split(string s, char delim) {
	replace(s.begin(), s.end(), delim, ' ');
	stringstream ss(s);
	vector<string> ans;
	while (ss >> s)
		ans.push_back(s);
	return ans;
}

void touppercase(string& s) {
	for (char& c : s) c = toupper(c);
}

void tolowercase(string& s) {
	for (char& c : s) c = tolower(c);
}

void flipcase(string& s) {
	for (char& c : s) c = isupper(c) ? tolower(c) : toupper(c);
}