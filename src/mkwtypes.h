#ifndef MAKAW_TYPES_H
#define MAKAW_TYPES_H

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
        MakawVec2 position_top_left_vertex;
        float width_left_to_right, height_top_to_bottom;
} MakawSquare;

enum MakawShaderType {
        MAKAW_SHADER_VERTEX,
        MAKAW_SHADER_FRAGMENT,
};

typedef enum MakawStatus {
        MAKAW_FAILURE = 0,
        MAKAW_SUCCESS = 1,
} MakawStatus;

#endif // MAKAW_TYPES_H
