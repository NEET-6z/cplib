#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907"
#include "../segtree/merge_sort_tree.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<string> S(N);
    rep(i, N) cin >> S[i];
    sort(all(S));
    vector<string> T = S;
    rep(i, N) reverse(all(T[i]));
    merge_sort_tree<string> tree(T);
    rep(i, Q) {
        string p, s;
        cin >> p >> s;
        int l = lower_bound(all(S), p) - S.begin();
        p += "|";
        int r = lower_bound(all(S), p) - S.begin();
        reverse(all(s));
        int ans = 0;
        ans -= tree.range_cnt(l, r, s);
        s += '|';
        ans += tree.range_cnt(l, r, s);
        cout << ans << "\n";
    }
}