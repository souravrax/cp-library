#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::max;
using std::min;

/** Algorithm
 *  
 *  First let's take a Z-Window (l, r)
 *  If the current index + z[current_index - left] < r; then
 *      we are sure that if we try to check it against the 0,1,2... it will be the same
 *      so we put z[current_index] = z[current_index - left]
 *  else; do
 *      we can either get a bigger value here or a smaller one
 *      set the left of the window to the current_index
 *      now increment right as long as s[right] == s[right - left]
 *      set z[current_index] = right - left
 *      decrement right, as that was the unmatched character
 *
 *  return the z array
**/

vector<int> z_array(string s) {
    const int n = (int)s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i + z[i - l] < r) {
            z[i] = z[i - l];
        } else {
            l = i, r = max(r, i);
            while (r < n && s[r] == s[r - l]) r++;
            z[i] = r---l;
        }
    }
    return z;
}

int main() {
    string s = "aabxaabxcaabxaabxay";
    string p = "aabx";
    swap(s, p);
    s += '#';
    s += p;
    auto z = z_array(s);
    for (char& c : s) {
        printf("%c ", c);
    }
    puts("");
    for (int& i : z) {
        printf("%d ", i);
    }
    puts("");
}
