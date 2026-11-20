#ifndef MAKAW_H
#define MAKAW_H

#include <stdint.h>

#include "mkwtypes.h"

#ifndef MAKAW_API
#define MAKAW_API
#endif // MAKAW_API

MAKAW_API MakawStatus makaw_init();
MAKAW_API void makaw_exit();
MAKAW_API MakawStatus makaw_is_running();
MAKAW_API void makaw_clear();
MAKAW_API void makaw_draw_triangle(MakawVec2 vertex_a, MakawVec2 vertex_b,
                                   MakawVec2 vertex_c);
MAKAW_API void makaw_draw_rectangle(MakawRectangle rectangle);
MAKAW_API void makaw_draw_cuboid(MakawCuboid cuboid);
MAKAW_API void makaw_present();

#endif // MAKAW_H
