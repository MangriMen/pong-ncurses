#include "game_scene.h"
#include "constants.h"
#include "graphics.h"
#include "ncurses_wrapper.h"
#include "physics.h"
#include <stdbool.h>

void draw_info(int y, int x, GameState state)
{
    draw_score(y, x, state.racket_1_score, state.racket_2_score);
    mvprintw(y, x + 13, "Racket 1: A/Z, Racket 2: K/M, Quit: Q, Skip: Space");
}

void draw_game_scene(GameConfig config, GameState state)
{
    draw_rectangle(0, 0, config.height, config.width);
    draw_racket(state.racket_1_position.y, state.racket_1_position.x, config.racket_height);
    draw_racket(state.racket_2_position.y, state.racket_2_position.x, config.racket_height);
    draw_ball(state.ball_position.y, state.ball_position.x);
    draw_info(config.height + 1, 1, state);
}

int move_racket(int y, int racket_height, int zone_height)
{
    if (y - 1 < 0) {
        return 1;
    } else if (y + racket_height > zone_height) {
        return zone_height - racket_height;
    } else {
        return y;
    }
}

GameState process_key(int key, GameConfig config, GameState state)
{
    if (key == QUIT_KEY) {
        state.current_scene = EXIT;
    }

    if (key == RACKET_1_KEY_UP) {
        state.racket_1_position.y = move_racket(state.racket_1_position.y - 1, config.racket_height, config.height);
    }

    if (key == RACKET_1_KEY_DOWN) {
        state.racket_1_position.y = move_racket(state.racket_1_position.y + 1, config.racket_height, config.height);
    }

    if (key == RACKET_2_KEY_UP) {
        state.racket_2_position.y = move_racket(state.racket_2_position.y - 1, config.racket_height, config.height);
    }

    if (key == RACKET_2_KEY_DOWN) {
        state.racket_2_position.y = move_racket(state.racket_2_position.y + 1, config.racket_height, config.height);
    }

    return state;
}

GameState move_ball(GameConfig config, GameState state)
{
    int next_ball_y = state.ball_position.y + state.ball_velocity.y;
    int next_ball_x = state.ball_position.x + state.ball_velocity.x;

    if (next_ball_y <= 1 || next_ball_y >= config.height - 1) {
        state.ball_velocity.y = -state.ball_velocity.y;
        next_ball_y = state.ball_position.y; // Оставляем на текущей позиции
    }

    bool collision_with_racket_1 = is_box_collision(
        next_ball_x, next_ball_y, config.ball_size, config.ball_size,
        state.racket_1_position.x, state.racket_1_position.y,
        RACKET_WIDTH, config.racket_height);

    bool collision_with_racket_2 = is_box_collision(
        next_ball_x, next_ball_y, config.ball_size, config.ball_size,
        state.racket_2_position.x, state.racket_2_position.y,
        RACKET_WIDTH, config.racket_height);

    if (collision_with_racket_1 || collision_with_racket_2) {
        state.ball_velocity.x = -state.ball_velocity.x;
        next_ball_x = state.ball_position.x;
    }

    bool intersects_with_left_wall = next_ball_x <= 1;
    bool intersects_with_right_wall = next_ball_x >= config.width - 1;

    // Goal
    if (intersects_with_left_wall || intersects_with_right_wall) {
        if (intersects_with_left_wall) {
            state.racket_2_score += 1;
        } else {
            state.racket_1_score += 1;
        }

        if (state.racket_1_score == GOALS_TO_WIN || state.racket_2_score == GOALS_TO_WIN) {
            state.current_scene = GAME_OVER;
        }

        state.ball_position.y = config.height / 2;
        state.ball_position.x = config.width / 2;
        state.ball_velocity.x = -state.ball_velocity.x;
        return state;
    }

    state.ball_position.y = next_ball_y;
    state.ball_position.x = next_ball_x;

    return state;
}

GameState process_updates(GameConfig config, GameState state, int frame_count)
{
    if (frame_count % BALL_PHYSICS_UPDATE_FRAMES_COUNT == 0) {
        state = move_ball(config, state);
    }

    return state;
}

GameState process_game_scene(int key, GameConfig config, GameState state, int frame_count)
{
    state = process_key(key, config, state);
    state = process_updates(config, state, frame_count);
    return state;
}
