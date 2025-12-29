#include "../template.hpp"

struct FunctionalGraph {
    int N,L;
    vector<int> P,color,isc,cid,leader,root; //親, どの連結成分, サイクルに属するか, サイクルに属する場合leaderから何番目か, 連結成分のリーダー(サイクル内のどれか), はじめて訪れるサイクル内の頂点
    vector<vector<int>> cycles,G;
    FunctionalGraph(vector<int> P_):N(si(P_)),L(0),P(P_),color(N,-1),isc(N,0),cid(N,0),leader(N,0),root(N,0),G(N){
        rep(i,N){
            if(~color[i]) continue;
            vector<int> V;
            int now=i;
            while(color[now]==-1){
                color[now]=L;
                V.push_back(now);
                now=P[now];
            }
            if(color[now]==L){
                int r=now;
                cycles.emplace_back();
                int j=0;
                do{
                    isc[now]=1;
                    cid[now]=j;
                    cycles.back().push_back(now);
                    leader[now]=r;
                    root[now]=now;
                    now=P[now];
                    j++;
                }while(now!=r);
                L++;
            }
            for(int e: V|views::reverse){
                if(isc[e]) continue;
                leader[e]=leader[P[e]];
                root[e]=root[P[e]];
                color[e]=color[P[e]];
            }
        }
        rep(i,N) if(!isc[i]) G[P[i]].push_back(i);
    };
};
// auto [_, L, __, color, isc, cid, leader, root, cycles, G] = FunctionalGraph(A);
