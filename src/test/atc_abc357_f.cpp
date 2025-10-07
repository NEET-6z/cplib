
#include "../BucketDecomposition.hpp"
#include "../modint.hpp"

struct Block {
    struct S {
        mint a = 0, b = 0, s = 0;
    };
    struct F {
        mint a = 0, b = 0;
    };
    S sum{};
    F lazy{};
    int n, id;
    vector<S> a;

    Block(int n_, int id_, vector<S> &a_): n(n_), id(id_), a(a_) {
        build();
    }
    S op(S l, S r) { return {l.a + r.a, l.b + r.b, l.s + r.s}; }
    void build() {
        sum = {};
        rep(i, n) {
            a[i].a += lazy.a;
            a[i].b += lazy.b;
            a[i].s = a[i].a * a[i].b;
            sum = op(sum, a[i]);
        }
        lazy = {};
    }

    S all_prod() { return sum; }

    S prod(int l, int r) {
        build();
        S ret = {0, 0, 0};
        for(int i = l; i < r; i++) {
            ret = op(ret, a[i]);
        }
        return ret;
    }

    void all_apply(F f) {
        lazy.a += f.a;
        lazy.b += f.b;
        sum.s += f.a * sum.b + f.b * sum.a + f.a * f.b * n;
        sum.a += f.a * n;
        sum.b += f.b * n;
        return;
    }
    void apply(int l, int r, F f) {
        for(int i = l; i < r; i++) {
            a[i].a += f.a;
            a[i].b += f.b;
            a[i].s += a[i].a * a[i].b;
        }
        build();
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<long> A(N), B(N);
    rep(i, N) cin >> A[i];
    rep(i, N) cin >> B[i];

    vector<Block::S> init(N);
    rep(i, N) init[i] = Block::S{A[i], B[i], A[i] * B[i]};
    BucketDecomposition<Block> D(init);
    while(Q--) {
        int t, l, r, x;
        cin >> t >> l >> r;
        l--;
        if(t == 1) {
            cin >> x;
            D.apply(l, r, {x, 0});
        }
        else if(t == 2) {
            cin >> x;
            D.apply(l, r, {0, x});
        }
        else {
            cout << D.prod(l, r).s.val() << "\n";
        }
    }
}