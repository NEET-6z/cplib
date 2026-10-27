// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sharp_p_subset_sum
#include <bits/stdc++.h>
using namespace std;
using V=vector<int>;
using ll=long long;
const int P=998244353, G=3;

ll pw(ll a, ll e){
    ll r=1;
    for(;e;e>>=1, a=a*a%P)
        if(e&1) r=r*a%P;
    return r;
}

void ntt(V& a, bool rev){
    int n=a.size();
    for(int i=1, j=0;i<n;i++){
        int b=n>>1;
        for(;j& b;b>>=1) j^=b;
        j^=b;
        if(i<j) swap(a[i], a[j]);
    }
    for(int l=2;l<=n;l<<=1){
        ll w0=pw(G, (P-1)/l);
        if(rev) w0=pw(w0, P-2);
        for(int i=0;i<n;i+=l){
            ll w=1;
            for(int j=0;j<l/2;j++, w=w*w0%P){
                int u=a[i+j], v=(ll)a[i+j+l/2]*w%P;
                a[i+j]=u+v;
                if(a[i+j]>=P) a[i+j]-=P;
                a[i+j+l/2]=u-v;
                if(a[i+j+l/2]<0) a[i+j+l/2]+=P;
            }
        }
    }
    if(rev){
        ll z=pw(n, P-2);
        for(int& x:a) x=x*z%P;
    }
}

V mul(V a, V b, int n=-1){
    if(a.empty()||b.empty()) return {};
    int m=a.size()+b.size()-1, z=1;
    while(z<m) z<<=1;
    a.resize(z);b.resize(z);
    ntt(a, 0);ntt(b, 0);
    for(int i=0;i<z;i++) a[i]=(ll)a[i]*b[i]%P;
    ntt(a, 1);
    a.resize(n<0?m:n);
    return a;
}

struct FPS {
    V iv;
    FPS(int n):iv(n+1){
        iv[1]=1;
        for(int i=2;i<=n;i++)
            iv[i]=P-(ll)(P/i)*iv[P%i]%P;
    }

    V inv(V a, int n){
        a.resize(n);
        V b(1, pw(a[0], P-2));
        while((int)b.size()<n){
            int k=min(n, (int)b.size()*2);
            V c=a;c.resize(k);
            V d=mul(c, b, k);
            for(int& x:d) x=x?P-x:0;
            d[0]+=2;
            if(d[0]>=P) d[0]-=P;
            b=mul(b, d, k);
        }
        return b;
    }

    V log(V a, int n){
        a.resize(n);
        V d(n-1);
        for(int i=1;i<n;i++) d[i-1]=(ll)a[i]*i%P;
        V c=mul(d, inv(a, n), n-1), r(n);
        for(int i=1;i<n;i++) r[i]=(ll)c[i-1]*iv[i]%P;
        return r;
    }

    V exp(const V& f){
        int n=f.size();
        V a(1, 1);
        while((int)a.size()<n){
            int k=min(n, (int)a.size()*2);
            V b=a;b.resize(k);
            V c=log(b, k);
            for(int i=0;i<k;i++) c[i]=(f[i]-c[i]+P)%P;
            if(++c[0]==P) c[0]=0;
            a=mul(a, c, k);
        }
        return a;
    }
};

V subset_sum(const V& s, int T){
    FPS fps(T);
    V cnt(T+1), f(T+1);
    for(int x:s) cnt[x]++;

    for(int k=1;k<=T;k++)
        if(cnt[k])
            for(int q=1;k*q<=T;q++){
                ll v=(ll)cnt[k]*fps.iv[q]%P;
                if(!(q&1)) v=(P-v)%P;
                int& x=f[k*q];
                x+=v;
                if(x>=P) x-=P;
            }


    return fps.exp(f);
}

int main(){
    int n, T;cin>>n>>T;
    V s(n);
    for(int& x:s) cin>>x;

    V ans=subset_sum(s, T);
    for(int t=1;t<=T;t++)
        cout<<ans[t]<<(t==T?'\n':' ');
}