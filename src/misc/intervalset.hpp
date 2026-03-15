#include "../template.hpp"

struct IntervalSet{
    set<pair<long,long>> st;
    IntervalSet(){
        st.insert(make_pair(-1e18,-1e18));
        st.insert(make_pair(1e18,1e18));
    }
    void add(long l, long r){
        if(l>=r) return ;
        auto it=st.lower_bound(make_pair(l,r));
        it--;
        if(it->fi<=l && l<=it->se){
            chmin(l,it->fi);
            chmax(r,it->se);
        }
        it=st.lower_bound(make_pair(l,r));
        while(1){
            if(l<=it->fi&&it->fi<=r){
                chmax(r,it->se);
                it=st.erase(it);
            }
            else break;
        }
        st.insert(make_pair(l,r));
    }
    void erase(long l, long r){
        if(l>=r) return ;
        long mr=r;
        auto it=st.lower_bound(make_pair(l,-1));
        it--;
        chmax(mr,it->se);
        if(l<it->se){
            long ml=it->fi;
            st.erase(it);
            st.insert(make_pair(ml,l));
        }
        it=st.lower_bound(make_pair(l,-1));
        while(1){
            if(it->fi<=r){
                chmax(mr,it->se);
                it=st.erase(it);
            }
            else break;
        }
        if(r<mr)st.insert(make_pair(r,mr));
    }
    bool in(long x){
        auto it=st.lower_bound(make_pair(x+1,0));
        it--;
        return (x<it->se);
    }
};
