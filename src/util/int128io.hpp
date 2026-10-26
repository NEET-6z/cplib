#include "../template.hpp"


istream& operator>>(istream& is, i128& x){
    string s;
    is>>s;
    x=0;
    bool neg=false;
    int i=0;
    if(s[0]=='-'){
        neg=true;
        i=1;
    }
    else if(s[0]=='+'){
        i=1;
    }
    for(;i<(int)s.size();++i){
        x=x*10+(s[i]-'0');
    }
    if(neg) x=-x;
    return is;
}

ostream& operator<<(ostream& os, i128 x){
    if(x==0) return os<<'0';
    if(x<0){
        os<<'-';
        __uint128_t u=-(__uint128_t)x;
        string s;
        while(u>0){
            s+=char('0'+u%10);
            u/=10;
        }
        reverse(s.begin(), s.end());
        return os<<s;
    }

    string s;
    while(x>0){
        s+=char('0'+x%10);
        x/=10;
    }

    reverse(s.begin(), s.end());
    return os<<s;
}