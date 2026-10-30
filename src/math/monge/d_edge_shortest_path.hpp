#include "../../template.hpp"

using ll=long;
using P=pair<ll, int>;

// 頂点0..n, 辺i->j (i<j) の重み w(i,j) がMonge。0->nのちょうどd辺(1<=d<=n)の最短路長
//O(nlognlogB) Bは重みの絶対値の最大以上。dpの値がB*nまで膨らむ
template<class F> ll d_edge_shortest_path(int n, int d, F w, ll B=1e12){
    vector<P> dp(n+1);
    auto run=[&](ll lam){
        auto f=[&](int i, int j){return P(dp[i].fi+w(i, j)+lam, dp[i].se+1);};
        vector<int> c(n+1), s(n+1);int h=0, t=1;c[0]=0;s[0]=1;
        for(int j=1;j<=n;j++){
            while(h+1<t&&s[h+1]<=j) h++;
            dp[j]=f(c[h], j);
            if(j==n) break;
            while(t>h){
                int p=max(s[t-1], j+1);
                if(f(j, p)<f(c[t-1], p)) t--;else break;
            }
            if(t==h){c[t]=j;s[t++]=j+1;continue;}
            int lo=max(s[t-1], j+1), hi=n+1;
            while(hi-lo>1){
                int m=(lo+hi)/2;
                (f(j, m)<f(c[t-1], m)?hi:lo)=m;
            }
            if(hi<=n){c[t]=j;s[t++]=hi;}
        }
    };
    ll lo=-B, hi=B;
    while(lo<hi){
        ll m=lo+(hi-lo)/2;
        run(m);
        (dp[n].se<=d?hi:lo)=(dp[n].se<=d?m:m+1);
    }
    run(lo);
    return dp[n].fi-lo*d;
}

//復元
template<class F> vector<int> d_edge_shortest_path_restore(int n, int d, F w, ll B=1e12){
    vector<P> dp(n+1);vector<int> pr(n+1);
    auto run=[&](ll lam, int g){ // g=1:同点なら辺数最小, g=-1:辺数最大
        auto f=[&](int i, int j){return P(dp[i].fi+w(i, j)+lam, dp[i].se+g);};
        vector<int> c(n+1), s(n+1);int h=0, t=1;c[0]=0;s[0]=1;
        for(int j=1;j<=n;j++){
            while(h+1<t&&s[h+1]<=j) h++;
            dp[j]=f(c[h], j);pr[j]=c[h];
            if(j==n) break;
            while(t>h){
                int p=max(s[t-1], j+1);
                if(f(j, p)<f(c[t-1], p)) t--;else break;
            }
            if(t==h){c[t]=j;s[t++]=j+1;continue;}
            int lo=max(s[t-1], j+1), hi=n+1;
            while(hi-lo>1){
                int m=(lo+hi)/2;
                (f(j, m)<f(c[t-1], m)?hi:lo)=m;
            }
            if(hi<=n){c[t]=j;s[t++]=hi;}
        }
    };
    auto get=[&]{
        vector<int> v{n};
        while(v.back()) v.push_back(pr[v.back()]);
        reverse(all(v));return v;
    };
    ll lo=-B, hi=B;
    while(lo<hi){
        ll m=lo+(hi-lo)/2;
        run(m, 1);
        if(dp[n].se<=d) hi=m;else lo=m+1;
    }
    run(lo, 1);auto A=get();int k=si(A)-1;
    if(k==d) return A;
    run(lo, -1);auto C=get();int m=si(C)-1, s=m-d;
    int i=0;
    while(C[i+1+s]>=A[i+1]) i++;
    vector<int> r(A.begin(), A.begin()+i+1);
    r.insert(r.end(), C.begin()+i+s+1, C.end());
    return r;
}