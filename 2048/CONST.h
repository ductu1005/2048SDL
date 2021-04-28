#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#include<math.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#define SCREEN_WIDTH 1000 // chieu rong man
#define SCREEN_HEIGHT 700 // chieu all màn
#define DL_INFORMATION 128
#define DL_NAPIS 32
#define HEAD_HEIGHT 100
#define HEADER_STEP 4
#define BOARD_BOARD_SIZE 450
#define CHAMBER_SIZE 100
#define BEG_HEIGHT_PLAN 150
#define SPLIT_SUMP_KOMORKI 10
#define NUMBER_CHAMBERS 4
#define NUMBER_NUMBERS 12
#define GAME_END 2048
#define NO_PICTURE 0

typedef struct
{
    int first;
    int second;
} order_t;

typedef enum
{
    FALSE,
    TRUE
} discri_t;

typedef enum
{
    UP,
    DOW,
    RIGHT,
    LEFT
} direction_t;

typedef struct
{
    //cấu trúc mô tả các thuộc tính của một hình ảnh nhất định - diện tích và giá trị, tức là số mà hình ảnh chứa
    SDL_Surface *picture;
    int value;
} cell_t;



typedef struct
{
    // các trường mô tả bảng
    order_t coordinates; //hằng số - xác định tọa độ của góc trên cùng của ô
    int value; //số có chứa hình ảnh trên ô đã cho, 0 - không có hình ảnh
    order_t new_coordinates; //tọa độ mà ô sẽ đi qua hoạt ảnh
    discri_t combined; //xác định xem một ô có được kết hợp thành một hay không
    discri_t unchanged; //xác định xem sẽ có hoạt ảnh trên ô
} board_cell_t;

typedef struct
{
    SDL_Texture *texture;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *screen;
} main_t;

#endif // CONST_H_INCLUDED
