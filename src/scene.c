#include "scene.h"
#include "constants.h"
#include "game_over_scene.h"
#include "game_scene.h"
#include "ncurses_wrapper.h"
#include <stdbool.h>

void draw_scene(GameConfig config, GameState state)
{
    switch (state.current_scene) {
    case GAME:
        draw_game_scene(config, state);
        break;
    case GAME_OVER:
        draw_game_over_scene(config, state);
        break;
    default:
        break;
    }
}
