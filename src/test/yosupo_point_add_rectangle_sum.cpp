#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../segtree/segtree2d.hpp"
long op(long l, long r) { return l + r; }
long e() { return 0; }

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<array<int, 5>> qu(N + Q);
    segtree_2d<int, long, op, e> seg;
    rep(i, N) {
        int x, y, w;
        cin >> x >> y >> w;
        qu[i] = {0, x, y, w};
        seg.add_point(x, y);
    }
    rep(i, Q) {
        int t;
        cin >> t;
        if(t == 0) {
            int x, y, w;
            cin >> x >> y >> w;
            qu[i + N] = {0, x, y, w};
            seg.add_point(x, y);
        }
        else {
            int l, d, r, u;
            cin >> l >> d >> r >> u;
            qu[i + N] = {1, l, d, r, u};
        }
    }

    seg.build();
    for(auto a: qu) {
        if(a[0] == 0) {
            seg.apply(a[1], a[2], a[3]);
        }
        else {
            cout << seg.range(a[1], a[3], a[2], a[4]) << "\n";
        }
    }
}