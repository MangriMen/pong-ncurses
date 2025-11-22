#include "game_over_scene.h"
#include "constants.h"
#include "graphics.h"
#include "ncurses_wrapper.h"

void draw_game_over_scene(GameConfig config, GameState state)
{
    int half_height = config.height / 2;
    int half_width = config.width / 2;

    draw_rectangle(0, 0, config.height, config.width);
    mvprintw(half_height - 2, half_width - 3, "Game Over");
    draw_score(half_height, half_width - 5, state.racket_1_score, state.racket_2_score);
    mvprintw(half_height + 2, half_width - 16, "Press Space to restart or Q to quit");
}

GameState process_game_over_scene(int key, GameConfig config, GameState state)
{
    if (key == QUIT_KEY) {
        state.current_scene = EXIT;
    }

    if (key == SKIP_KEY) {
        state = get_initial_state(config);
    }

    return state;
}