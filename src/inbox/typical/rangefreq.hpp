#include "../template.hpp"

template<typename T>
struct rangefreq {
    int n;
    vector<vector<T>> dat;

    rangefreq(const vector<T>& v={}){
        n=1;
        while(n<v.size()) n<<=1;
        dat.assign(2*n, {});

        for(int i=0;i<(int)v.size();i++)
            dat[i+n].push_back(v[i]);

        for(int i=n-1;i>=1;i--){
            dat[i].resize(dat[i*2].size()+dat[i*2+1].size());
            merge(dat[i*2].begin(), dat[i*2].end(),
                  dat[i*2+1].begin(), dat[i*2+1].end(),
                  dat[i].begin());
        }
    }

    int query(int a, int b, T x, int k=1, int l=0, int r=-1)const {            // [a,b) count(* < x)
        if(r<0) r=n;
        if(b<=l||r<=a) return 0;
        if(a<=l&&r<=b) return lower_bound(dat[k].begin(), dat[k].end(), x)-dat[k].begin();
        return query(a, b, x, k*2, l, (l+r)/2)+query(a, b, x, k*2+1, (l+r)/2, r);
    }
};