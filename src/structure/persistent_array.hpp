#include "../template.hpp"

template <class S, int B=20>
struct persistent_array {
    static_assert(B>=2);

    struct Node {
        S d;
        array<Node*, B> ch{};

        explicit Node(const S& d):d(d){}
        explicit Node(const array<Node*, B>& ch):d(S{}), ch(ch){}
    };
    using NP=Node*;

private:
    int n{}, h{};
    vector<int> pw;
    NP make_node(const S& d)const {
        return new Node(d);
    }
    NP make_node(const array<NP, B>& ch)const {
        return new Node(ch);
    }

    NP build(int level, int l, const vector<S>& v)const {
        if(level==0) return make_node(v[l]);

        array<NP, B> ch{};
        int len=pw[level-1];
        rep(i, B){
            int nl=l+i*len;
            if(nl>=n) break;
            ch[i]=build(level-1, nl, v);
        }
        return make_node(ch);
    }

    NP set(int k, const S& x, NP t, int level)const {
        if(level==0) return make_node(x);

        int len=pw[level-1];
        int i=k/len;
        k%=len;

        auto ch=t->ch;
        ch[i]=set(k, x, ch[i], level-1);
        return make_node(ch);
    }

public:
    persistent_array() = default;

    explicit persistent_array(int n):n(n){
        assert(n>=1);
        pw.push_back(1);
        while(pw.back()<n){
            assert(pw.back()<=INT_MAX/B);
            pw.push_back(pw.back()*B);
        }
        h=(int)pw.size()-1;
    }

    NP build(const vector<S>& v)const {
        assert(n==(int)v.size());
        assert(n>=1);
        return build(h, 0, v);
    }

    NP set(NP t, int k, const S& x)const {
        assert(0<=k&&k<n);
        return set(k, x, t, h);
    }

    S get(NP t, int k)const {
        assert(0<=k&&k<n);
        int level=h;
        while(level>0){
            int len=pw[level-1];
            int i=k/len;
            k%=len;
            t=t->ch[i];
            --level;
        }
        return t->d;
    }
};