#include "../tree/lca.hpp"

//https://beet-aizu.github.io/library/tree/auxiliarytree.cpp
struct AuxiliaryTree:LCA {
    using super=LCA;

    vector<int> idx;
    vector<vector<int>> T;
    AuxiliaryTree(vector<vector<int>> G_, int root=0)
        :super(G_, root), idx(si(G_)), T(si(G_)){
        int pos=0;
        dfs(root, -1, pos);
    }

    void dfs(int v, int p, int& pos){
        idx[v]=pos++;
        for(int u : G[v])
            if(u!=p) dfs(u, v, pos);
    }

    void add_aux_edge(int u, int v){
        T[u].emplace_back(v);
        T[v].emplace_back(u);
    }

    using super::lca, super::dep;
    //vsの中身は変更される。clearで消すときは初めにvsに入れた頂点ではなく、ここに渡した後のvsから直接見ると良い
    void query(vector<int>& vs){
        assert(!vs.empty());
        sort(all(vs), [&](int a, int b) {return idx[a]<idx[b];});
        vs.erase(unique(all(vs)), vs.end());

        int k=si(vs);
        stack<int> st;
        st.emplace(vs[0]);
        rep(i, k-1){
            int w=lca(vs[i], vs[i+1]);
            if(w!=vs[i]){
                int l=st.top();
                st.pop();
                while(!st.empty() and dep[w]<dep[st.top()]){
                    add_aux_edge(st.top(), l);
                    l=st.top();
                    st.pop();
                }
                if(st.empty() or st.top()!=w){
                    st.emplace(w);
                    vs.emplace_back(w);
                }
                add_aux_edge(w, l);
            }
            st.emplace(vs[i+1]);
        }

        while(si(st)>1){
            int c=st.top();
            st.pop();
            add_aux_edge(st.top(), c);
        }
    }

    void clear(const vector<int>& ws){
        for(int w : ws) T[w].clear();
    }
};