#include "DisplayW.h"

void DrawString (SDL_Surface *screen, int x, int y, const char *chain, SDL_Surface *charset)
{
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*chain)
    {
        c = *chain & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface (charset, &s, screen, &d);
        x += 8;
        chain++;
    }
}
