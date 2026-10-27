#include "./intersect.hpp"

vector<vector<pair<int,S>>> segment_arrangement(const vector<Line>& ss, vector<P>& ps){
    ps.clear();
    int n=ss.size();
    vector<P> cand;
    rep(i, n){
        cand.push_back(ss[i].a);
        cand.push_back(ss[i].b);
        for(int j=i+1;j<n;++j)
            if(intersect_ss(ss[i], ss[j]) && !is_parallel(ss[i], ss[j]))
                cand.push_back(crosspoint_ll(ss[i], ss[j]));
    }
    sort(all(cand), [](const P& x, const P& y){return x.real()<y.real();});
    for(const P& p: cand){
        bool dup=false;
        for(int k=(int)ps.size()-1; k>=0 && p.real()-ps[k].real()<=EPS; --k)
            if(abs(p-ps[k])<=EPS){dup=true; break;}
        if(!dup) ps.push_back(p);
    }

    vector<vector<pair<int,S>>> g(ps.size());
    set<pair<int,int>> used;
    rep(i, n){
        vector<pair<S,int>> list;
        rep(j, ps.size())
            if(intersect_sp(ss[i], ps[j]))
                list.emplace_back(norm(ps[j]-ss[i].a), j);
        sort(all(list));
        for(int j=0; j+1<(int)list.size(); ++j){
            int a=list[j].second, b=list[j+1].second;
            if(a>b) swap(a, b);
            if(!used.insert({a, b}).second) continue;
            g[a].emplace_back(b, abs(ps[a]-ps[b]));
            g[b].emplace_back(a, abs(ps[a]-ps[b]));
        }
    }
    return g;
}