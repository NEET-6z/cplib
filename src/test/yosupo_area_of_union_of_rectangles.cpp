#define PROBLEM "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"
#include "../segtree/lazy_segtree.hpp"

struct UnionRect{
    struct S{
        int c, w;
        static S op(S x, S y){
            if(x.c<y.c)return x;
            if(x.c>y.c)return y;
            return {x.c,x.w+y.w};
        };
        static S e(){
            return {(int)1e9,0};
        }
    };
    struct F{
        int a;
        static S mpp(F f, S x){
            x.c+=f.a;
            return x;
        }
        static F cmpo(F f, F g){
            g.a+=f.a;
            return g;
        }
        static F id(){
            return {0};
        }
    };

    vector<array<int,4>> a;
    vector<int> z;
    void add(int d, int u, int l, int r){
        a.push_back({d,u,l,r});
        z.push_back(l);
        z.push_back(r);
    }
    long area(){
        int n=si(a);
        if(n==0)return 0;
        sort(all(z));
        z.erase(unique(all(z)),z.end());
        vector<array<int,4>> ev;
        rep(i,n){
            int l=lower_bound(all(z),a[i][2])-z.begin();
            int r=lower_bound(all(z),a[i][3])-z.begin();
            ev.push_back({a[i][0],l,r,0});
            ev.push_back({a[i][1],l,r,1});
        }
        sort(all(ev));
        int pr=0;
        int M=si(z);
        lazy_segtree<S,S::op,S::e,F,F::mpp,F::cmpo,F::id> seg(M-1);
        rep(i,M-1)seg.set(i,S{0,z[i+1]-z[i]});
        
        int W=z.back()-z[0];
        long ret=0;
        int cur=W;
        for(auto [h,l,r,v]:ev){
            ret+=1l*(h-pr)*(W-cur);
            if(v==0){
                S s=seg.prod(l,r);
                if(s.c==0)cur-=s.w;
                seg.apply(l,r,{1});
            }
            else{
                S s=seg.prod(l,r);
                if(s.c==1)cur+=s.w;
                seg.apply(l,r,{-1});
            }
            pr=h;
        }
        return ret;
    }
};

int main(){
    int N;
    cin>>N;
    UnionRect ur;
    rep(i,N){
        int l,d,r,u;
        cin>>l>>d>>r>>u;
        ur.add(l,r,d,u);
    }
    cout<<ur.area()<<"\n";
}