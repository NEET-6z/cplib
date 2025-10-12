#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#include "../dsu/dsu.hpp"
int main() {
    int n, q;
    cin >> n >> q;
    dsu uf(n);
    rep(i, q) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) {
            uf.merge(x, y);
        }
        else {
            cout << uf.same(x, y) << "\n";
        }
    }
}