#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, l;
    cin >> n >> m >> l;
    // n = number of elements in the array
    // m = number of queries
    // l = size of the window

    vector<int> ans(n);
    deque<int> q;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (q.size() >= l) {
            q.pop_front();
        }
        while (!q.empty() && q.back() > x) {
            q.pop_back();
        }
        q.push_back(x);

        cout << q.front() << endl;
    }
}