#include "../template.hpp"

template<class S, S (*op)(S, S), S (*e)()>
struct SWAG{
    vector<S> r,ld,rd;
    SWAG(): r(1,e()), ld(1,e()), rd(1, e()) {}
    
    void push(S s){
        r.push_back(s);
        rd.push_back(op(rd.back(), s));
    }
    void pop(){
        if(si(ld)==1) while(si(r)>=2) {
            ld.push_back(op(r.back(), ld.back()));
            r.pop_back();
            rd.pop_back();
        }
        ld.pop_back();
        assert(si(ld));
    }
    S get(){
        return op(ld.back(), rd.back());
    }
    pair<S,S> get_lr(){
        return {ld.back(),rd.back()};
    }
};

