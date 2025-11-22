#pragma once

#include "game.h"
#include "state.h"
#include <stdbool.h>

void draw_game_scene(GameConfig config, GameState state);

GameState process_game_scene(int key, GameConfig config, GameState state, int frame_count);
