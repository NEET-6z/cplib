#include "../template.hpp"

//https://qandori.github.io/cp-library/components/bitwise_zeta.hpp.html
//inverse: Mebius, superset:上位集合
template <bool inverse=false, bool superset=false, class T>
void bitwise_zeta(vector<T>& a){
    assert(a.empty()||has_single_bit(a.size()));
    for(size_t half=1;half<a.size();half*=2)
        for(size_t start=0;start<a.size();start+=2*half)
            for(size_t j=0;j<half;++j){
                T& to=a[start+j+(superset?0:half)];
                const T& from=a[start+j+(superset?half:0)];
                if constexpr(inverse) to-=from;
                else to+=from;
            }
}

vector<int> subset_zeta(int n, vector<int> a){
    rep(j, n){
        int b=1<<j;
        rep(i, 1<<n){
            if(i&b) a[i]+=a[i^b];
        }
    }
    return a;
}
vector<int> subset_mobius(int n, vector<int> a){
    rep(j, n){
        int b=1<<j;
        rep(i, 1<<n){
            if(i&b){
                a[i]-=a[i^b];
            }
        }
    }
    return a;
}
vector<int> superset_zeta(int n, vector<int> a){
    rep(j, n){
        int b=1<<j;
        rep(i, 1<<n){
            if((i&b)==0){
                a[i]+=a[i|b];
            }
        }
    }
    return a;
}

vector<int> superset_mobius(int n, vector<int> a){
    rep(j, n){
        int b=1<<j;
        rep(i, 1<<n){
            if((i&b)==0){
                a[i]-=a[i|b];
            }
        }
    }
    return a;
}

vector<int> or_convolution(int n, vector<int> A, vector<int> B){
    vector<int> ZA=subset_zeta(n, A);
    vector<int> ZB=subset_zeta(n, B);
    vector<int> D(1<<n);
    for(int u=0;u<(1<<n);++u) D[u]=ZA[u]*ZB[u];
    vector<int> C=subset_mobius(n, D);
    return C;
}
vector<int> and_convolution(int n, vector<int> A, vector<int> B){
    vector<int> ZA=superset_zeta(n, A);
    vector<int> ZB=superset_zeta(n, B);
    vector<int> D(1<<n);
    for(int u=0;u<(1<<n);++u) D[u]=ZA[u]*ZB[u];
    vector<int> C=superset_mobius(n, D);
    return C;
}