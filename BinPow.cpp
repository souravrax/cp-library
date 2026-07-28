#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int binPow(int n, int p)
{
    if (p == 0)
        return 1;
    int res = binPow(n, p / 2);
    res = (res * res) % mod;
    if (p & 1)
    {
        res = (res * n) % mod;
    }
    return res;
}

int main()
{
    int n, p;
    cin >> n >> p;
    cout << binPow(n, p);
}