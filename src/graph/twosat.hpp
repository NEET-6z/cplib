#include "../template.hpp"


//https://ei1333.github.io/library/graph/others/two-satisfiability.hpp
struct two_sat {
    two_sat():two_sat(0){}
    two_sat(int n):n(n), g(2*n), built(false){}

    int add_var(){
        g.resize(g.size()+2);
        return n++;
    }

    // not i は ~i で渡す
    void add_clause(int i, int j){
        i=max(2*i, -1-2*i);
        j=max(2*j, -1-2*j);
        assert(0<=i&&i<2*n);
        assert(0<=j&&j<2*n);
        g[i].push_back(j^1);
        g[j].push_back(i^1);
    }

    void if_then(int i, int j){add_clause(~i, j);}
    void set_val(int i){add_clause(i, i);}

    void at_most_one(const vector<int>& nodes){ //総和が1以下
        if(nodes.size()<=1) return;
        int cur=~nodes[0];
        for(int i=2;i<(int)nodes.size();++i){
            int nxt=add_var(), ni=~nodes[i];
            add_clause(cur, ni);
            add_clause(cur, nxt);
            add_clause(ni, nxt);
            cur=~nxt;
        }
        add_clause(cur, ~nodes[1]);
    }

    bool satisfiable(){
        built=true;
        ans.resize(n);
        auto id=scc_ids();
        for(int i=0;i<n;++i){
            if(id[2*i]==id[2*i+1]){
                ans.clear();
                return false;
            }
            ans[i]=id[2*i]<id[2*i+1];
        }
        return true;
    }

    vector<bool> answer(){
        if(!built) satisfiable();
        return ans;
    }

private:
    int n;
    vector<vector<int>> g;
    bool built;
    vector<bool> ans;

    vector<int> scc_ids(){
        int m=g.size(), timer=0, cnt=0;
        vector<int> st, low(m), ord(m, -1), id(m);
        st.reserve(m);

        auto dfs=[&](auto&& self, int v)->void {
            low[v]=ord[v]=timer++;
            st.push_back(v);
            for(int to : g[v]){
                if(ord[to]==-1){
                    self(self, to);
                    low[v]=min(low[v], low[to]);
                }
                else{
                    low[v]=min(low[v], ord[to]);
                }
            }
            if(low[v]==ord[v]){
                while(true){
                    int u=st.back();
                    st.pop_back();
                    ord[u]=m;
                    id[u]=cnt;
                    if(u==v) break;
                }
                ++cnt;
            }
        };

        for(int i=0;i<m;++i)
            if(ord[i]==-1) dfs(dfs, i);

        for(int& x : id) x=cnt-1-x;
        return id;
    }
};