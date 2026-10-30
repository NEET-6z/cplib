#include "../template.hpp"

/*
divisor_transform::zeta(a): aを約数ゼータ変換する(下位集合への累積和=一般的な累積和)
divisor_transform::mobius(a): aを約数メビウス変換する(下位集合への累積和の逆変換)
multiple_transform::zeta(a): aを倍数ゼータ変換する(上位集合への累積和)
multiple_transform::mobius(a): aを倍数メビウス変換する(上位集合への累積和の逆変換)
*/

vector<int> prime_enumerate(int N){
    vector<bool> sieve(N/3+1, 1);
    for(int p=5, d=4, i=1, sqn=sqrt(N);p<=sqn;p+=d=6-d, i++){
        if(!sieve[i]) continue;
        for(int q=p*p/3, r=d*p/3+(d*p%3==2), s=2*p,
            qe=sieve.size();
            q<qe;q+=r=s-r)
            sieve[q]=0;
    }
    vector<int> ret{2, 3};
    for(int p=5, d=4, i=1;p<=N;p+=d=6-d, i++)
        if(sieve[i]) ret.push_back(p);
    while(!ret.empty()&&ret.back()>N) ret.pop_back();
    return ret;
}

struct divisor_transform {
    template <typename T>
    static void zeta(vector<T>& a){
        int N=a.size()-1;
        auto sieve=prime_enumerate(N);
        for(auto& p : sieve)
            for(int k=1;k * p<=N;++k) a[k*p]+=a[k];
    }
    template <typename T>
    static void mobius(vector<T>& a){
        int N=a.size()-1;
        auto sieve=prime_enumerate(N);
        for(auto& p : sieve)
            for(int k=N/p;k>0;--k) a[k*p]-=a[k];
    }

    template <typename I, typename T>
    static void zeta(map<I, T>& a){
        for(auto p=rbegin(a);p!=rend(a);p++)
            for(auto& x : a){
                if(p->first==x.first) break;
                if(p->first%x.first==0) p->second+=x.second;
            }
    }
    template <typename I, typename T>
    static void mobius(map<I, T>& a){
        for(auto& x : a){
            for(auto p=rbegin(a);p!=rend(a);p++){
                if(x.first==p->first) break;
                if(p->first%x.first==0) p->second-=x.second;
            }
        }
    }
};

struct multiple_transform {
    template <typename T>
    static void zeta(vector<T>& a){
        int N=a.size()-1;
        auto sieve=prime_enumerate(N);
        for(auto& p : sieve)
            for(int k=N/p;k>0;--k) a[k]+=a[k*p];
    }
    template <typename T>
    static void mobius(vector<T>& a){
        int N=a.size()-1;
        auto sieve=prime_enumerate(N);
        for(auto& p : sieve)
            for(int k=1;k * p<=N;++k) a[k]-=a[k*p];
    }

    template <typename I, typename T>
    static void zeta(map<I, T>& a){
        for(auto& x : a)
            for(auto p=rbegin(a);p->first!=x.first;p++)
                if(p->first%x.first==0) x.second+=p->second;
    }
    template <typename I, typename T>
    static void mobius(map<I, T>& a){
        for(auto p1=rbegin(a);p1!=rend(a);p1++)
            for(auto p2=rbegin(a);p2!=p1;p2++)
                if(p2->first%p1->first==0) p1->second-=p2->second;
    }
};

/**
 * @brief 倍数変換・約数変換
 * @docs docs/multiplicative-function/divisor-multiple-transform.md
 */