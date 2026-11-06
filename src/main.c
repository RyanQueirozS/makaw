#include "makaw.h"
#include "mkwtypes.h"
#include <stdio.h>

int main(void) {
        if (!makaw_init()) {
                return 1;
        }

        while (makaw_is_running()) {
                makaw_clear();
                // makaw_draw_triangle(MAKAW_VEC2(-0.5, -0.5),
                //                     MAKAW_VEC2(0.5, -0.5), MAKAW_VEC2(0,
                //                     0.5));
                makaw_draw_square(MAKAW_VEC2(-0.5, 0.5), 1, 1);
                makaw_present();
        }

        makaw_exit();
}
