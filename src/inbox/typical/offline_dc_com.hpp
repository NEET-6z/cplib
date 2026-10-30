template<class S, S (*op)(S, S)>
struct dsu_rollback {
    vector<int> p;
    vector<S> val;
    vector<char> has;  // val が有効か(根のみ意味を持つ)
    struct Rec { int a, b, pa, pb;S va;char ha; };
    vector<Rec> st;

    dsu_rollback(){}
    int append(const S& x, bool h){   // run 前にノードを追加
        p.push_back(-1);val.push_back(x);has.push_back(h);
        return (int)p.size()-1;
    }

    int leader(int x)const {return p[x]<0?x:leader(p[x]);}
    bool same(int a, int b)const {return leader(a)==leader(b);}
    int size(int x)const {return -p[leader(x)];}
    S get(int x)const {return val[leader(x)];}
    int time()const {return (int)st.size();}

    int merge(int a, int b){
        a=leader(a), b=leader(b);
        if(a!=b&&p[a]>p[b]) swap(a, b);
        st.push_back({a, b, p[a], p[b], val[a], has[a]});
        if(a==b) return a;
        p[a]+=p[b];
        p[b]=a;
        if(has[b]){
            if(has[a]) val[a]=op(val[a], val[b]);
            else val[a]=val[b], has[a]=1;
        }
        return a;
    }

    void undo(){
        auto& r=st.back();
        p[r.a]=r.pa;
        p[r.b]=r.pb;
        val[r.a]=r.va;
        has[r.a]=r.ha;
        st.pop_back();
    }

    void rollback(int t){while(time()>t) undo();}
};

template<class S, S (*op)(S, S)>
struct OfflineDynamicConnectivity {
    using E=pair<int, int>;

    dsu_rollback<S, op> uf;
    int V, Q, segsz;
    vector<S> A;
    vector<vector<pair<int, S>>> sets;  // sets[v] = {(時刻, 値)}
    vector<vector<E>> seg;
    int comp;

    vector<pair<pair<int, int>, E>> pend;
    map<E, int> cnt, appear;

    OfflineDynamicConnectivity(const vector<S>& A_, int Q)
        :V(A_.size()), Q(Q), A(A_), sets(A_.size()), comp(A_.size()){
        for(int i=0;i<V;i++) uf.append(S(), false);         // 頂点ノードは空
        segsz=1;
        while(segsz<Q) segsz<<=1;
        seg.resize(2*segsz-1);
    }

    void insert(int idx, int s, int t){
        auto e=minmax(s, t);
        if(cnt[e]++==0) appear[e]=idx;
    }

    void erase(int idx, int s, int t){
        auto e=minmax(s, t);
        if(--cnt[e]==0) pend.emplace_back(make_pair(appear[e], idx), e);
    }

    // 時刻 t 以降 A[idx] = x
    void set(int idx, int i, S x){sets[i].emplace_back(idx, x);}

    void add(int a, int b, const E& e, int k, int l, int r){
        if(r<=a||b<=l) return;
        if(a<=l&&r<=b){seg[k].emplace_back(e);return;}
        add(a, b, e, 2*k+1, l, (l+r)>>1);
        add(a, b, e, 2*k+2, (l+r)>>1, r);
    }
    void add(int a, int b, const E& e){add(a, b, e, 0, 0, segsz);}

    void build(){
        for(auto& p : cnt)
            if(p.second>0)
                pend.emplace_back(make_pair(appear[p.first], Q), p.first);
        for(auto& s : pend) add(s.first.first, s.first.second, s.second);

        // 値ノードの生成
        for(int v=0;v<V;v++){
            auto& ev=sets[v];
            stable_sort(ev.begin(), ev.end(),
                        [](auto& x, auto& y) {return x.first<y.first;});
            S cur=A[v];
            int curT=0;
            auto put=[&](int l, int r, const S& x) {
                if(l>=r) return;     // 同時刻の set は後勝ち
                int id=uf.append(x, true);
                add(l, r, E(v, id));
            };
            for(auto& [t, x] : ev){
                put(curT, t, cur);
                cur=x;curT=t;
            }
            put(curT, Q, cur);
        }
    }

    void run(const function<void(int)>& f, int k=0){
        int added=0;
        for(auto& e : seg[k]){
            // 頂点同士の辺だけが連結成分数に影響する
            if(e.second<V&&!uf.same(e.first, e.second)) added++;
            uf.merge(e.first, e.second);
        }
        comp-=added;
        if(k<segsz-1){
            run(f, 2*k+1);
            run(f, 2*k+2);
        }
        else if(k-(segsz-1)<Q){
            f(k-(segsz-1));
        }
        for(size_t i=0;i<seg[k].size();i++) uf.undo();
        comp+=added;
    }
};