vector<int> z_array(const string& _string, const string& _pattern) {
    int x = 0, y = 0;
    string s;
    char special = '$';
    s = _pattern + special + _string;
    int n = (int)s.size();
	vector<int> z(n);

    for(int i = 0; i < n; i++) {
        z[i] = max(0, min(z[i-x], y - i + 1));
        while (i + z[i] < n && s[z[i]] == s[i+z[i]]) {
            x = i, y = i + z[i], z[i]++;
        }
    }
    return vector<int>(z.begin() + _pattern.size() + 1, z.end());
}