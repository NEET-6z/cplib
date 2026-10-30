#include "../math/modint.hpp"
#include "../math/convolution.hpp"

template <typename G>
struct CentroidDecomposition {
    const G& g;
    vector<int> sub;
    vector<bool> v;
    vector<vector<int>> tree;
    int root;

    CentroidDecomposition(const G& g_, int isbuild=true):g(g_){
        sub.resize(g.size(), 0);
        v.resize(g.size(), false);
        if(isbuild) build();
    }

    void build(){
        tree.resize(g.size());
        root=build_dfs(0);
    }

    int get_size(int cur, int par){
        sub[cur]=1;
        for(auto& dst : g[cur]){
            if(dst==par||v[dst]) continue;
            sub[cur]+=get_size(dst, cur);
        }
        return sub[cur];
    }

    int get_centroid(int cur, int par, int mid){
        for(auto& dst : g[cur]){
            if(dst==par||v[dst]) continue;
            if(sub[dst]>mid) return get_centroid(dst, cur, mid);
        }
        return cur;
    }

    int build_dfs(int cur){
        int centroid=get_centroid(cur, -1, get_size(cur, -1)/2);
        v[centroid]=true;
        for(auto& dst : g[centroid]){
            if(!v[dst]){
                int nxt=build_dfs(dst);
                if(centroid!=nxt) tree[centroid].emplace_back(nxt);
            }
        }
        v[centroid]=false;
        return centroid;
    }
};

template <typename G>
struct FrequencyTableOfTreeDistance:CentroidDecomposition<G> {
    using mint=modint<>;
    using CentroidDecomposition<G>::g;
    using CentroidDecomposition<G>::v;
    using CentroidDecomposition<G>::get_size;
    using CentroidDecomposition<G>::get_centroid;


    FrequencyTableOfTreeDistance(const G& _g)
        :CentroidDecomposition<G>(_g, false){}
    vector<mint> count, self;

    void dfs_depth(int cur, int par, int d){
        while((int)count.size()<=d) count.emplace_back(0);
        while((int)self.size()<=d) self.emplace_back(0);
        count[d]+=1;
        self[d]+=1;
        for(int dst : g[cur]){
            if(par==dst||v[dst]) continue;
            dfs_depth(dst, cur, d+1);
        }
    };

    vector<mint> get(int start=0){
        queue<int> Q;
        Q.push(get_centroid(start, -1, get_size(start, -1)/2));
        vector<mint> ans;
        ans.reserve(g.size());
        count.reserve(g.size());
        self.reserve(g.size());

        while(!Q.empty()){
            int r=Q.front();
            Q.pop();
            count.clear();
            v[r]=1;
            for(auto& c : g[r]){
                if(v[c]) continue;
                self.clear();
                Q.emplace(get_centroid(c, -1, get_size(c, -1)/2));
                dfs_depth(c, r, 1);
                auto self2=convolution(self, self);
                while(self2.size()>ans.size()) ans.emplace_back(0);
                for(int i=0;i<(int)self2.size();i++) ans[i]-=self2[i];
            }
            if(count.empty()) continue;
            count[0]+=1;
            auto count2=convolution(count, count);
            while(count2.size()>ans.size()) ans.emplace_back(0);
            for(int i=0;i<(int)count2.size();i++) ans[i]+=count2[i];
        }

        for(auto& x : ans) x/=2;
        return ans;
    }
};