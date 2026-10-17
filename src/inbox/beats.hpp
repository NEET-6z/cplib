#include "../template.hpp"

const long INF=3e18+100;
struct Segtree_beats {
    long op(int type,long x,long y){return type?min(x,y):max(x,y);}
    bool cmp(int type,long x,long y){return type?x < y:x > y;}
    struct alignas(32) Node {
        long sum=0;
        long a1[2]={},a2[2]={-INF,INF},ac[2]={1,1},add=0;
    };
    vector<Node> v;
    long n,log,e[3]={-INF,INF,0};
    Segtree_beats(){}
    Segtree_beats(int n):Segtree_beats(vector<long>(n)){}
    Segtree_beats(const vector<long>& a){
        n=1,log=0;
        while(n<(int)a.size()) n<<=1,log++;
        v.resize(2*n);
        rep(i,(int)a.size()){
            v[i+n].sum=v[i+n].a1[0]=v[i+n].a1[1]=a[i];
        }
        for(int i=n-1;i>=1;--i) update(i);
    }

    // 0 : add, 1 : chmin, 2 : chmax, 3 : update
    template <int cmd> void apply(int l,int r,long x){
        if(l==r) return;
        l+=n,r+=n;
        for(int i=log;i>=1;--i){
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        {
            int l2=l,r2=r;
            while(l<r){
                if(l&1) _apply<cmd>(l++,x);
                if(r&1) _apply<cmd>(--r,x);
                l>>=1;
                r>>=1;
            }
            l=l2,r=r2;
        }
        for(int i=1;i<=log;++i){
            if(((l>>i)<<i)!=l) update(l>>i);
            if(((r>>i)<<i)!=r) update((r-1)>>i);
        }
    }

    // 0 : max, 1 : min, 2 : sum
    template <int cmd> long fold(int l,int r){
        if(l==r) return 0;
        l+=n,r+=n;
        for(int i=log;i>=1;--i){
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        long lx=e[cmd],rx=e[cmd];
        while(l<r){
            if(l&1) op<cmd>(lx,v[l++]);
            if(r&1) op<cmd>(rx,v[--r]);
            l>>=1;
            r>>=1;
        }
        if constexpr(cmd<=1) lx=op(cmd,lx,rx);
        if constexpr(cmd==2) lx+=rx;
        return lx;
    }
private:
    void update(int k){
        Node& p=v[k];
        Node& l=v[k*2+0];
        Node& r=v[k*2+1];
        p.sum=l.sum+r.sum;
        rep(t,2){
            if(l.a1[t]==r.a1[t]){
                p.a1[t]=l.a1[t];
                p.a2[t]=op(t,l.a2[t],r.a2[t]);
                p.ac[t]=l.ac[t]+r.ac[t];
            }
            else{
                bool f=cmp(t,l.a1[t],r.a1[t]);
                p.a1[t]=f?l.a1[t]:r.a1[t];
                p.ac[t]=f?l.ac[t]:r.ac[t];
                p.a2[t]=op(t,f?r.a1[t]:l.a1[t],
                           f?l.a2[t]:r.a2[t]);
            }
        }
    }
    void push_add(int k,long x){
        Node& p=v[k];
        p.sum+=x<<(log+__builtin_clz(k)-31);
        rep(t,2){
            p.a1[t]+=x;
            if(p.a2[t]!=e[t]) p.a2[t]+=x;
        }
        p.add+=x;
    }
    void push(int cmd,int k,long x){
        Node& p=v[k];
        p.sum+=(x-p.a1[cmd])*p.ac[cmd];
        if(p.a1[cmd^1]==p.a1[cmd]) p.a1[cmd^1]=x;
        if(p.a2[cmd^1]==p.a1[cmd]) p.a2[cmd^1]=x;
        p.a1[cmd]=x;
    }
    void push(int k){
        Node& p=v[k];
        if(p.add){
            rep(t,2) push_add(k*2+t,p.add);
            p.add=0;
        }
        rep(t,2) rep(s,2) if(cmp(t,v[k*2+s].a1[t],p.a1[t]))
            push(t,k*2+s,p.a1[t]);
    }
    void subtree_ch(int cmd,int k,long x){
        if(!cmp(cmd,v[k].a1[cmd],x)) return;
        if(cmp(cmd,x,v[k].a2[cmd])){
            return push(cmd,k,x);
        }
        push(k);
        rep(t,2) subtree_ch(cmd,k*2+t,x);
        update(k);
    }
    template <int cmd> inline void _apply(int k,long x){
        rep(i,2) if(cmd>>i&1) subtree_ch(i,k,x);
        if constexpr(cmd==0) push_add(k,x);
    }
    template <int cmd> inline void op(long& a,const Node& b){
        if constexpr(cmd<=1) a=op(cmd,a,b.a1[cmd]);
        if constexpr(cmd==2) a+=b.sum;
    }
};