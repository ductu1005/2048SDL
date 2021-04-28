#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include "CONST.h"

void DrawSurface (SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

//hàm lấy hình ảnh BMP từ tệp
void image_bmp_init (SDL_Surface **imaged, char *image_name, main_t image);
void number_init (cell_t *numbers, main_t image);

#endif // SURFACE_H_INCLUDED
