#include "../structure/fenwick_tree_arbitrary.hpp"

/*
https://sotanishy.github.io/cp-library-cpp/tree/centroid_decomposition.hpp
level: Gを重心分解したときの各頂点の深さ (何回目の分割でそれが重心となるか)
sz: 各頂点が重心となるときにそれが含まれる部分木のサイズ
par: 各頂点が重心となる直前に属していた部分木の重心
*/
tuple<vector<int>, vector<int>, vector<int>>
centroid_decomposition(const vector<vector<int>>& G){
    const int N=G.size();
    vector<int> sz(N), level(N, -1), sz_comp(N), par(N);

    auto dfs_size=[&](auto& dfs_size, int v, int p)->int {
        sz[v]=1;
        for(int c : G[v]){
            if(c!=p&&level[c]==-1) sz[v]+=dfs_size(dfs_size, c, v);
        }
        return sz[v];
    };

    auto dfs_centroid=[&](auto& dfs_centroid, int v, int p, int n)->int {
        for(int c : G[v]){
            if(c!=p&&level[c]==-1&&sz[c]>n/2)
                return dfs_centroid(dfs_centroid, c, v, n);
        }
        return v;
    };

    auto decompose=[&](auto& decompose, int v, int k, int p)->void {
        int n=dfs_size(dfs_size, v, -1);
        int s=dfs_centroid(dfs_centroid, v, -1, n);
        level[s]=k;
        sz_comp[s]=n;
        par[s]=p;
        for(int c : G[s]){
            if(level[c]==-1) decompose(decompose, c, k+1, s);
        }
    };

    decompose(decompose, 0, 0, -1);
    return {level, sz_comp, par};
}
template <typename Group>
class RangeContourAggregation {
    using T=typename Group::T;

public:
    RangeContourAggregation() = default;
    explicit RangeContourAggregation(const vector<vector<int>>& G)
        :seg(G.size()),
        seg_sub(G.size()),
        dist(G.size()),
        idx(G.size()),
        sub(G.size()),
        idx_sub(G.size()),
        first(G.size()),
        first_sub(G.size()){
        tie(level, sz_comp, par)=centroid_decomposition(G);

        for(int v=0;v<(int)G.size();++v){
            // 各頂点 u について、以下の情報を計算する。
            // dist：頂点 v から頂点 u までの距離
            // idx：BFS 順序における頂点 u のインデックス
            // sub：頂点 u が属する、頂点 v の部分木の識別番号
            // idx_sub：その部分木内の BFS 順序における頂点 u のインデックス

            // 各深さ d について、以下の情報を計算する。
            // first：深さ d の頂点が BFS 順序上で最初に現れるインデックス
            // first_sub：部分木 i において、深さ d の頂点が
            //部分木内の BFS 順序で最初に現れるインデックス

            dist[v][v]=0;
            queue<pair<int, int>> que;
            que.push({v, -1});
            int k=0, sub_idx=0;
            vector<int> ks;

            while(!que.empty()){
                auto [u, i]=que.front();
                que.pop();

                // update component info
                int d=dist[v][u];
                if(d>=(int)first[v].size()){
                    first[v].push_back(k);
                }
                idx[v][u]=k++;
                // enter subtree
                if(d==1){
                    i=sub_idx++;
                    ks.push_back(0);
                    first_sub[v].emplace_back();
                }
                // update subtree info
                if(i!=-1){
                    sub[v][u]=i;
                    if(d-1>=(int)first_sub[v][i].size()){
                        first_sub[v][i].push_back(ks[i]);
                    }
                    idx_sub[v][u]=ks[i]++;
                }

                for(int w : G[u]){
                    if(level[w]>level[v]&&dist[v].find(w) == dist[v].end()){
                        dist[v][w]=d+1;
                        que.push({w, i});
                    }
                }
            }

            first[v].push_back(k);
            seg[v]=fenwick_tree_arbitrary<Group>(k);
            for(int i=0;i<sub_idx;++i){
                first_sub[v][i].push_back(ks[i]);
                seg_sub[v].emplace_back(ks[i]);
            }
        }
    }

    void update(int v, T x){
        seg[v].add(0, x);
        for(int p=par[v];p!=-1;p=par[p]){
            seg[p].add(idx[p][v], x);
            int i=sub[p][v];
            seg_sub[p][i].add(idx_sub[p][v], x);
        }
    }

    T fold(int v, int d)const { //頂点vから距離d未満の集約
        int dd=min((int)first[v].size()-1, d);
        T res=seg[v].sum(first[v][dd]);
        for(int p=par[v];p!=-1;p=par[p]){
            int dep=d-dist[p].at(v);
            if(dep>=0){
                dd=min((int)first[p].size()-1, dep);
                res=Group::op(res, seg[p].sum(first[p][dd]));
                if(dd>0){
                    int i=sub[p].at(v);
                    dd=min((int)first_sub[p][i].size()-1, dep-1);
                    res=Group::op(res, Group::inv(seg_sub[p][i].sum(first_sub[p][i][dd])));
                }
            }
        }
        return res;
    }

private:
    vector<int> level, sz_comp, par;
    vector<fenwick_tree_arbitrary<Group>> seg;
    vector<vector<fenwick_tree_arbitrary<Group>>> seg_sub;
    vector<unordered_map<int, int>> dist, idx, sub, idx_sub;
    vector<vector<int>> first;
    vector<vector<vector<int>>> first_sub;
};