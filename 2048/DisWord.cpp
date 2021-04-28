#include "DisWord.h"

void insert_header(SDL_Surface *screen, SDL_Surface *encoding, int points)
{
    // chức năng in thông tin trong tiêu đề
    int header_colour = SDL_MapRGB(screen->format, 0xCD, 0x85, 0x3F);  // màu tiêu đề
    char *info = (char*)malloc(DL_INFORMATION * sizeof (char));
    // vẽ một hình vuông với tiêu đề
    DrawRectangle(screen, HEADER_STEP, HEADER_STEP, SCREEN_WIDTH - 2 * HEADER_STEP, HEAD_HEIGHT, header_colour, header_colour);
    sprintf (info, "2048");
    DrawString (screen, screen->w / 2 - strlen(info) * 8 / 2, 10, info, encoding);
    sprintf (info, "DUC TU 999");
    DrawString (screen, screen->w / 2 - strlen(info) * 8 / 2, 42, info, encoding);
    sprintf (info, "Points: %d", points);
    DrawString (screen, screen->w / 2 - strlen(info) * 8 / 2, 58, info, encoding);
    sprintf (info, "Esc - exit, n - new game, u - walk 1 step");
    DrawString (screen, screen->w / 2 - strlen(info) * 8 / 2, 74, info, encoding);
    free(info);
}
