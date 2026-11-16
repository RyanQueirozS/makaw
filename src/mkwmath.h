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

MakawVec3 mkwmath_vec3_add_scalar(MakawVec3 vec3, float _x, float _y,
                                  float _z) {
        return (MakawVec3){vec3.x + _x, vec3.y + _y, vec3.z + _z};
}

#endif // MAKAW_MATH_H
