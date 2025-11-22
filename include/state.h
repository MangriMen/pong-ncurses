#pragma once
#include "game.h"

typedef struct {
    int x;
    int y;
} Vector2;

typedef enum {
    EXIT,
    GAME,
    GAME_OVER,
} Scene;

typedef struct {
    int racket_1_score;
    int racket_2_score;
    Vector2 racket_1_position;
    Vector2 racket_2_position;
    Vector2 ball_position;
    Vector2 ball_velocity;
    Scene current_scene;
} GameState;

GameState get_initial_state(GameConfig config);

GameState update_state(int key, GameConfig config, GameState state, int frame_count);