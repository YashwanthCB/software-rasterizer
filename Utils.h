//
// Created by yashwanth on 3/15/26.
//

#ifndef RASTERYZEN_UTILS_H
#define RASTERYZEN_UTILS_H
#include <string>

#include "Types.h"

class Utils {

public:
    static void load_wavefront(const std::string& filename);

    static float signed_area(const TriangleDC& tri){
        return 0.5f * ( tri.x1*( tri.y2 - tri.y3 ) + tri.x2*( tri.y3 - tri.y1 ) + tri.x3*( tri.y1 - tri.y2 ) );
    }
};
//1200-400+1000-3000+3000-1800

#endif //RASTERYZEN_UTILS_H