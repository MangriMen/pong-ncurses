#pragma once

typedef struct {
    int width;
    int height;
    int racket_height;
    int ball_size;
} GameConfig;

int run(GameConfig config);

int init(GameConfig config);
int check_terminal_size(GameConfig config);
void dispose();

void run_game_cycle(GameConfig config);