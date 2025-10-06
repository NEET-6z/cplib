// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D
#include "../dual_segtree.hpp"

using F = pair<int, int>;
F id() { return {-1, INT_MAX}; }
void cmpo(const F& f, F& g) {
    if(g.fi < f.fi) g = f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    dual_segtree<F, id, cmpo> seg(n);
    rep(qi, q) {
        int o;
        cin >> o;
        if(o == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            t++;
            seg.apply(s, t, {qi, x});
        }
        else {
            int i;
            cin >> i;
            cout << seg.get(i).se << "\n";
        }
    }
}