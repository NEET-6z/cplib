#include "../template.hpp"

using ld=long double;
const ld INF=1e18;

using pld=pair<ld, ld>;
pair<ld, vector<pld>> cp_rec(vector<pld>& ps, int i, int n){ //最近点対距離
    if(n==0) return {INF, {}};
    if(n<=1) return {INF, {ps[i]}};
    int m=n/2;
    ld x=ps[i+m].first;
    auto [d1, qs1]=cp_rec(ps, i, m);
    auto [d2, qs2]=cp_rec(ps, i+m, n-m);
    ld d=min(d1, d2);
    vector<pld> qs;
    qs.reserve(n);
    int s=0, t=0;
    while(s<m&&t<n-m){
        if(qs1[s].second<qs2[t].second) qs.push_back(qs1[s++]);
        else qs.push_back(qs2[t++]);
    }
    while(s<m) qs.push_back(qs1[s++]);
    while(t<n-m) qs.push_back(qs2[t++]);
    vector<pld> b;

    rep(k, n){
        ld ax=qs[k].first;
        ld ay=qs[k].second;
        if(abs(ax-x)>=d) continue;
        for(int j=(int)b.size();j--;){
            ld dx=ax-b[j].first;
            ld dy=ay-b[j].second;
            if(dy>=d) break;
            d=min(d, sqrt(dx*dx+dy*dy));
        }
        b.push_back(qs[k]);
    }
    return {d, qs};
}

ld closest_pair(vector<pld> ps){
    sort(ps.begin(), ps.end());
    int n=ps.size();
    if(n<2) return INF;
    return cp_rec(ps, 0, n).first;
}