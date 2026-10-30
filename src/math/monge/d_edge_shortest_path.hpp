#include "../../template.hpp"

using ll=long;

// 頂点0..n, 辺i->j (i<j) の重み w(i,j) がMonge。0->nのちょうどd辺(1<=d<=n)の最短路長
//O(nlognlogB) Bは重みの絶対値の最大以上。dpの値がB*nまで膨らむ
template<class F> ll d_edge_shortest_path(int n, int d, F w, ll B=1e12){
    vector<ll> dv(n+1);
    vector<int> dc(n+1), c(n+2), s(n+2);
    auto lt=[&](int i, int k, int p){
        ll a=dv[i]+w(i, p), b=dv[k]+w(k, p);
        return a<b||(a==b&&dc[i]<dc[k]);
    };
    auto run=[&](ll lam){
        int h=0, t=1;c[0]=0;s[0]=1;dv[0]=0;dc[0]=0;
        for(int j=1;j<=n;j++){
            while(h+1<t&&s[h+1]<=j) h++;
            int b=c[h];
            dv[j]=dv[b]+w(b, j)+lam;dc[j]=dc[b]+1;
            if(j==n) break;
            while(t>h){
                int p=max(s[t-1], j+1);
                if(lt(j, c[t-1], p)) t--;else break;
            }
            if(t==h){c[t]=j;s[t++]=j+1;continue;}
            int lo=max(s[t-1], j+1), hi=n+1;
            while(hi-lo>1){
                int m=(lo+hi)>>1;
                (lt(j, c[t-1], m)?hi:lo)=m;
            }
            if(hi<=n){c[t]=j;s[t++]=hi;}
        }
    };
    ll lo=-B, hi=B, last=LLONG_MIN;
    while(lo<hi){
        ll m=lo+(hi-lo)/2;
        run(m);last=m;
        if(dc[n]==d) return dv[n]-m*d;
        if(dc[n]<d) hi=m;else lo=m+1;
    }
    if(last!=lo) run(lo);
    return dv[n]-lo*d;
}


using P=pair<ll, int>;
// 各λでのDPでLarschを使いO(N)で全体O(NlogB)
template<class F> ll d_edge_shortest_path_larsch(int n, int d, F w, ll B=1e12){
    vector<ll> dv(n+1);vector<int> dc(n+1);
    int L=0;while((n>>L)>=1) L++;
    vector<vector<int>> col(L), par(L);
    vector<int> len(L), prv(L), xs(L);
    for(int l=0;l<L;l++){
        col[l].resize(n>>l);par[l].resize(n>>l);
    }
    iota(col[0].begin(), col[0].end(), 0);

    auto val=[&](int l, int t, int c){
        int R=((t+1)<<l)-1;
        return P(dv[c]+w(c, R+1), dc[c]);
    };

    auto ask=[&](auto&& self, int l, int r)->int {
        int nr=n>>l;
        if(l>0){
            auto& C=col[l];auto& Pp=par[l];int& ln=len[l];
            auto push=[&](int p){
                int c=col[l-1][p];
                while(ln>r){
                    if(val(l, ln-1, c)<val(l, ln-1, C[ln-1])) ln--;else break;
                }
                if(ln<nr){C[ln]=c;Pp[ln]=p;ln++;}
            };
            if(r>0) push(2*r-1);
            push(2*r);
        }
        int q;
        if(!(r&1)){
            int hi=min(r, len[l]-1);
            if(r+1<nr){int x=self(self, l+1, r>>1);xs[l]=x;hi=min(hi, x);}
            int lo=r?prv[l]:0;
            q=lo;P best=val(l, r, col[l][lo]);
            for(int p=lo+1;p<=hi;p++){
                P v=val(l, r, col[l][p]);
                if(v<best){best=v;q=p;}
            }
        }
        else{
            q=xs[l];
            if(r<len[l]&&val(l, r, col[l][r])<val(l, r, col[l][q])) q=r;
        }
        prv[l]=q;
        return l?par[l][q]:q;
    };

    auto run=[&](ll lam){
        len[0]=n;for(int l=1;l<L;l++) len[l]=0;
        dv[0]=0;dc[0]=0;
        for(int r=0;r<n;r++){
            int b=ask(ask, 0, r);
            dv[r+1]=dv[b]+w(b, r+1)+lam;
            dc[r+1]=dc[b]+1;
        }
    };

    ll lo=-B, hi=B, last=LLONG_MIN;
    while(lo<hi){
        ll m=lo+(hi-lo)/2;
        run(m);last=m;
        if(dc[n]==d) return dv[n]-m*d;
        if(dc[n]<d) hi=m;else lo=m+1;
    }
    if(last!=lo) run(lo);
    return dv[n]-lo*d;
}
