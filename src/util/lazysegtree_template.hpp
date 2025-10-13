#include "../segtree/lazy_segtree.hpp"

struct RMQ_RAQ {
    using S = long;
    using F = long;
    static S op(S l, S r) { return min(l, r); }
    static S e() { return LONG_MAX; }
    static S mpp(F f, S s) { return f + s; }
    static F cmpo(F f, F g) { return f + g; }
    static F id() { return 0; }
};

struct RMQ_RUQ {
    using S = long;
    using F = optional<long>;
    static S op(S l, S r) { return min(l, r); }
    static S e() { return LONG_MAX; }
    static S mpp(F f, S s) { return (f ? f.value() : s); }
    static F cmpo(F f, F g) { return (f ? f : g); }
    static F id() { return nullopt; }
};

struct RSQ_RAQ{
    using S=pair<long,int>;
    using F=long;
    S op(S l, S r){return {l.fi+r.fi,l.se+r.se};}
    S e(){return {0,1};}
    S mpp(F f, S s){return {s.fi+s.se*f,s.se};}
    F cmpo(F f, F g){return f+g;}
    F id(){return 0;}
};
struct RSQ_RUQ{
    using S=pair<long,int>;
    using F=optional<long>;
    S op(S l, S r){return {l.fi+r.fi, l.se+r.se};}
    S e(){return {0,1};}
    S mpp(F f, S s){return (f?S{f.value()*s.se,s.se}:s);}
    F cmpo(F f, F g){return f?f:g;}
    F id(){return nullopt;}
};

