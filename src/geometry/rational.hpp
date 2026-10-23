#pragma once
#include "../template.hpp"

struct Rational {
    long num, den;

    Rational(long n=0, long d=1):num(n), den(d){
        if(den==0) throw invalid_argument("den == 0");
        if(den<0) num=-num, den=-den;
        long g=gcd(abs(num), den);
        num/=g, den/=g;
    }

    Rational operator-()const {return {-num, den};}

    Rational operator+(const Rational& r)const {
        long g=gcd(den, r.den);
        return {num * (r.den/g)+r.num*(den/g),
                den * (r.den/g)};
    }

    Rational operator-(const Rational& r)const {return *this+(-r);}

    Rational mul(Rational r)const {
        long g1=gcd(abs(num), r.den), g2=gcd(abs(r.num), den);
        return {(num/g1)*(r.num/g2),
                (den/g2)*(r.den/g1)};
    }

    Rational operator*(const Rational& r)const {return mul(r);}

    Rational operator/(const Rational& r)const {
        if(r.num==0) throw invalid_argument("division by zero");
        return mul({r.den, r.num});
    }

    Rational& operator+=(const Rational& r){return *this=*this+r;}
    Rational& operator-=(const Rational& r){return *this=*this-r;}
    Rational& operator*=(const Rational& r){return *this=*this*r;}
    Rational& operator/=(const Rational& r){return *this=*this/r;}

    bool operator==(const Rational& r)const {
        return num==r.num&&den==r.den;
    }
    bool operator!=(const Rational& r)const {return !(*this==r);}

    bool operator<(const Rational& r)const {
        return num*(r.den/gcd(den, r.den))
               <r.num*(den/gcd(den, r.den));
    }
    bool operator>(const Rational& r)const {return r<*this;}
    bool operator<=(const Rational& r)const {return !(r<*this);}
    bool operator>=(const Rational& r)const {return !(*this<r);}
    friend ostream& operator<<(ostream& os, const Rational& r){
        os<<r.num;
        if(r.den!=1) os<<'/'<<r.den;
        return os;
    }
};