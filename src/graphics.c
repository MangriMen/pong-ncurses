#include "graphics.h"
#include "constants.h"
#include "ncurses_wrapper.h"
#include <stdbool.h>

void draw_score(int y, int x, int racket_1_score, int racket_2_score)
{
    mvprintw(y, x, "Score: %02d/%02d", racket_1_score, racket_2_score);
}

void draw_racket(int y, int x, int height)
{
    draw_vertical_line(y, x, height);
}

void draw_ball(int y, int x)
{
    mvaddch(y, x, BALL);
}

void draw_rectangle(int y, int x, int height, int width)
{
    int ul_corner_y = y;
    int ul_corner_x = x;

    int ur_corner_y = y;
    int ur_corner_x = x + width;

    int lr_corner_y = y + height;
    int lr_corner_x = x + width;

    int ll_corner_y = y + height;
    int ll_corner_x = x;

    mvaddch(ul_corner_y, ul_corner_x, CORNER_UL);

    draw_horizontal_line(ul_corner_y, ul_corner_x + 1, width - 1);

    mvaddch(ur_corner_y, ur_corner_x, CORNER_UR);

    draw_vertical_line(ur_corner_y + 1, ur_corner_x, height - 1);

    mvaddch(lr_corner_y, lr_corner_x, CORNER_LR);

    draw_horizontal_line(ll_corner_y, ll_corner_x + 1, width - 1);

    mvaddch(ll_corner_y, ll_corner_x, CORNER_LL);

    draw_vertical_line(ul_corner_y + 1, ll_corner_x, height - 1);
}

void draw_horizontal_line(int y, int x, int width)
{
    for (int i = x; i < x + width; i++) {
        mvaddch(y, i, HORIZONTAL_LINE);
    }
}

void draw_vertical_line(int y, int x, int height)
{
    for (int i = y; i < y + height; i++) {
        mvaddch(i, x, VERTICAL_LINE);
    }
}
