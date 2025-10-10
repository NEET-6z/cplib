#include "template.hpp"

inline array<long, 3> line_normalized(long sy, long sx, long ty, long tx) {
    long a = sy - ty;
    long b = tx - sx;
    long c = -(sx * a + sy * b);
    long g = gcd(gcd(a, b), c);
    a /= g;
    b /= g;
    c /= g;
    if(a < 0) a *= -1, b *= -1, c *= -1;
    return {a, b, c};
}