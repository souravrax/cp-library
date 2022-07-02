#include <bits/stdc++.h>
using namespace std;

template <typename T = int> class Trie {
private:
  struct node {
    node *bit[2];
    int bit_cnt = 0;
    node() {
      memset(bit, 0, sizeof bit);
      bit_cnt = 0;
    }
  };
  node *root;
  const int MAX_BITS = 30;

public:
  Trie() { this->root = new node(); }
  inline void insert(T val) {
    auto curr = this->root;
    for (int i = MAX_BITS; ~i; i--) {
      int b = (val >> i) & 1;
      if (curr->bit[b] == nullptr)
        curr->bit[b] = new node();
      curr = curr->bit[b];
      curr->bit_cnt++;
    }
  }
  inline void remove(T val) {
    auto curr = this->root;
    for (int i = MAX_BITS; ~i; i--) {
      int b = (val >> i) & 1;
      if (--curr->bit[b]->bit_cnt == 0) {
        curr->bit[b] = nullptr;
        break;
      }
      curr = curr->bit[b];
    }
  }
  inline T get_max_xor(T val) {
    T counter_val = 0;
    auto curr = this->root;
    for (int i = MAX_BITS; ~i; i--) {
      int b = (val>>i)&1;
      if (curr->bit[b^1])
        b ^= 1;
      counter_val <<= 1;
      counter_val |= b;
      curr = curr->bit[b];
    }
    return counter_val ^ val;
  }
};
