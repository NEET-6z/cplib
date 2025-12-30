#include "../template.hpp"


struct Min {
    using S=long;
    S op(S l,S r){return min(l,r);}
    S e(){return LONG_MAX;}
};

struct Sum {
    using S=long;
    S op(S l,S r){return l+r;}
    S e(){return 0;}
};

//f_i(x)=a_ix+b_i, prod(l,r)=f_{r-1}(f_{r-2}(...f_l(x)))
struct LinearF {
    using S=pair<long,long>;
    S op(S l,S r){return {l.fi*r.fi,l.se*r.fi+r.se};}
    S e(){return {1,0};}
};

struct Minid {
    using S=pair<long,int>;
    S op(S l,S r){return min(l,r);}
    S e(){return {LONG_MAX,-1};}
};


