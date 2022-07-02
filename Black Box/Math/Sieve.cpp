#include <bits/stdc++.h>
using namespace std;
const int nax = (int)1e6 + 7;
vector<int> primes;

// Finds all the primes upto MAX

// void sieve() {

void sieve(bool generate_primes = false) {
    bitset<nax> sieve_status;
    for (int i = 2; i * i < nax; i++) {
        if (sieve_status[i]) continue;
        for (int j = i * i; j < nax; j += i) {
            sieve_status[j] = true;
        }
    }
    if (generate_primes) {
        for (int i = 2; i < nax; i++) {
            if (sieve_status[i]) continue;
            primes.push_back(i);
        }
    }
}