#pragma once
#include "combination.hpp"

template<typename T>
struct Twelvefoldway:Combination<T> {
    using Combination<T>::Combination;

    // (玉を区別しない, 玉を区別する) x (箱を区別しない, 箱を区別する) x (1個以内, 制限無し, 1個以上)
    T f000(int n, int k){
        return (n<=k);
    }
    T f001(int n, int k){
        //分割数
        vector<vector<T>> dp(k+1,vector<T>(n+1,0));
        dp[0][0]=1;
        rep(i,k){
            rep(j,n+1){
                if(j-i-1>=0){
                    dp[i+1][j]=dp[i][j]+dp[i][j-i-1];
                }
                else{
                    dp[i+1][j]=dp[i][j];
                }
            }
        }
        return dp[k][n];

    }
    T f002(int n, int k){
        if(n<k) return 0;
        return f001(n-k,k);
    }
    T f010(int n, int k){
        return this->C(k,n);
    }
    T f011(int n, int k){
        return this->H(k,n);
    }

    T f012(int n, int k){
        return this->C(n-1,k-1);
    }

    T f100(int n, int k){
        return (n<=k);
    }
    T f101(int n, int k){
        //ベル数
        vector<T> b(k+2,0);
        rep(i,k+1) b[i+1]=b[i]+this->ifact(k)*(i%2*2-1);
        T ret=0;
        rep(i,k+1) ret+=T(i).pow(n)*this->ifact(i)*b[k+1-i];
        return ret;
    }
    T f102(int n, int k){
        //第二種スターリング数
        return f112(n,k)*this->ifact(k);
    }

    T f110(int n, int k){
        return this->P(k,n);
    }
    T f111(int n, int k){
        return T(k).pow(n);
    }
    T f112(int n, int k){
        if(n<k) return 0;
        T ret=0;
        rep(i,k+1) ret+=((k-i)%2*2-1)*this->C(k,i)*T(i).pow(n);
        return ret;
    }
};