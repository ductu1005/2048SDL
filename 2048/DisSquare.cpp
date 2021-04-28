#include "DisSquare.h"

void DrawPixel (SDL_Surface *surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32 *)p = color;
}

void DrawLine (SDL_Surface * screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
    for (int i = 0; i < l; i ++)
    {
        DrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    }
}

void DrawRectangle (SDL_Surface *screen, int x, int y, int l, int k, Uint32 frame_color, Uint32 filling)
{
    int i;
    DrawLine(screen, x, y, k, 0, 1, frame_color);
    DrawLine(screen, x + l - 1, y, k, 0, 1, frame_color);
    DrawLine(screen, x, y, l, 1, 0, frame_color);
    DrawLine(screen, x, y + k - 1, l, 1, 0, frame_color);
    for (i = y + 1; i < y + k - 1; i++)
        DrawLine(screen, x + 1, i, l - 2, 1, 0, filling);
}
