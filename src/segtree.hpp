#include<bits/stdc++.h>
using namespace std;

template<class S,S(*op)(S,S),S(*e)()>struct segtree{
  int n;vector<S> t;
  segtree(int n_): n(__bit_ceil(n_)), t(n*2, e()) {}
  void set(int i,S x){for(t[i+=n]=x;i>>=1;)t[i]=op(t[i*2],t[i*2+1]);}
  S operator[](int k){return t[k+n];}
  S prod(int l,int r){
    S L=e(),R=e();
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
      if(l&1)L=op(L,t[l++]);
      if(r&1)R=op(t[--r],R);
    }
    return op(L,R);
  }
};
