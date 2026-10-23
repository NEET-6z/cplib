#include "../template.hpp"

// Interval Set
// T: type of range, VAL: data type
template<class T, class VAL=long long>
struct IntervalSet {
    struct Node {
        T l, r;
        VAL val;
        Node(const T& l, const T& r, const VAL& v):l(l), r(r), val(v){}
        bool operator<(const Node& o)const {
            return l!=o.l?l<o.l:r<o.r;
        }
        friend ostream& operator<<(ostream& os, const Node& n){
            return os<<"(["<<n.l<<", "<<n.r<<"): "<<n.val<<")";
        }
    };

    using Iter=typename set<Node>::iterator;
    const VAL identity;
    set<Node> S;

    IntervalSet(const VAL& id=VAL()):identity(id){}
    IntervalSet(const vector<VAL>& v, const VAL& id=VAL()):identity(id){
        for(int l=0, r;l<(int)v.size();l=r){
            for(r=l+1;r<(int)v.size()&&v[r]==v[l];++r);
            S.emplace(l, r, v[l]);
        }
    }

    Iter begin(){return S.begin();}
    Iter end(){return S.end();}

    Iter get(const T& p){
        auto it=S.upper_bound(Node(p, numeric_limits<T>::max(), VAL()));
        if(it==S.begin()) return S.end();
        --it;
        return it->l<=p&&p<it->r?it:S.end();
    }

    Iter lower_bound(const T& p){
        auto it=get(p);
        return it!=end()?it:S.lower_bound(Node(p, T(), VAL()));
    }

    bool covered(const T& p){return get(p)!=end();}

    bool covered(const T& l, const T& r){
        assert(l<=r);
        if(l==r) return true;
        auto it=get(l);
        return it!=end()&&r<=it->r;
    }

    bool same(const T& p, const T& q){
        auto a=get(p), b=get(q);
        return a!=end()&&a==b;
    }

    VAL get_val(const T& p){
        auto it=get(p);
        return it==end()?identity:it->val;
    }

    VAL operator[](const T& p)const {
        auto it=S.upper_bound(Node(p, numeric_limits<T>::max(), VAL()));
        if(it==S.begin()) return identity;
        --it;
        return it->l<=p&&p<it->r?it->val:identity;
    }

    T get_mex(const T& p=0){
        auto it=get(p);
        return it==end()?p:it->r;
    }

    template<class ADD, class DEL>
    void update(T l, T r, const VAL& v, const ADD& add, const DEL& del){
        if(!(l<r)) return;
        erase(l, r, add, del);
        auto it=S.lower_bound(Node(l, T(), VAL()));
        if(it!=S.begin()&&prev(it)->r==l&&prev(it)->val==v){
            l=prev(it)->l;
            del(prev(it)->l, prev(it)->r, prev(it)->val);
            S.erase(prev(it));
        }
        while(it!=S.end()&&it->l==r&&it->val==v){
            r=it->r;
            del(it->l, it->r, it->val);
            it=S.erase(it);
        }
        it=S.emplace_hint(it, l, r, v);
        add(it->l, it->r, it->val);
    }

    void update(const T& l, const T& r, const VAL& v){
        update(l, r, v, [](T, T, VAL){}, [](T, T, VAL){});
    }

    template<class ADD, class DEL>
    void insert(T l, T r, const ADD& add, const DEL& del){
        update(l, r, VAL(), add, del);
    }
    void insert(const T& l, const T& r){update(l, r, VAL());}

    template<class ADD, class DEL>
    void erase(T l, T r, const ADD& add, const DEL& del){
        if(!(l<r)) return;
        auto it=S.lower_bound(Node(l, T(), VAL()));
        if(it!=S.begin()) --it;
        while(it!=S.end()&&it->l<r){
            if(it->r<=l){++it;continue;}
            Node n=*it;
            del(n.l, n.r, n.val);
            it=S.erase(it);
            if(n.l<l){
                auto x=S.emplace_hint(it, n.l, l, n.val);
                add(x->l, x->r, x->val);
            }
            if(r<n.r){
                auto x=S.emplace_hint(it, r, n.r, n.val);
                add(x->l, x->r, x->val);
                break;
            }
        }
    }

    void erase(const T& l, const T& r){
        erase(l, r, [](T, T, VAL){}, [](T, T, VAL){});
    }

    friend ostream& operator<<(ostream& os, const IntervalSet& s){
        for(auto& n : s.S) os<<n<<' ';
        return os;
    }
};

/*
auto add = [&](int l, int r, long long v) {
    sum += 1LL * (r - l) * v;
};

auto del = [&](int l, int r, long long v) {
    sum -= 1LL * (r - l) * v;
};
*/