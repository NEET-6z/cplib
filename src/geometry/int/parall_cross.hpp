#include "../../template.hpp"

optional<P> parall_cross(P a1,P a2,P b1,P b2){
    auto [x1,y1]=a1;
    auto [x2,y2]=a2;
    auto [x3,y3]=b1;
    auto [x4,y4]=b2;
    auto [ax0,ax1]=minmax(x1,x2);
    auto [ay0,ay1]=minmax(y1,y2);
    auto [bx0,bx1]=minmax(x3,x4);
    auto [by0,by1]=minmax(y3,y4);
    int ix0=max(ax0,bx0),ix1=min(ax1,bx1);
    int iy0=max(ay0,by0),iy1=min(ay1,by1);
    if(ix0>ix1||iy0>iy1) return nullopt;
    return {{ix0,iy0}};
}