#include "../template.hpp"

template <class T>
vector<vector<T>> mat_mul(vector<vector<T>> a,vector<vector<T>> b){
    vector ret(si(a),vector<T>(si(b[0])));
    rep(i,si(a)){
        rep(j,si(b[0])){
            rep(k,si(b)){
                ret[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    return ret;
}

template <class T>
vector<vector<T>> mat_pow(vector<vector<T>> a,long k){
    vector ret(si(a),vector<T>(si(a)));
    rep(i,si(a)) ret[i][i]=1;
    while(k>0){
        if(k&1) ret=mat_mul(a,ret);
        a=mat_mul(a,a);
        k>>=1;
    }
    return ret;
}