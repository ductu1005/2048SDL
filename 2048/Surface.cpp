#include "Surface.h"

void DrawSurface (SDL_Surface *screen, SDL_Surface *sprite, int x, int y)
{
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface (sprite, NULL, screen, &dest);
}

void image_bmp_init (SDL_Surface **imaged, char *image_name, main_t image)
{
    // đọc ảnh từ tệp
    char path [DL_NAPIS] = "./GRAPHICS/";
    // Nối chuỗi của đối số thứ hai với đối số đầu tiên
    strcat (path, image_name);
    strcat (path, ".bmp");
    *imaged = SDL_LoadBMP (path);
    if (*imaged == NULL)
    {
        printf("SDL_LoadBMP () error: %s\n", SDL_GetError());
        SDL_FreeSurface(image.screen);
        SDL_DestroyTexture(image.texture);
        SDL_DestroyWindow(image.window);
        SDL_DestroyRenderer(image.renderer);
        SDL_Quit();
        return;
    }
}

void number_init(cell_t *numbers, main_t image)
{
    int i;
    char *chain = (char*)malloc(DL_NAPIS * sizeof (char));
    for (i = 0; i < NUMBER_NUMBERS; i ++)
    {
        numbers[i].value = pow(2 , i+1);
        numbers[i].picture = NULL;
        sprintf (chain, "%d", numbers[i].value); //chuyển đổi giá trị thành chuỗi
        image_bmp_init(&numbers[i].picture, chain, image); //khởi tạo hình ảnh
    }
    free(chain);
}
