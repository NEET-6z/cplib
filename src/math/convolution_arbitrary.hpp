#include "./modint.hpp"
#include "./convolution.hpp"
#include "./crt.hpp"


template<int P>
array<vector<modint<P>>, 3> split_conv(const vector<long>& a, const vector<long>& b){
    using mint=modint<P>;
    const long mask=(1LL<<30)-1;
    int n=si(a), m=si(b);
    vector<mint> a0(n), a1(n), as(n), b0(m), b1(m), bs(m);
    rep(i, n){ a0[i]=a[i]&mask; a1[i]=a[i]>>30; as[i]=a0[i]+a1[i]; }
    rep(i, m){ b0[i]=b[i]&mask; b1[i]=b[i]>>30; bs[i]=b0[i]+b1[i]; }
    auto c00=convolution(a0, b0);
    auto c11=convolution(a1, b1);
    auto cs=convolution(as, bs);
    rep(i, n+m-1) cs[i]-=c00[i]+c11[i];
    return {c00, cs, c11};
}

vector<long> convolution_arbitrary(const vector<long>& a, const vector<long>& b, long mod){
    int n=si(a), m=si(b);
    if(!n||!m) return {};
    auto r0=split_conv<998244353>(a, b);
    auto r1=split_conv<167772161>(a, b);
    auto r2=split_conv<469762049>(a, b);
    const vector<i128> p={998244353, 167772161, 469762049};
    const i128 M=mod;
    const i128 s30=(1LL<<30)%M, s60=(i128(1)<<60)%M;
    vector<long> ans(n+m-1);
    rep(i, n+m-1){
        i128 v[3];
        rep(k, 3){
            v[k]=garner<i128>({r0[k][i].val(), r1[k][i].val(), r2[k][i].val()}, p, M);
        }
        ans[i]=(long)((v[0]+v[1]*s30%M+v[2]*s60%M)%M);
    }
    return ans;
}
