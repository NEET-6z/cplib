#include "../template.hpp"
#include <atcoder/convolution>

template<class T, class Conv> struct FormalPowerSeries: vector<T> {
    using vector<T>::vector;
    using vector<T>::operator=;
    using F = FormalPowerSeries;

    F operator-() const {
        F res(*this);
        for(auto &e: res) e = -e;
        return res;
    }
    F &operator*=(const T &g) {
        for(auto &e: *this) e *= g;
        return *this;
    }
    F &operator/=(const T &g) {
        assert(g != T(0));
        *this *= g.inv();
        return *this;
    }
    F &operator+=(const F &g) {
        int n = (*this).size(), m = g.size();
        rep(i, min(n, m))(*this)[i] += g[i];
        return *this;
    }
    F &operator-=(const F &g) {
        int n = (*this).size(), m = g.size();
        rep(i, min(n, m))(*this)[i] -= g[i];
        return *this;
    }
    F &operator<<=(const int d) {
        int n = (*this).size();
        (*this).insert((*this).begin(), d, 0);
        (*this).resize(n);
        return *this;
    }
    F &operator>>=(const int d) {
        int n = (*this).size();
        (*this).erase((*this).begin(), (*this).begin() + min(n, d));
        (*this).resize(n);
        return *this;
    }
    F inv(int d = -1) const {
        int n = (*this).size();
        assert(n != 0 && (*this)[0] != 0);
        if(d == -1) d = n;
        assert(d > 0);
        F res{(*this)[0].inv()};
        while(res.size() < d) {
            int m = size(res);
            F f(begin(*this), begin(*this) + min(n, 2 * m));
            F r(res);
            f.resize(2 * m), atcoder::internal::butterfly(f);
            r.resize(2 * m), atcoder::internal::butterfly(r);
            rep(i, 2 * m) f[i] *= r[i];
            atcoder::internal::butterfly_inv(f);
            f.erase(f.begin(), f.begin() + m);
            f.resize(2 * m), atcoder::internal::butterfly(f);
            rep(i, 2 * m) f[i] *= r[i];
            atcoder::internal::butterfly_inv(f);
            T iz = T(2 * m).inv();
            iz *= -iz;
            rep(i, m) f[i] *= iz;
            res.insert(res.end(), f.begin(), f.begin() + m);
        }
        return {res.begin(), res.begin() + d};
    }

    // fast: FMT-friendly modulus only
    F &operator*=(const F &g) {
        int n = (*this).size();
        *this = atcoder::convolution(*this, g);
        (*this).resize(n);
        return *this;
    }
    F &operator/=(const F &g) {
        int n = (*this).size();
        *this = atcoder::convolution(*this, g.inv(n));
        (*this).resize(n);
        return *this;
    }

    // naive
    //   F &operator*=(const F &g) {
    //     int n = (*this).size(), m = g.size();
    //     for(int i=n;i--;) {
    //       (*this)[i] *= g[0];
    //       for(int j=1;j<min(i+1, m);j++) (*this)[i] += (*this)[i-j] * g[j];
    //     }
    //     return *this;
    //   }
    //   F &operator/=(const F &g) {
    //     assert(g[0] != T(0));
    //     T ig0 = g[0].inv();
    //     int n = (*this).size(), m = g.size();
    //     rep(i, n) {
    //       for(int j=1;j<min(i+1, m);j++) (*this)[i] -= (*this)[i-j] * g[j];
    //       (*this)[i] *= ig0;
    //     }
    //     return *this;
    //   }

    // sparse
    F &operator*=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        if(d == 0) g.erase(g.begin());
        else c = 0;
        for(int i = n; i--;) {
            (*this)[i] *= c;
            for(auto &[j, b]: g) {
                if(j > i) break;
                (*this)[i] += (*this)[i - j] * b;
            }
        }
        return *this;
    }
    F &operator/=(vector<pair<int, T>> g) {
        int n = (*this).size();
        auto [d, c] = g.front();
        assert(d == 0 && c != T(0));
        T ic = c.inv();
        g.erase(g.begin());
        rep(i, n) {
            for(auto &[j, b]: g) {
                if(j > i) break;
                (*this)[i] -= (*this)[i - j] * b;
            }
            (*this)[i] *= ic;
        }
        return *this;
    }

    // multiply and divide (1 + cz^d)
    void multiply(const int d, const T c) {
        int n = (*this).size();
        if(c == T(1))
            for(int i = n - d; i--;) (*this)[i + d] += (*this)[i];
        else if(c == T(-1))
            for(int i = n - d; i--;) (*this)[i + d] -= (*this)[i];
        else
            for(int i = n - d; i--;) (*this)[i + d] += (*this)[i] * c;
    }
    void divide(const int d, const T c) {
        int n = (*this).size();
        if(c == T(1)) rep(i, n - d)(*this)[i + d] -= (*this)[i];
        else if(c == T(-1)) rep(i, n - d)(*this)[i + d] += (*this)[i];
        else rep(i, n - d)(*this)[i + d] -= (*this)[i] * c;
    }

    T eval(const T &a) const {
        T x(1), res(0);
        for(auto e: *this) res += e * x, x *= a;
        return res;
    }

    void shrink() {
        while(si(*this) && (*this).back() == 0) (*this).pop_back();
    }
    F diff() const {
        int n = size();
        F res(n);
        for(int i = 1; i < n; i++) res[i - 1] = (*this)[i] * T(i);
        return res;
    }

    F integral() const {
        int n = size();
        F res(n);
        for(int i = 1; i < n; i++) res[i] = (*this)[i - 1] / T(i);
        return res;
    }

    F log(int d = -1) const {
        int n = size();
        if(d == -1) d = n;
        F res = diff() * inv(d);
        res = res.integral();
        res.resize(d);
        return res;
    }

    F exp(int d = -1) const {
        int n = size();
        if(d == -1) d = n;
        F res{T(1)};
        while(res.size() < d) {
            int m = res.size();
            F f(begin(*this), begin(*this) + min(n, 2 * m));
            F g = res.log(2 * m);
            f -= g;
            f[0] += T(1);
            res *= f;
            res.resize(2 * m);
        }
        res.resize(d);
        return res;
    }

    F pow(long k, int d = -1) const {
        int n = size();
        if(d == -1) d = n;
        if(k == 0) {
            F res(d);
            res[0] = T(1);
            return res;
        }
        int i = 0;
        while(i < n && (*this)[i] == T(0)) i++;
        if(i == n || (long)i * k >= d) return F(d);
        T c = (*this)[i];
        F f(begin(*this) + i, end());
        f /= c;
        F res = (f.log(d - i * k) * T(k)).exp(d - i * k);
        res *= c.pow(k);
        res <<= i * k;
        res.resize(d);
        return res;
    }


    F operator*(const T &g) const { return F(*this) *= g; }
    F operator/(const T &g) const { return F(*this) /= g; }
    F operator+(const F &g) const { return F(*this) += g; }
    F operator-(const F &g) const { return F(*this) -= g; }
    F operator<<(const int d) const { return F(*this) <<= d; }
    F operator>>(const int d) const { return F(*this) >>= d; }
    F operator*(const F &g) const { return F(*this) *= g; }
    F operator/(const F &g) const { return F(*this) /= g; }
    F operator*(vector<pair<int, T>> g) const { return F(*this) *= g; }
    F operator/(vector<pair<int, T>> g) const { return F(*this) /= g; }
};