#include <bits/stdc++.h>
#include <string>
using namespace std;

// Arpa's O(nlogn) offline min/max range query algorithm
template<typename T = int>
vector<T> Arpas(const vector<T>& a, vector<vector<T>>& queries) {
    T n = (T)a.size();
    vector<T> parent(n);
    function<T(T)> find = [&](T x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    };
    stack<T> st;

    vector<vector<pair<T, T>>> transition(n);
    for (int i = 0; i < (int)queries.size(); i++) {
        T l = queries[i][0];
        T r = queries[i][1];
        transition[r].push_back({l, i});
    }

    vector<int> ans(n);
    for (T i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) {
            parent[st.top()] = i;
            st.pop();
        }
        st.push(i);
        for (auto& [l, idx] : transition[i]) {
            ans[idx] = a[find(l)];
        }
    }
    return ans;
}