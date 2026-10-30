#pragma once
#include "../template.hpp"

//acl(template)
template<typename T> constexpr pair<T, T> inv_gcd(T a, T b){
    a=(a%b+b)%b;
    if(a==0) return {b, 0};
    T s=b, t=a;
    T m0=0, m1=1;

    while(t){
        T u=s/t;
        s-=t*u;
        m0-=m1*u;
        auto tmp=s;
        s=t;
        t=tmp;
        tmp=m0;
        m0=m1;
        m1=tmp;
    }
    if(m0<0) m0+=b/s;
    return {s, m0};
}

template<typename T> T inv_mod(T x, T m){
    assert(1<=m);
    auto z=inv_gcd(x, m);
    assert(z.fi==1);
    return z.se;
}

template<typename T> pair<T, T> crt(const vector<T>& r, const vector<T>& m){
    assert(r.size()==m.size());
    int n=si(r);
    T r0=0, m0=1;
    for(int i=0;i<n;i++){
        assert(1<=m[i]);
        T r1=(r[i]%m[i]+m[i])%m[i], m1=m[i];
        if(m0<m1){
            swap(r0, r1);
            swap(m0, m1);
        }
        if(m0%m1==0){
            if(r0%m1!=r1) return {0, 0};
            continue;
        }
        T g, im;
        tie(g, im)=inv_gcd(m0, m1);

        T u1=(m1/g);
        if((r1-r0)%g) return {0, 0};

        T x=(r1-r0)/g%u1*im%u1;
        r0+=x*m0;
        m0*=u1;
        if(r0<0) r0+=m0;
    }
    return {r0, m0};
}


template<typename T>
T garner(const vector<T>& a, vector<T> p, const T mod){
    const int sz=si(a);
    vector<T> kp(sz+1, 0), rmult(sz+1, 1);
    p.push_back(mod);
    for(int i=0;i<sz;++i){
        T x=(a[i]-kp[i])%p[i];
        if(x<0) x+=p[i];
        x=x*inv_mod(rmult[i], p[i])%p[i];

        for(int j=i+1;j<sz+1;++j){
            kp[j]=(kp[j]+rmult[j]*x)%p[j];
            rmult[j]=rmult[j]*p[i]%p[j];
        }
    }
    return kp[sz];
}
