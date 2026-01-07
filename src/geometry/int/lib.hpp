#include "../../template.hpp"

using S=long;
struct P {
    S x,y;
    P(){}
    P(S x,S y):x(x),y(y){}
    auto operator<=>(const P& o) const = default;
    P operator-(){
        P res(*this);
        res.x*=-1;
        res.y*=-1;
        return res;
    }
    P& operator+=(P o){x+=o.x;y+=o.y;return *this;}
    P operator+(P o){return P(*this)+=o;}
    P& operator-=(P o){return (*this)+=-o;}
    P operator-(P o){return P(*this)-=o;}
    P& operator*=(S k){x*=k;y*=k;return *this;}
    P operator*(S k){return P(*this)*=k;}
    S real(){return x;}
    S imag(){return y;}
};
S dot(P a,P b){return a.x*b.x+a.y*b.y;}
S cross(P a,P b){return a.x*b.y-a.y*b.x;}
S norm(P a){return dot(a,a);}
int ccw(P a,P b,P c){
    b-=a;c-=a;
    if(cross(b,c)>0) return 1;  // counter-clockwise(反時計)
    if(cross(b,c)<0) return -1;  // clockwise(時計)
    if(dot(b,c)<0) return 2;  // c-a-b
    if(norm(b)<norm(c)) return -2; // a-b-c
    return 0; // a=c=b
}

bool is_orthogonal(P a1,P a2,P b1,P b2){
    return dot(a1-a2,b1-b2)==0;
}
bool is_parallel(P a1,P a2,P b1,P b2){
    return cross(a1-a2,b1-b2)==0;
}
bool is_point_on_line(P a1,P a2,P b){
    return ccw(a1,b,a2)==0;
}
bool is_point_on_segment(P a1,P a2,P b){
    return abs(ccw(a1,b,a2))!=1;
}

int intersect_segment(P a1,P a2,P b1,P b2){
    int x=ccw(a1,a2,b1)*ccw(a1,a2,b2);
    int y=ccw(b1,b2,a1)*ccw(b1,b2,a2);
    if(x>0||y>0) return 0; //触れていない
    if(x==0||y==0) return 1; // 触れている
    return 2; //交差している
}

S polyArea2(vector<P> ps){
    int n=si(ps);
    S ret=0;
    rep(i,n) ret+=cross(ps[i],ps[(i+1)%n]);
    return abs(ret); //面積の2倍 psが時計回りの場合は負になるためabs
}

int isConvex(vector<P> ps){
    int n=si(ps);
    if(n<3) return 0;
    int dir=0;
    rep(i,n){
        int t=ccw(ps[i],ps[(i+1)%n],ps[(i+2)%n]);
        if(t==0||t==-2||t==2) continue;
        if(dir==0) dir=t;
        if(dir!=t) return 0; // 凸ではない
    }
    dir=0;
    rep(i,n){
        int t=ccw(ps[0],ps[i],ps[(i+1)%n]);
        if(t==0||t==-2||t==2) continue;
        if(dir==0) dir=t;
        if(dir!=t) return -1; // 凸だが外角の和が360度ではない
    }
    return 1;
}

int inConvexContained(vector<P> ps,P a){
    int n=si(ps);
    int dir=0;
    rep(i,n){
        int t=ccw(ps[i],ps[(i+1)%n],a);
        if(t==2||t==-2) continue;
        if(t==0) return 1; //周に触れる
        if(dir==0) dir=t;
        if(t!=dir) return 0; //含まれない
    }
    return 2; //含まれる
}

int intersect_poly_segment(vector<P> ps,P a1,P a2){
    int n=si(ps);
    vector<pair<P,P>> dia;
    rep(i,n) dia.emplace_back(ps[i],ps[(i+1)%n]);
    rep(i,n/2) dia.emplace_back(ps[i],ps[i+n/2]);
    if(n>=4&&n%2) dia.emplace_back(ps.back(),ps[1]);
    for(auto [d1,d2]:dia){
        if(intersect_segment(d1,d2,a1,a2)==2){
            return 2; //内部を通過する
        }
    }
    rep(i,n) if(intersect_segment(ps[i],ps[(i+1)%n],a1,a2)==1) return 1; //周に触れる
    return 0; //触れない
}

vector<P> convex_hull(vector<P> ps,bool strict=true){  //共線点を排除するか
    int n=si(ps),k=0;
    sort(ps.begin(),ps.end());
    vector<P> ch(2*n);

    for(int i=0;i<n;ch[k++]=ps[i++]){
        while(k>=2&&cross(ch[k-1]-ch[k-2],ps[i]-ch[k-1])<strict)
            --k;
    }
    for(int i=n-2,t=k+1;i>=0;ch[k++]=ps[i--]){
        while(k>=t&&cross(ch[k-1]-ch[k-2],ps[i]-ch[k-1])<strict)
            --k;
    }
    ch.resize(k-1);
    return ch;
}

bool arglt(P a,P b){
    return (P(0,0)<a)==(P(0,0)<b)?a.x*b.y>a.y*b.x:a<b;
}