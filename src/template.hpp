#pragma once
#include <bits/stdc++.h>
using namespace std;
using i128=__int128_t;
#define si(a) (long)a.size()
#define lbi(a,x) (lower_bound(a.begin(),a.end(),x)-a.begin())
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rep(i,n) for(int i=0;i<(int)(n);++i)
template<typename S,typename F> bool chmin(S&a,F b){return b<a?(a=b,1):0;}
template<typename S,typename F> bool chmax(S&a,F b){return b>a?(a=b,1):0;}
bool _=(ios::sync_with_stdio(0),cin.tie(0),cout<<fixed<<setprecision(16),0);