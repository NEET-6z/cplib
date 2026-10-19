#include "../template.hpp"

// returns gcd(a, b) and assign x, y to integers
// s.t. ax + by = gcd(a, b) and |x| + |y| is minimized
long extgcd(long a, long b, long& x, long& y) {
   // assert(a >= 0 && b >= 0);
   if(!b) return x = 1, y = 0, a;
   long d = extgcd(b, a % b, y, x);
   y -= a / b * x;
   return d;
}
long inv_mod(long x, long md) {
   long y, z;
   extgcd(x, md, y, z);
   return (y % md + md) % md;
}