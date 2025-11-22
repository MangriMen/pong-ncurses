#include "game.h"
#include "constants.h"
#include "ncurses_wrapper.h"
#include "scene.h"
#include "state.h"
#include <stdbool.h>
#include <stdio.h>

int run(GameConfig config)
{
    int result = init(config);
    if (result < 0) {
        return result;
    };

    run_game_cycle(config);

    dispose();

    return EXIT_SUCCESS;
}

int init(GameConfig config)
{

    initscr();

    int result = check_terminal_size(config);
    if (result < 0) {
        dispose();
        return result;
    }

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    return EXIT_SUCCESS;
}

int check_terminal_size(GameConfig config)
{
    int mrow;
    int mcol;

    getmaxyx(stdscr, mrow, mcol);

    if (mrow < config.height || mcol < config.width) {
        fprintf(stderr, "Terminal too small\nCurrent size: %dx%d\nMinimum size: %dx%d\n", mcol, mrow, config.width, config.height);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void dispose()
{
    keypad(stdscr, FALSE);
    nodelay(stdscr, FALSE);
    endwin();
}

void render(GameConfig config, GameState state)
{
    clear();
    draw_scene(config, state);
    refresh();
}

void run_game_cycle(GameConfig config)
{
    GameState state = get_initial_state(config);

    int frame_count = 0;
    int ch = 0;
    while (true) {
        ch = getch();

        state = update_state(ch, config, state, frame_count);

        if (state.current_scene == EXIT) {
            break;
        }

        render(config, state);

        frame_count++;

        napms(TARGET_FRAME_TIME);
    }
}
