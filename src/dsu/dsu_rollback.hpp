#include "../template.hpp"

struct dsu_rollback {
    vector<int> p;
    vector<pair<int,int>> st;
    dsu_rollback(int n):p(n,-1){}
    bool same(int a,int b){return leader(a)==leader(b);}
    int size(int x){return -p[leader(x)];}
    int leader(int x){return p[x]<0?x:leader(p[x]);}
    int time(){return si(st);}
    void rollback(int t){
        for(int i=time();i-->t;) p[st[i].first]=st[i].second;
        st.resize(t);
    }
    int merge(int a,int b){
        a=leader(a),b=leader(b);
        if(a==b) return a;
        if(p[a]>p[b]) swap(a,b);
        st.push_back({a,p[a]});
        st.push_back({b,p[b]});
        p[a]+=p[b];
        p[b]=a;
        return a;
    }
};