#ifndef MAKAW_TYPES_H
#define MAKAW_TYPES_H

typedef enum MakawStatus {
        MAKAW_FAILURE = 0,
        MAKAW_SUCCESS = 1,
} MakawStatus;

enum MakawShaderType {
        MAKAW_SHADER_VERTEX,
        MAKAW_SHADER_FRAGMENT,
};

typedef struct {
        float x, y;
} MakawVec2;

typedef struct {
        float x, y, z;
} MakawVec3;

#define MAKAW_VEC3_TO_VEC2(_vec2, _z)                                          \
        (MakawVec3) {                                                          \
                (_vec2).x, (_vec2).y, (_z)                                     \
        }

typedef struct MakawSquare {
        MakawVec2 position_center;
        float width_x, height_y, depth_z;
} MakawSquare;

#endif // MAKAW_TYPES_H
