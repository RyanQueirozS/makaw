#ifndef MAKAW_MATH_H
#define MAKAW_MATH_H

#include "mkwtypes.h"
#include <stdio.h>

MakawVec3 mkwmath_vec3_add(MakawVec3 a, MakawVec3 b) {
        return (MakawVec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

MakawVec2 mkwmath_vec2_add(MakawVec3 a, MakawVec3 b) {
        return (MakawVec2){a.x + b.x, a.y + b.y};
}

#endif // MAKAW_MATH_H
