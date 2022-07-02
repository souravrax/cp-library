#include <bits/stdc++.h>
using namespace std;

vector<int> generate_prefix(string s) {
    int n = int(s.length());
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int find_pattern(string txt, string pat) {
    vector<int> pi = generate_prefix(pat);
    int txt_ptr = 0, p_ptr = 0;
    const int n = int(txt.length());
    const int m = int(pat.length());
    while (txt_ptr < n) {
        if (txt[txt_ptr] == pat[p_ptr]) txt_ptr++, p_ptr++;
        else {
            if (p_ptr == 0) txt_ptr++;
            else p_ptr = pi[p_ptr - 1];
        }
        if (p_ptr == m) return txt_ptr - m;
    }
    return -1;
}

int main() {
    string s = "aaacd";
    string p = "cd";
    printf("my function: %d\nstl string find function: %lld", find_pattern(s, p), s.find(p));
}
