#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "../fenwick_tree.hpp"

int main() {
    int n, q;
    cin >> n >> q;
    fenwick_tree<int> bit(n);
    rep(i, q) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) {
            bit.add(x, y);
        }
        else {
            cout << bit.sum(x, y + 1) << "\n";
        }
    }
}