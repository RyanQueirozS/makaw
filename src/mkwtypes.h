#ifndef MAKAW_TYPES_H
#define MAKAW_TYPES_H

typedef struct {
        float x, y;
} MakawVec2;

typedef struct {
        float x, y, z;
} MakawVec3;

#define MAKAW_VEC2(_x, _y)                                                     \
        (MakawVec2) {                                                          \
                .x = _x, .y = _y                                               \
        }

enum MakawShaderType {
        MAKAW_SHADER_VERTEX,
        MAKAW_SHADER_FRAGMENT,
};

typedef enum MakawStatus {
        MAKAW_FAILURE = 0,
        MAKAW_SUCCESS = 1,
} MakawStatus;

#endif // MAKAW_TYPES_H
