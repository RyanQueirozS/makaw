#include "makaw.h"
#include "mkwtypes.h"

int main(void) {
        if (!makaw_init()) {
                return 1;
        }

        while (makaw_is_running()) {
                makaw_clear();
                makaw_draw_triangle((MakawVec2){-1, -0.5},
                                    (MakawVec2){0, -0.5}, (MakawVec2){-0.5,
					0.5});
                makaw_draw_square((MakawSquare){(MakawVec2){-0.5, 0.5}, 1, 1});
                makaw_present();
        }

        makaw_exit();
}
