#include "../template.hpp"

using ld=long double;
using S=long;
struct P {
    S x,y;
    P(){}
    P(S x,S y):x(x),y(y) {} 
    //auto operator<=>(const P& o) const = default;
    bool operator==(const P&o)const{return x==o.x&&y==o.y;}
    bool operator<(const P& o)const{
        if(x!=o.x) return x<o.x;
        return y<o.y;
    }
    P operator-(){
        P res(*this);
        res.x*=-1;
        res.y*=-1;
        return res;
    }
    P operator+(const P& o) const { return P(x + o.x, y + o.y); }
    P& operator+=(const P& o) { return *this = *this + o; }
    P operator-(const P& o) const { return P(x - o.x, y - o.y); }
    P& operator-=(const P& o) { return *this = *this - o; }
    P operator*(S k) const { return P(x * k, y * k); }
    P& operator*=(S k) { return *this = *this * k; }
    P operator/(S k) const { return P(x / k, y / k); }
    P& operator/=(S k) { return *this = *this / k; }
    S real(){return x;}
    S imag(){return y;}
};

S dot(P a,P b){return a.x*b.x+a.y*b.y;}
S cross(P a,P b){return a.x*b.y-a.y*b.x;}
ld abs(P a){return sqrt(norm(a));}
S norm(P a){return dot(a,a);}

int ccw(P b, P c){
    if(cross(b,c)>0) return 1;  // counter-clockwise(反時計)
    if(cross(b,c)<0) return -1;  // clockwise(時計)
    if(dot(b,c)<0) return 2;  // c-a-b
    if(norm(b)<norm(c)) return -2; // a-b-c
    return 0; // a=c=b
}
int ccw(P a,P b,P c){
    b-=a;c-=a;
    return ccw(b,c);
}

bool is_orthogonal(P a1,P a2,P b1,P b2){
    return dot(a1-a2,b1-b2)==0;
}
bool is_parallel(P a1,P a2,P b1,P b2){
    return cross(a1-a2,b1-b2)==0;
} 
bool is_point_on_segment(P a1,P a2,P b){
    return ccw(a1,a2,b)==0;
}
bool is_point_on_line(P a1,P a2,P b){
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
    return ret; //面積の2倍 与えられるpsが時計回りの場合は負になる
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
int inPolygon(vector<P>& qs, P p0) {
    int cnt=0;
    int n=qs.size();
    rep(i,n){
        P a = qs[(i+n-1)%n];
        P b = qs[i];
        if(is_point_on_segment(a,b,p0)) return 1;
		a-=p0;
		b-=p0;
        if (ccw(a, b) == 2 || (cross(a, b) == 0 && dot(a, b) <= 0)) return true;
        if (a.imag() > b.imag()) swap(a, b);
        if (a.imag() <= 0 && 0 < b.imag() &&
            cross(a, b) > 0)
            cnt++;
    }
    if(cnt%2) return 2;
    return 0;
}

int inConvex(vector<P> ps,P a){ //凸
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
    assert(n>0);
    sort(ps.begin(),ps.end()); //戻り値の順番: (最小/最大) (x優先/y優先)
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

int argtype(P p){
    if (norm(p)==0) return 0;
    if (p.y>0||(p.y==0&&p.x>0)) return 1;
    return 2;
}
bool arglt(P a, P b){ //xの正軸から反時計回り
    if(argtype(a)!=argtype(b))return argtype(a)<argtype(b);
    S c=cross(a,b);
    if(c!=0) return c>0;
    return norm(a)<norm(b);
}

P conj(P a){
    return P(a.x,-a.y);
}
P multiply(P a,P b){return P(dot(a,conj(b)),cross(conj(a),b));}
pair<P,S> divide(P a,P b){
    return make_pair(multiply(a,conj(b)),norm(b));
    // return P(dot(b,a), cross(b,a))/norm(b);
}

S lnorm(P a, P d){
    S g=gcd(d.imag(),d.real());
    d/=g;
    if(d.imag()<0)d=-d;
    if(d.real()<0)d=-d;
    return -d.imag()*a.real()+d.real()*a.imag();
}

array<S,3> line_normalized(P a,P b){
    S dy=a.imag()-b.imag();
    S dx=b.real()-a.real();
    S c=-(a.real()*dy+a.imag()*dx);
    S g=gcd(gcd(dy,dx),c);
    if(dy<0) g*=-1;
    dy/=g,dx/=g,c/=g;
    return {dy,dx,c};
}

struct Line {
    P a, b;
    Line(P a=P(), P b=P()): a(a), b(b) {}
};
struct Circle {
    P p;
    S r;
    Circle(P p=P(), S r=0): p(p), r(r) {}
};
P vec(Line&s){return s.b-s.a;}