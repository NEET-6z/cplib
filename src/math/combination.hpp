#pragma once
#include "../template.hpp"

template<typename T>
struct Combination {
    vector<T> fa{},ifa{};
    Combination(int n){
        fa.resize(n+1);
        ifa.resize(n+1);
        fa[0]=1;
        for(int i=1;i<=n;i++) fa[i]=fa[i-1]*i;
        ifa[n]=fa[n].inv();
        for(int i=n;i>=1;i--) ifa[i-1]=ifa[i]*i;
    }

    T fact(int n){
        if(n<0) return T(0);
        return fa[n];
    }

    T ifact(int n){
        if(n<0) return T(0);
        return ifa[n];
    }

    T C(int n,int k){
        if(k<0||k>n) return 0;
        return fact(n)*ifact(k)*ifact(n-k);
    }
    T H(int n,int k){
        if(n==0&&k==0) return 1;
        if(n<=0||k<0) return 0;
        return C(n+k-1,k);
    }
    T P(int n,int k){
        if(k<0||k>n) return 0;
        return fact(n)*ifact(n-k);
    }
    // n<=m+K
    T Kata(int n,int m,int k){
        if(n>m+k) return 0;
        return C(n+m,n)-C(n+m,n-k-1);
    };
    // n個の箱にk個の玉を入れる。各箱は最大でr個しか入れれない
    T limC(int n,int k,int r){
        T ret=0;
        rep(i,k/(r+1)+1){
            ret+=((i%2==0)*2-1)*C(n,i)
                  *C(n+k-1-i*(r+1),n-1);
        }
        return ret;
    }
};