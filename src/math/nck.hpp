#include "../template.hpp"

template<int mod=998244353>
long Comb(int n, int k){
    if(k<0||k>n) return 0;
    static vector<long> fa(1, 1), ifa(1, 1);
    int sz=fa.size();
    if(sz<=n){
        fa.resize(n+1);
        ifa.resize(n+1);
        for(int i=sz;i<=n;i++)fa[i]=fa[i-1]*i%mod;
        
        long r=1;
        long a=fa[n];
        for(long n=mod-2;n;n>>=1, a=a*a%mod) if(n&1) r=r*a%mod;
        ifa[n]=r;
        for(int i=n;i>=sz;i--)ifa[i-1]=ifa[i]*i%mod;
    }

    return fa[n]*ifa[k]%mod*ifa[n-k]%mod;
}