#pragma once
#include <bits/stdc++.h>
using namespace std;
#define si(a) (long)a.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rep(i,n) for(long i=0;i<(long)(n);++i)
template<typename T>bool chmin(T&a,T b){return b<a?(a=b,1):0;}
template<typename T>bool chmax(T&a,T b){return b>a?(a=b,1):0;}
struct _ {
   _() { cin.tie(0)->sync_with_stdio(0), cout.tie(0), cout << fixed << setprecision(16); }
} __;