#ifndef DISSQUARE_H_INCLUDED
#define DISSQUARE_H_INCLUDED

#include "CONST.h"


void DrawPixel (SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine (SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle (SDL_Surface *screen, int x, int y, int l, int k, Uint32 frame_color, Uint32 filling);

#endif // DISSQUARE_H_INCLUDED
