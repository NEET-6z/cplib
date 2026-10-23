#include "../template.hpp"

vector<int> boyer_moore_generalized(vector<int> a, int k){
    vector<int> val(k, 0), cnt(k, 0);

    for_each(all(a), [&](int& x) {
        rep(i, k){
            if(cnt[i]&&val[i]==x){
                cnt[i]++;
                return;
            }
        }
        rep(i, k){
            if(!cnt[i]){
                val[i]=x;
                cnt[i]=1;
                return;
            }
        }
        rep(i, k) cnt[i]--;
    });
    vector<int> ret;
    rep(i, k) if(cnt[i]>0){
        int s=0;
        for(int x: a)
            if(val[i]==x) s++;
        if(s>si(a)/(k+1)) ret.push_back(val[i]);
    }
    sort(all(ret));
    ret.erase(unique(all(ret)), ret.end());
    return ret;
}