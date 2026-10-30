| 関数 | 依存している関数（直接・間接） |
|---|---|
| angle_diff | なし |
| arglt | argtype, cross |
| ccw(a,b,c) | ccw(b,c), cross, dot |
| ccw(a,b) | cross, dot |
| projection | vec, dot |
| reflection | projection, vec, dot |

| intersect_cp | eq, sign |
| intersect_cl | distance_lp, projection, vec, dot, sign |
| intersect_cs | distance_sp, vec, dot, projection, eq, sign |
| intersect_ss | ccw, cross, dot |
| intersect_ls | ccw, cross, dot |
| intersect_sp | eq, sign, ccw, cross, dot |
| contain_cs | eq, sign |
| crosspoint_ll | is_parallel, eq, sign, cross, vec |
| crosspoint_cl | projection, vec, dot, unitvector |
| crosspoint_cs | crosspoint_cl, projection, vec, dot, unitvector |
| crosspoint_cc | sqr |
| distance_ss | intersect_ss, ccw, cross, dot, distance_sp, vec, projection |
| distance_ls | vec |
| distance_cp | なし |
| distance_Cp | なし |
| distance_cc | なし |
| distance_CC | なし |
| is_orthogonal | eq, sign, dot, vec |
| is_parallel | eq, sign, cross, vec |

| circumcircle | cross |
| incircle | cross |
| excircle | なし |
| count_tangent | sign, sqr |
| intersect_cc | count_tangent, sign, sqr |
| tangent_points | normalvector, sqr |
| tangent | eq, sign, normalvector |
| area(vector,Circle&) | cross |
| area(Circle) | sqr |
| area(Circle,Circle) | sqr |
| min_ball | cross |

| poly_area | cross |
| is_convex | ccw(a,b,c), ccw(b,c), cross, dot |
| poly_contains | sign, cross, dot |
| convex_contains | ccw(a,b,c), ccw(b,c), cross, dot |
| convex_contains_log | ccw(a,b,c), ccw(b,c), cross, dot, intersect_sp, eq, sign |
| intersect_poly_segment | intersect_ss, ccw, cross, dot |
| convex_hull | cross |
| convex_diamenter | cross |
| convex_cut | cross, sign |
| segment_arrangement | intersect_ss, ccw, cross, dot, is_parallel, eq, sign, vec, crosspoint_ll, intersect_sp |