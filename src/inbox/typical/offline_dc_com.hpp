
template<class S, S (*op)(S, S)>
struct OfflineDynamicConnectivity {
    using E=pair<int, int>;
    struct Rec { int a, b, pa, pb;S va;char ha; };

    int V, Q, n=1;
    vector<S> A;
    vector<int> p;                       // DSU(頂点 + 値ノード)
    vector<S> val;
    vector<char> has;                    // val が有効か(根のみ意味を持つ)
    vector<Rec> st;
    vector<vector<pair<int, S>>> sets;   // 頂点ごとの (時刻, 新しい値)
    vector<vector<E>> seg;
    map<E, int> appear;                  // 現在存在する辺の開始時刻
    vector<tuple<int, int, E>> pend;     // 確定した辺区間 [l, r)

    OfflineDynamicConnectivity(const vector<S>& A)
        :V(A.size()), A(A), p(V, -1), val(V), has(V, 0), sets(V){}

    void insert(int idx, int s, int t){appear[minmax(s, t)]=idx;}
    void erase(int idx, int s, int t){
        auto e=minmax(s, t);
        pend.emplace_back(appear[e], idx, e);
        appear.erase(e);
    }
    void set(int idx, int v, S x){sets[v].emplace_back(idx, x);}

    void add(int l, int r, E e){
        for(l+=n, r+=n;l<r;l>>=1, r>>=1){
            if(l&1) seg[l++].push_back(e);
            if(r&1) seg[--r].push_back(e);
        }
    }

    void build(int q){
        Q=q;
        while(n<Q) n<<=1;
        seg.assign(2*n, {});
        for(auto& [e, t] : appear) pend.emplace_back(t, Q, e);
        for(auto& [l, r, e] : pend) add(l, r, e);
        for(int v=0;v<V;v++){
            S cur=A[v];
            int t0=0;
            auto put=[&](int r) {
                if(t0>=r) return;
                add(t0, r, E(v, (int)p.size()));
                p.push_back(-1);val.push_back(cur);has.push_back(1);
            };
            for(auto& [t, x] : sets[v]){put(t);cur=x;t0=t;}
            put(Q);
        }
    }

    int leader(int x)const {while(p[x]>=0) x=p[x];return x;}
    S get(int x)const {return val[leader(x)];}

    void merge(int a, int b){
        a=leader(a), b=leader(b);
        if(a==b) return;
        if(p[a]>p[b]) swap(a, b);
        st.push_back({a, b, p[a], p[b], val[a], has[a]});
        p[a]+=p[b];p[b]=a;
        if(has[b]){val[a]=has[a]?op(val[a], val[b]):val[b];has[a]=1;}
    }
    void undo(){
        auto& r=st.back();
        p[r.a]=r.pa;p[r.b]=r.pb;val[r.a]=r.va;has[r.a]=r.ha;
        st.pop_back();
    }

    void run(const function<void(int)>& f, int k=1){
        size_t t=st.size();
        for(auto& [a, b] : seg[k]) merge(a, b);
        if(k<n) run(f, 2*k), run(f, 2*k+1);
        else if(k-n<Q) f(k-n);
        while(st.size()>t) undo();
    }
};