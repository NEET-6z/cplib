#include "monotone_minima.hpp"

//a凸b任意
template<typename T>
vector<T> concave_min_plus_convolution(vector<T> a,vector<T> b){
    if(a.empty()||b.empty()) return {};
    int n=si(a),m=si(b);
    auto g=[&](int i,int j)->T {
        return a[i-j]+b[j];
    };
    auto f=[&](int i,int j,int k)->bool {
        if(i<k) return true;
        if(i-j>=m) return false;
        return g(i,j)<=g(i,k);
    };
    vector<int> arm=monotone_minima(n+m-1,m,f);
    vector<T> ret(n+m-1);
    rep(i,n+m-1){
        ret[i]=g(i,arm[i]);
    }
    return ret;
}
template<typename T>
vector<T> concave_max_plus_convolution(vector<T> a,vector<T> b){
    if(a.empty()||b.empty()) return {};
    int n=si(a),m=si(b);
    auto g=[&](int i,int j)->T {
        return a[i-j]+b[j];
    };
    auto f=[&](int i,int j,int k)->bool {
        if(i<k) return true;
        if(i-j>=n) return false;
        return g(i,j)>=g(i,k);
    };
    vector<int> arm=monotone_minima(n+m-1,m,f);
    vector<T> ret(n+m-1);
    rep(i,n+m-1){
        ret[i]=g(i,arm[i]);
    }
    return ret;
}
