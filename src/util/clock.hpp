#include "../template.hpp"

auto now(){
    return chrono::system_clock::now();
}
int get_time(auto t0,auto t1){
    auto elapsed=chrono::duration_cast<chrono::milliseconds>(t1-t0);
    return elapsed.count();
}