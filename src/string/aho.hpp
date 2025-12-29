#pragma once
#include "../template.hpp"

struct Node {
    int prefix_cnt;
    int parent;
    vector<int> nxt, ids;
    Node(int sigma=26, int parent=-1):prefix_cnt(0), parent(-1), nxt(sigma, -1){}
};

struct Trie {
    int sigma;
    vector<Node> nodes;

    Trie(int _sigma):sigma(_sigma), nodes(1, Node(sigma)){}
    int add(vector<int> V){
        int id=nodes[0].prefix_cnt;
        int now=0;
        for(int v: V){
            if(nodes[now].nxt[v]==-1){
                nodes[now].nxt[v]=ssize(nodes);
                nodes.push_back(Node(sigma, now));
            }
            nodes[now].prefix_cnt++;
            now=nodes[now].nxt[v];
        }
        nodes[now].ids.push_back(id);
        return now;
    }
};

struct AhoCorasick:Trie {
    vector<int> cnt;
    AhoCorasick(int _sigma):Trie(_sigma+1){}
    void build(){
        cnt.assign(ssize(nodes), 0);
        rep(i,ssize(nodes)) cnt[i]=ssize(nodes[i].ids);
        queue<int> q;
        rep(i,sigma){
            if(~nodes[0].nxt[i]){
                nodes[nodes[0].nxt[i]].nxt[sigma]=0;
                q.push(nodes[0].nxt[i]);
            }
            else{
                nodes[0].nxt[i]=0;
            }
        }
        while(!q.empty()){
            auto& now=nodes[q.front()];
            int fail=now.nxt[sigma];
            cnt[q.front()]|=cnt[fail];
            q.pop();
            rep(i,sigma){
                if(~now.nxt[i]){
                    nodes[now.nxt[i]].nxt[sigma]=nodes[fail].nxt[i];
                    q.push(now.nxt[i]);
                }
                else{
                    now.nxt[i]=nodes[fail].nxt[i];
                }
            }
        }
    }

    //[cnt, next]
    pair<int,int> move(int c, int now){
        now=nodes[now].nxt[c];
        return {cnt[now], now};
    }

    int size(){
        return ssize(nodes);
    }
};