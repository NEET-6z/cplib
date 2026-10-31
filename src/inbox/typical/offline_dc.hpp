//QlogQlogN
struct OfflineDynamicConnectivity {
    using E=pair<int, int>;
    int V, Q=0, n=1, comp;
    vector<int> p;                          // DSU(union by size, 経路圧縮なし)
    vector<tuple<int, int, int>> st;        // (親にした根 a, 子にした根 b, 元の p[b])
    vector<vector<E>> seg;
    map<E, int> appear;                     // 現在存在する辺の開始時刻
    vector<tuple<int, int, E>> pend;        // 確定した辺区間 [l, r)

    OfflineDynamicConnectivity(int V):V(V), comp(V), p(V, -1){}

    void insert(int idx, int s, int t){appear[minmax(s, t)]=idx;}
    void erase(int idx, int s, int t){
        auto e=minmax(s, t);
        pend.emplace_back(appear[e], idx, e);
        appear.erase(e);
    }

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
    }

    int leader(int x)const {while(p[x]>=0) x=p[x];return x;}
    bool same(int a, int b)const {return leader(a)==leader(b);}
    int size(int x)const {return -p[leader(x)];}

    void merge(int a, int b){
        a=leader(a), b=leader(b);
        if(a==b) return;
        if(p[a]>p[b]) swap(a, b);
        st.emplace_back(a, b, p[b]);
        p[a]+=p[b];p[b]=a;
        comp--;
    }
    void undo(){
        auto [a, b, pb]=st.back();st.pop_back();
        p[a]-=pb;p[b]=pb;
        comp++;
    }

    void run(const function<void(int)>& f, int k=1){
        size_t t=st.size();
        for(auto& [a, b] : seg[k]) merge(a, b);
        if(k<n) run(f, 2*k), run(f, 2*k+1);
        else if(k-n<Q) f(k-n);
        while(st.size()>t) undo();
    }
};