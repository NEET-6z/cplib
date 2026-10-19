#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E"
#include "../math/extgcd.hpp"

int main(){
	cin.tie(0)->ios::sync_with_stdio(0);
	
	long a,b,x,y;
	cin>>a>>b;
	extgcd(a,b,x,y);
	cout<<x<<" "<<y<<"\n";
}