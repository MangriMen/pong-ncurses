#include "state.h"
#include "constants.h"
#include "game.h"
#include "game_over_scene.h"
#include "game_scene.h"
#include "physics.h"
#include <stdlib.h>

GameState get_initial_state(GameConfig config)
{
    int half_height = config.height / 2;
    int half_width = config.width / 2;

    GameState state = {
        .racket_1_score = 0,
        .racket_2_score = 0,
        .racket_1_position = { .y = half_height / 2, .x = 1 },
        .racket_2_position = { .y = half_height / 2, .x = config.width - 1 },
        .ball_position = { .y = half_height, .x = half_width },
        .ball_velocity = { .y = 1, .x = 1 },
        .current_scene = GAME,
    };

    return state;
}

GameState update_state(int key, GameConfig config, GameState state, int frame_count)
{
    switch (state.current_scene) {
    case GAME:
        return process_game_scene(key, config, state, frame_count);
    case GAME_OVER:
        return process_game_over_scene(key, config, state);
    default:
        return state;
    }
}
