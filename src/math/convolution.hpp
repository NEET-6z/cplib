#pragma once
#include "./modint.hpp"

//acl
mint g=3;
void fft(vector<mint>& a, bool inv = false) {
    int n = si(a), s = __lg(n);
    static vector<mint> z, iz;
    while (si(z) <= s) {
        z.emplace_back(g.pow(mint(-1).val() / (1 << si(z))));
        iz.emplace_back(z.back().inv());
    }
    vector<mint> b(n);
    for (int i = 1; i <= s; i++) {
        int w = 1 << s - i;
        mint base = inv ? iz[i] : z[i], now = 1;
        for (int y = 0; y < n / 2; y += w) {
            rep(x, w) {
                auto l = a[y << 1 | x], r = now * a[y << 1 | x | w];
                b[y | x] = l + r, b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
}

vector<mint> convolution(vector<mint> a, vector<mint> b) {
    int n = si(a), m = si(b);
    if (!n or !m) return {};
    if (min(n, m) <= 30) {
        vector<mint> ans(n + m - 1);
        rep(i, n) rep(j, m) ans[i + j] += a[i] * b[j];
        return ans;
    }
    int N = n + m - 1;
    int z = __bit_ceil(unsigned(N));
    a.resize(z), b.resize(z);
    fft(a), fft(b);
    rep(i, z) a[i] *= b[i];
    fft(a, true);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (auto&& e : a) e *= iz;
    return a;
}