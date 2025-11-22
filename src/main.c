#include "constants.h"
#include "game.h"
#include <stdio.h>

int main()
{
    GameConfig config = {
        .width = 80,
        .height = 25,
        .racket_height = 3,
        .ball_size = 1
    };

    if (run(config) < 0) {
        return EXIT_FAILURE;
    };

    return EXIT_SUCCESS;
}
