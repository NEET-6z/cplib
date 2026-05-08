#include "../../template.hpp"

template<typename T>
vector<T> shortest_path(int N,const function<T(int,int)>& f){
    vector<T> dp(N,numeric_limits<T>::max()/2);
    dp[0]=0;
    vector<int> arm(N);
    auto update=[&](int i,int j)->void {
        if(i<=j) return;
        if(chmin(dp[i],dp[j]+f(j,i))){
            arm[i]=j;
        }
    };
    auto dfs=[&](auto dfs,int l,int r)->void {
        if(r-l<=1) return;
        int m=(l+r)/2;
        for(int j=arm[l];j<=arm[r];j++) update(m,j);
        dfs(dfs,l,m);
        for(int j=l+1;j<=m;j++) update(r,j);
        dfs(dfs,m,r);
    };
    dfs(dfs,0,N-1);
}