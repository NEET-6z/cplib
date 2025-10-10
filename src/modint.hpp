#pragma once
#include "template.hpp"

template<int mod = 998244353> struct modint {
    int x;
    constexpr modint(long x_ = 0): x(((x_ % mod)+mod)%mod) { }
    constexpr modint operator-() {
        auto res = *this;
        res.x = (x ? mod - x : 0);
        return res;
    }
    constexpr modint& operator+=(modint r) {
        if((x += r.x) >= mod) x -= mod;
        return *this;
    }
    constexpr modint& operator-=(modint r) {
        if((x -= r.x) < 0) x += mod;
        return *this;
    }
    constexpr modint& operator*=(modint r) {
        x = 1l * x * r.x % mod;
        return *this;
    }
    constexpr modint& operator/=(modint r) { return *this *= r.inv(); }
    constexpr friend modint operator+(modint a, modint b) { return a += b; }
    constexpr friend modint operator-(modint a, modint b) { return a -= b; }
    constexpr friend modint operator*(modint a, modint b) { return a *= b; }
    constexpr friend modint operator/(modint a, modint b) { return a /= b; }
    constexpr modint inv() const { return pow(mod - 2); }
    constexpr modint pow(long b) const {
        assert(0 <= b);
        modint a = *this, c = 1;
        while(b) {
            if(b & 1) c *= a;
            a *= a;
            b >>= 1;
        }
        return c;
    }
    constexpr int val() const { return x; }
    constexpr friend ostream& operator<<(ostream& os, const modint& m) { return os << m.val(); }
    constexpr friend istream& operator>>(istream& is, modint& m) {
        long v;
        is >> v;
        m = modint(v);
        return is;
    }
};