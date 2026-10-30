| ファイル | 関数 | 依存している関数（直接・間接） |
|---|---|---|
| base.hpp | angle_diff | なし |
| base.hpp | arglt | argtype, cross |
| base.hpp | ccw(a,b,c) | ccw(b,c), cross, dot |
| base.hpp | ccw(a,b) | cross, dot |
| base.hpp | projection | vec, dot |
| base.hpp | reflection | projection, vec, dot |
| intersect.hpp | intersect_cp | eq, sign |
| intersect.hpp | intersect_cl | distance_lp, projection, vec, dot, sign |
| intersect.hpp | intersect_cs | distance_sp, vec, dot, projection, eq, sign |
| intersect.hpp | contain_cs | eq, sign |
| intersect.hpp | crosspoint_ll | is_parallel, eq, sign, cross, vec |
| intersect.hpp | crosspoint_cl | projection, vec, dot, unitvector |
| intersect.hpp | crosspoint_cs | crosspoint_cl, projection, vec, dot, unitvector |
| intersect.hpp | crosspoint_cc | sqr |
| intersect.hpp | distance_ss | intersect_ss, ccw, cross, dot, distance_sp, vec, projection |
| intersect.hpp | distance_ls | vec |
| intersect.hpp | distance_cp | なし |
| intersect.hpp | distance_Cp | なし |
| intersect.hpp | distance_cc | なし |
| intersect.hpp | distance_CC | なし |
| intersect.hpp | intersect_ss | ccw, cross, dot |
| intersect.hpp | intersect_ls | ccw, cross, dot |
| intersect.hpp | intersect_sp | eq, sign, ccw, cross, dot |
| intersect.hpp | is_orthogonal | eq, sign, dot, vec |
| intersect.hpp | is_parallel | eq, sign, cross, vec |
| circle.hpp | circumcircle | cross |
| circle.hpp | incircle | cross |
| circle.hpp | excircle | なし |
| circle.hpp | count_tangent | sign, sqr |
| circle.hpp | intersect_cc | count_tangent, sign, sqr |
| circle.hpp | tangent_points | normalvector, sqr |
| circle.hpp | tangent | eq, sign, normalvector |
| circle.hpp | area(vector<P>,Circle&) | cross |
| circle.hpp | area(Circle) | sqr |
| circle.hpp | area(Circle,Circle) | sqr |
| circle.hpp | min_ball | cross |
| poly.hpp | poly_area | cross |
| poly.hpp | is_convex | ccw(a,b,c), ccw(b,c), cross, dot |
| poly.hpp | poly_contains | sign, cross, dot |
| poly.hpp | convex_contains | ccw(a,b,c), ccw(b,c), cross, dot |
| poly.hpp | convex_contains_log | ccw(a,b,c), ccw(b,c), cross, dot, intersect_sp, eq, sign |
| poly.hpp | intersect_poly_segment | intersect_ss, ccw, cross, dot |
| poly.hpp | convex_hull | cross |
| poly.hpp | convex_diamenter | cross |
| poly.hpp | convex_cut | cross, sign |
| arrangement.hpp | segment_arrangement | intersect_ss, ccw, cross, dot, is_parallel, eq, sign, vec, crosspoint_ll, intersect_sp |