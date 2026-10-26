#include "../math/convolution.hpp"

template<typename mint>
void fft(vector<mint>& a, bool inv=false){
    mint g=3;
    int n=(int)a.size(), s=__lg(n);
    static vector<mint> z, iz;
    while((int)z.size()<=s){
        z.emplace_back(g.pow(mint(-1).val()>>(z.size())));
        iz.emplace_back(z.back().inv());
    }
    vector<mint> b(n);
    for(int i=1;i<=s;i++){
        int w=1<<s-i;
        mint base=inv?iz[i]:z[i], now=1;
        for(int y=0;y<n/2;y+=w){
            rep(x, w){
                auto l=a[y<<1|x], r=now*a[y<<1|x|w];
                b[y|x]=l+r, b[y|x|n>>1]=l-r;
            }
            now*=base;
        }
        swap(a, b);
    }
}

template<typename mint>
vector<mint> convolution(vector<mint> a, vector<mint> b){
    int n=si(a), m=si(b);
    if(!n||!m) return {};
    if(min(n, m)<=30){
        vector<mint> ans(n+m-1);
        rep(i, n) rep(j, m) ans[i+j]+=a[i]*b[j];
        return ans;
    }
    int N=n+m-1;
    int z=1;
    while(z<N) z<<=1;
    a.resize(z), b.resize(z);
    fft(a), fft(b);
    rep(i, z) a[i]*=b[i];
    fft(a, true);
    a.resize(n+m-1);
    mint iz=mint(z).inv();
    for(auto&& e : a) e*=iz;
    return a;
}
template<class T>
struct FormalPowerSeries:vector<T> {
    using vector<T>::vector;
    using vector<T>::operator=;
    using F=FormalPowerSeries;

    F operator-()const {
        F res(*this);
        for(auto& e : res) e=-e;
        return res;
    }
    F &operator*=(const T& g){
        for(auto& e : *this) e*=g;
        return *this;
    }
    F &operator/=(const T& g){
        assert(g!=T(0));
        *this*=g.inv();
        return *this;
    }
    F &operator+=(const F& g){
        int n=(*this).size(), m=g.size();
        rep(i, min(n, m)) (*this)[i]+=g[i];
        return *this;
    }
    F &operator-=(const F& g){
        int n=(*this).size(), m=g.size();
        rep(i, min(n, m)) (*this)[i]-=g[i];
        return *this;
    }
    F &operator<<=(const int d){
        int n=(*this).size();
        (*this).insert((*this).begin(), d, 0);
        (*this).resize(n);
        return *this;
    }
    F &operator>>=(const int d){
        int n=(*this).size();
        (*this).erase((*this).begin(), (*this).begin()+min(n, d));
        (*this).resize(n);
        return *this;
    }
    F inv(int d=-1)const {
        int n=(*this).size();
        assert(n!=0&&(*this)[0]!=0);
        if(d==-1) d=n;
        assert(d>0);
        F res{(*this)[0].inv()};
        while(res.size()<d){
            int m=size(res);
            F f(begin(*this), begin(*this)+min(n, 2*m));
            F r(res);
            f.resize(2*m), fft(f);
            r.resize(2*m), fft(r);
            rep(i, 2*m) f[i]*=r[i];
            fft(f, true);
            f.erase(f.begin(), f.begin()+m);
            f.resize(2*m), fft(f);
            rep(i, 2*m) f[i]*=r[i];
            fft(f, true);
            T iz=T(2*m).inv();iz*=-iz;
            rep(i, m) f[i]*=iz;
            res.insert(res.end(), f.begin(), f.begin()+m);
        }
        return {res.begin(), res.begin()+d};
    }

    // // fast: FMT-friendly modulus only
    // F &operator*=(const F &g) {
    //   int n = (*this).size();
    //   *this = convolution(*this, g);
    //   (*this).resize(n);
    //   return *this;
    // }
    // F &operator/=(const F &g) {
    //   int n = (*this).size();
    //   *this = convolution(*this, g.inv(n));
    //   (*this).resize(n);
    //   return *this;
    // }

    // // naive
    // F &operator*=(const F &g) {
    //   int n = (*this).size(), m = g.size();
    //   for(int i=n;i--;) {
    //     (*this)[i] *= g[0];
    //     for(int j=1;j<min(i+1, m);j++) (*this)[i] += (*this)[i-j] * g[j];
    //   }
    //   return *this;
    // }
    // F &operator/=(const F &g) {
    //   assert(g[0] != T(0));
    //   T ig0 = g[0].inv();
    //   int n = (*this).size(), m = g.size();
    //   rep(i, n) {
    //     for(int j=1;j<min(i+1, m);j++) (*this)[i] -= (*this)[i-j] * g[j];
    //     (*this)[i] *= ig0;
    //   }
    //   return *this;
    // }

    // sparse
    F &operator*=(vector<pair<int, T>> g){
        int n=(*this).size();
        auto [d, c]=g.front();
        if(d==0) g.erase(g.begin());
        else c=0;
        for(int i=n;i--;){
            (*this)[i]*=c;
            for(auto&[j, b] : g){
                if(j>i) break;
                (*this)[i]+=(*this)[i-j]*b;
            }
        }
        return *this;
    }
    F &operator/=(vector<pair<int, T>> g){
        int n=(*this).size();
        auto [d, c]=g.front();
        assert(d==0&&c!=T(0));
        T ic=c.inv();
        g.erase(g.begin());
        rep(i, n){
            for(auto&[j, b] : g){
                if(j>i) break;
                (*this)[i]-=(*this)[i-j]*b;
            }
            (*this)[i]*=ic;
        }
        return *this;
    }

    // multiply and divide (1 + cz^d)
    void multiply(const int d, const T c){
        int n=(*this).size();
        assert(d>=0);
        if(d>=n) return;
        if(c==T(1)) for(int i=n-d;i--;) (*this)[i+d]+=(*this)[i];
        else if(c==T(-1)) for(int i=n-d;i--;) (*this)[i+d]-=(*this)[i];
        else for(int i=n-d;i--;) (*this)[i+d]+=(*this)[i]*c;
    }
    void divide(const int d, const T c){
        int n=(*this).size();
        if(c==T(1)) rep(i, n-d) (*this)[i+d]-=(*this)[i];
        else if(c==T(-1)) rep(i, n-d) (*this)[i+d]+=(*this)[i];
        else rep(i, n-d) (*this)[i+d]-=(*this)[i]*c;
    }

    T eval(const T& a)const {
        T x(1), res(0);
        for(auto e : *this) res+=e*x, x*=a;
        return res;
    }

    // O(n)
    F &integral_inplace(){
        int n=this->size();
        assert(n>0);
        if(n==1) return *this=F{0};
        this->insert(this->begin(), 0);
        this->pop_back();
        vector<T> inv(n);
        inv[1]=1;
        int p=T::mod();
        for(int i=2;i<n;i++) inv[i]=-inv[p%i]*(p/i);
        for(int i=2;i<n;i++) (*this)[i]*=inv[i];
        return *this;
    }
    F integral()const {return F(*this).integral_inplace();}

    // O(n)
    F &derivative_inplace(){
        int n=this->size();
        assert(n>0);
        for(int i=2;i<n;i++) (*this)[i]*=i;
        this->erase(this->begin());
        this->push_back(0);
        return *this;
    }
    F derivative()const {return F(*this).derivative_inplace();}
    // O(n log n)
    F &log_inplace(int d=-1){
        int n=this->size();
        assert(n>0&&(*this)[0]==1);
        if(d==-1) d=n;
        assert(d>=0);
        if(d<n) this->resize(d);
        F f_inv=this->inv();
        this->derivative_inplace();
        this->multiply_inplace(f_inv);
        this->integral_inplace();
        return *this;
    }
    F log(const int d=-1)const {return F(*this).log_inplace(d);}

    // O(n log n)
    // https://arxiv.org/abs/1301.5804 (Figure 1, right)
    F &exp_inplace(int d=-1){
        int n=this->size();
        assert(n>0&&(*this)[0]==0);
        if(d==-1) d=n;
        assert(d>=0);
        F g{1}, g_fft{1, 1};
        (*this)[0]=1;
        this->resize(d);
        F h_drv(this->derivative());
        for(int m=2;m<d;m*=2){
            // prepare
            F f_fft(this->begin(), this->begin()+m);
            f_fft.resize(2*m), fft(f_fft);

            // Step 2.a'
            {
                F _g(m);
                rep(i, m) _g[i]=f_fft[i]*g_fft[i];
                fft(_g, true);
                _g.erase(_g.begin(), _g.begin()+m/2);
                _g.resize(m), fft(_g);
                rep(i, m) _g[i]*=g_fft[i];
                fft(_g, true);
                _g.resize(m/2);
                _g/=T(-m)*m;
                g.insert(g.end(), _g.begin(), _g.begin()+m/2);
            }

            // Step 2.b'--d'
            F t(this->begin(), this->begin()+m);
            t.derivative_inplace();
            {
                // Step 2.b'
                F r{h_drv.begin(), h_drv.begin()+m-1};
                // Step 2.c'
                r.resize(m);fft(r);
                rep(i, m) r[i]*=f_fft[i];
                fft(r, true);
                r/=-m;
                // Step 2.d'
                t+=r;
                t.insert(t.begin(), t.back());t.pop_back();
            }

            // Step 2.e'
            if(2*m<d){
                t.resize(2*m);fft(t);
                g_fft=g;g_fft.resize(2*m);fft(g_fft);
                rep(i, 2*m) t[i]*=g_fft[i];
                fft(t, true);
                t.resize(m);
                t/=2*m;
            }
            else{ // この場合分けをしても数パーセントしか速くならない
                F g1(g.begin()+m/2, g.end());
                F s1(t.begin()+m/2, t.end());
                t.resize(m/2);
                g1.resize(m), fft(g1);
                t.resize(m),  fft(t);
                s1.resize(m), fft(s1);
                rep(i, m) s1[i]=g_fft[i]*s1[i]+g1[i]*t[i];
                rep(i, m) t[i]*=g_fft[i];
                fft(t, true);
                fft(s1, true);
                rep(i, m/2) t[i+m/2]+=s1[i];
                t/=m;
            }

            // Step 2.f'
            F v(this->begin()+m, this->begin()+min<int>(d, 2*m));v.resize(m);
            t.insert(t.begin(), m-1, 0);t.push_back(0);
            t.integral_inplace();
            rep(i, m) v[i]-=t[m+i];

            // Step 2.g'
            v.resize(2*m);fft(v);
            rep(i, 2*m) v[i]*=f_fft[i];
            fft(v, true);
            v.resize(m);
            v/=2*m;

            // Step 2.h'
            rep(i, min(d-m, m)) (*this)[m+i]=v[i];
        }
        return *this;
    }
    F exp(const int d=-1)const {return F(*this).exp_inplace(d);}

    // O(n log n)
    F &pow_inplace(const long k, int d=-1){
        int n=this->size();
        if(d==-1) d=n;
        assert(d>=0&&k>=0);
        if(d==0) return *this=F(0);
        if(k==0){
            *this=F(d);
            (*this)[0]=1;
            return *this;
        }
        int l=0;
        while(l<n&&(*this)[l]==0) ++l;
        if(l==n||l>(d-1)/k) return *this=F(d);
        T c{(*this)[l]};
        this->erase(this->begin(), this->begin()+l);
        *this/=c;
        this->log_inplace(d-l*k);
        *this*=k;
        this->exp_inplace();
        *this*=c.pow(k);
        this->insert(this->begin(), l*k, 0);
        return *this;
    }
    F pow(const long k, const int d=-1)const {return F(*this).pow_inplace(k, d);}

    F operator*(const T& g)const {return F(*this)*=g;}
    F operator/(const T& g)const {return F(*this)/=g;}
    F operator+(const F& g)const {return F(*this)+=g;}
    F operator-(const F& g)const {return F(*this)-=g;}
    F operator<<(const int d)const {return F(*this)<<=d;}
    F operator>>(const int d)const {return F(*this)>>=d;}
    F operator*(const F& g)const {return F(*this)*=g;}
    F operator/(const F& g)const {return F(*this)/=g;}
    F operator*(vector<pair<int, T>> g)const {return F(*this)*=g;}
    F operator/(vector<pair<int, T>> g)const {return F(*this)/=g;}
};


// using mint = modint998244353;
// using fps = FormalPowerSeries<mint>;
// using sfps = vector<pair<int, mint>>;