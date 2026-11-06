#ifndef MAKAW_H
#define MAKAW_H

#ifndef MAKAW_API
#define MAKAW_API
#endif // MAKAW_API

#include "mkwtypes.h"

MAKAW_API MakawStatus makaw_init();
MAKAW_API void makaw_exit();
MAKAW_API MakawStatus makaw_is_running();
MAKAW_API void makaw_clear();
MAKAW_API void makaw_draw_triangle(MakawVec2 vertex_a, MakawVec2 vertex_b,
                                   MakawVec2 vertex_c);
MAKAW_API void makaw_draw_square(MakawVec2 position_top_left,
                                 float height_bottom, float lenght_right);
MAKAW_API void makaw_draw_quad(MakawVec2 vertex_a, MakawVec2 vertex_b,
                               MakawVec2 vertex_c, MakawVec2 vertex_d);
MAKAW_API void makaw_present();

#endif // MAKAW_H
