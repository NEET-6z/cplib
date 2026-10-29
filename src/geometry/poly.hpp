#pragma once
#include "intersect.hpp"

S poly_area(const vector<P>& ps){
    int n=si(ps);
    S ret=0;
    rep(i,n) ret+=cross(ps[i],ps[(i+1)%n]);
    return ret/2;
}

int is_convex(const vector<P>& ps){
    int n=si(ps);
    if(n<3) return 0;
    int dir=0;
    rep(i,n){
        int t=ccw(ps[i],ps[(i+1)%n],ps[(i+2)%n]);
        if(abs(t)!=1) continue;
        if(dir==0) dir=t;
        if(dir!=t) return 0; // 凸ではない
    }
    dir=0;
    rep(i,n){
        int t=ccw(ps[0],ps[i],ps[(i+1)%n]);
        if(abs(t)!=1) continue;
        if(dir==0) dir=t;
        if(dir!=t) return -1; // 凸だが外角の和が360度ではない
    }
    return 1;
}

int poly_contains(const vector<P>& Q,const P& p){
    bool in=false;
    int n=si(Q);
    rep(i,n){
        P a=Q[i]-p,b=Q[(i+1)%n]-p;
        if(a.imag()>b.imag()) swap(a,b);
        if(a.imag()<=0&&0<b.imag()&&cross(a,b)<0) in=!in;
        if(sign(cross(a,b))==0&&dot(a,b)<=0) return 1;
    }
    return in?2:0;
}

int convex_contains(const vector<P>& ps,const P& a){
    int n=si(ps),dir=0;
    rep(i,n){
        int t=ccw(ps[i],ps[(i+1)%n],a);
        if(abs(t)==2) continue;
        if(t==0) return 1; // 周に触れる
        if(dir==0) dir=t;
        if(t!=dir) return 0; // 含まれない
    }
    return 2; // 含まれる
}

int convex_contains_log(const vector<P>& p,const P& a){ // 共線点なし
    int n=si(p);
    if(a==p[0]) return 1;
    if(n==1) return 0;
    if(intersect_sp(Line(p[0],p[1]),a)) return 1;
    if(n==2) return 0;
    if(ccw(p[0],p[1],a)==-1) return 0;

    int ok=1,ng=n;
    while(ng-ok>1){
        int m=(ok+ng)/2;
        if(ccw(p[0],p[m],a)!=-1) ok=m;
        else ng=m;
    }
    if(ok==n-1) return intersect_sp(Line(p[0],p[n-1]),a);
    if(intersect_sp(Line(p[ok],p[ok+1]),a)) return 1;
    if(ccw(p[ok],p[ok+1],a)==-1) return 0;
    if(ccw(p[ok+1],p[0],a)==-1) return 0;
    return 2;
}

int intersect_poly_segment(const vector<P>& ps,Line l){
    int n=si(ps);
    vector<Line> dia;
    rep(i,n) dia.emplace_back(Line(ps[i],ps[(i+1)%n]));
    rep(i,n/2) dia.emplace_back(Line(ps[i],ps[i+n/2]));
    if(n>=4&&n%2) dia.emplace_back(Line(ps.back(),ps[1]));
    for(const Line& d:dia)
        if(intersect_ss(d,l)==2) return 2; // 内部を通過する
    rep(i,n)
        if(intersect_ss(Line(ps[i],ps[(i+1)%n]),l)==1)
            return 1; // 周に触れる
    return 0; // 触れない
}


vector<P> convex_hull(vector<P> ps, bool strict=true){  //共線点を排除するか
    int n=si(ps), k=0;
    assert(n>0);
    sort(all(ps), [&](P a, P b){return a<b;}); //戻り値の順番: (最小/最大) (x優先/y優先)
    vector<P> ch(2*n);


    // long bd=strict;
    ld bd=(strict?EPS:-EPS);

    for(int i=0;i<n;ch[k++]=ps[i++]){
        while(k>=2&&cross(ch[k-1]-ch[k-2], ps[i]-ch[k-1])<bd)
            --k;
    }
    for(int i=n-2, t=k+1;i>=0;ch[k++]=ps[i--]){
        while(k>=t&&cross(ch[k-1]-ch[k-2], ps[i]-ch[k-1])<bd)
            --k;
    }
    ch.resize(k-1);
    return ch;
}

S convex_diamenter(vector<P> p){ //2乗
    int n=p.size();
    int is=0, js=0;
    rep(i, n){
        if(p[i].imag()>p[is].imag()) is=i;
        if(p[i].imag()<p[js].imag()) js=i;
    }
    S md=norm(p[is]-p[js]);
    int mi, mj, i, j;
    i=mi=is;
    j=mj=js;
    do{
        if(cross(p[(i+1)%n]-p[i], p[(j+1)%n]-p[j])>=0) j=(j+1)%n;
        else i=(i+1)%n;
        if(norm(p[i]-p[j])>md){
            md=norm(p[i]-p[j]);
            mi=i, mj=j;
        }
    }while(i!=is||j!=js);
    return md;
}

vector<P> convex_cut(const vector<P>& p,const Line& s){
    vector<P> ret;
    int n=si(p);
    rep(i,n){
        Line t(p[i],p[(i+1)%n]);
        if(ccw(s.a,s.b,t.a)!=-1) ret.push_back(t.a);
        if(intersect_ls(s,t)==2) ret.push_back(crosspoint_ll(s,t));
    }
    return ret;
}