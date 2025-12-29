#include "../template.hpp"


//[val, id], idが被らないように小さい方から2つを保持する
template<typename T> bool top2id_chmin(pair<pair<T,T>,pair<T,T>> &p, pair<T,T> x){
    if(p.fi.se==x.se){
        if(p.fi.fi>x.fi){
            p.fi.fi=x.fi;
            return 1;
        }
    }
    else if(p.se.se==x.se){
        if(p.se.fi>x.fi){
            p.se.fi=x.fi;
            if(p.fi.fi>p.se.fi) swap(p.fi,p.se);
            return 1;
        }
    }
    else{
        if(p.fi.fi>x.fi){
            p.se=p.fi;
            p.fi=make_pair(x.fi,x.se);
        }
        if(p.se.fi>x.fi){
            p.se=make_pair(x.fi,x.se);
            if(p.fi.fi>p.se.fi) swap(p.fi,p.se);
        }
        return 1;
    }
    return 0;
}