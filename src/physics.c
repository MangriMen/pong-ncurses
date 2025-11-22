#include "physics.h"

bool is_box_collision(int rect1_x, int rect1_y, int rect1_width, int rect1_height,
    int rect2_x, int rect2_y, int rect2_width, int rect2_height)
{
    return (rect1_x < rect2_x + rect2_width && rect1_x + rect1_width > rect2_x && rect1_y < rect2_y + rect2_height && rect1_y + rect1_height > rect2_y);
}