#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(string gs) {
    string s = "#";
    for (char& c : gs) {
        s += c;
        s += '#';
    }
    int n = (int)s.length();
    vector<int> P(n);
    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        if (right <= i) {
            left = right = i;
            while (left >= 0 && right < n && s[left] == s[right]) P[i]++, left--, right++;
            left++, right--;
        } else {
            int mirror_pos = left + (right - i);
            P[i] = P[mirror_pos];
            if (mirror_pos - P[mirror_pos] + 1 == left) {
                left = i - P[i];
                right = i + P[i];
                while (left >= 0 && right < n && s[left] == s[right]) P[i]++, left--, right++;
                left++, right--;
            } 
        }
    }
    for (int i = 0; i < n; i++) {
        cout << s[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << P[i] << ' ';
    }
    return P;
}

int32_t main() {
    string s;
    cin >> s;
    vector<int> res = manacher(s);
}