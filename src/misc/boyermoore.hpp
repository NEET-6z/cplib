#include "../template.hpp"

inline vector<int> boyer_moore_generalized(const vector<int>& a, int k) {
    vector<int> c(k, 0), cnt(k, 0);
    for(int x: a) {
        bool f = false;
        rep(i, k) if(cnt[i] > 0 && c[i] == x) {
            cnt[i]++;
            f = true;
            break;
        }
        if(f) continue;
        rep(i, k) if(cnt[i] == 0) {
            c[i] = x;
            cnt[i] = 1;
            f = true;
            break;
        }
        if(f) continue;
        rep(i, k) cnt[i]--;
    }
    vector<int> ret;
    rep(i, k) if(cnt[i] > 0) {
        int s = 0;
        for(int x: a)
            if(x == c[i]) s++;
        if(s > si(a) / (k + 1)) ret.push_back(c[i]);
    }
    sort(all(ret));
    ret.erase(unique(all(ret)), ret.end());
    return ret;
}