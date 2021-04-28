#include "CONST.h"
#include "Surface.h"
#include "Random_2.h"
#include "ResetG.h"
#include "CheckA.h"
#include "DisplayW.h"
#include "DisSquare.h"
#include "DisWord.h"
#include "Table.h"

void release_memory(cell_t *numbers, SDL_Surface *encoding, main_t image);

int main (int argc, char **argv)
{
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    int rc, points = 0, hm_animation  = 0, finish = 0, undo_points = 0;
    //một bảng cho biết hoạt ảnh của một ô nhất định đã kết thúc hay chưa
    discri_t *reset = (discri_t*)calloc(NUMBER_CHAMBERS*NUMBER_CHAMBERS, sizeof(discri_t));
    discri_t transition;
    discri_t close;
    discri_t victory, wining;
    discri_t for_traval; // đi lại
    direction_t direction; // hướng qua bảng
    cell_t *numbers = (cell_t*)malloc(NUMBER_NUMBERS*sizeof(cell_t));
    // một mảng chứa các ô đó của mảng yêu cầu hoạt ảnh
    board_cell_t * animation = (board_cell_t *)malloc(NUMBER_CHAMBERS*NUMBER_CHAMBERS * sizeof(board_cell_t));
    SDL_Event event;
    SDL_Surface *encoding = NULL; //chứa các ký tự để ghi vào màn hình
    main_t image;
    board_cell_t **board = (board_cell_t**)malloc(NUMBER_CHAMBERS * sizeof(board_cell_t*));

    for (int i = 0; i < NUMBER_CHAMBERS; i++) board[i] = (board_cell_t *)malloc(NUMBER_CHAMBERS * sizeof(board_cell_t));
	//bảng phụ với thông tin trước một nước đi nhất định - được sử dụng để hoàn tác
	board_cell_t **undoboard = (board_cell_t**)malloc(NUMBER_CHAMBERS * sizeof(board_cell_t*));
	for (int i = 0; i < NUMBER_CHAMBERS; i++) undoboard [i] = (board_cell_t *)malloc(NUMBER_CHAMBERS * sizeof(board_cell_t));
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &image.window, &image.renderer);
    if (rc != 0)
    {
        SDL_Quit();
        printf ("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        free(board);
        free(undoboard);
        free(numbers);
        free(reset);
        free(animation);
        return 1;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(image.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(image.renderer, 0, 0, 0, 255);
    image.screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    image.texture = SDL_CreateTexture(image.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_ShowCursor (SDL_DISABLE); //vô hiệu hóa khả năng hiển thị của con trỏ chuột
    image_bmp_init(&encoding, "cs8x8", image);
    SDL_SetColorKey(encoding, true, 0x000000);
    int background_color = SDL_MapRGB(image.screen->format, 0xFA, 0xEB, 0xD7); // trắng
    number_init(numbers, image);
    plansza_init(board);
    plansza_init(undoboard);
    animation_init(animation);
    close = transition = FALSE;
    for_traval = victory = FALSE;
    wining = FALSE;
    random_2(numbers, board);
    random_2(numbers, board);
    while (close == FALSE)
    {
        if (for_traval == TRUE) //hoàn tác 1 bước đi
        {
            // sao chép nội dung của bảng phụ sang bảng gốc, thao tác này sẽ hoàn tác việc di chuyển
            copy_board(undoboard, board);
            points = undo_points; // khôi phục điểm về trạng thái trước đó
            for_traval = FALSE;
        }
        if (transition == TRUE) //người chơi nhấn các mũi tên, điều đó có nghĩa là phải đi trên bảng và di chuyển các ô
        {
            copy_board(board, undoboard); //sao chép nội dung của bảng vào bảng phụ
            undo_points = points;
            walk(board, direction, &points); //di chuyển
            transition = FALSE;
        }
        SDL_FillRect(image.screen, NULL, background_color); //cung cấp cho màn hình một màu sắc
        insert_header(image.screen, encoding, points);
        insert_plansze(image, board, numbers, &for_traval);
        // nếu không ở trong quá trình tạo hoạt ảnh, kiểm tra xem chúng tôi có nên tạo hoạt ảnh không sau khi chuyển đổi
        if (hm_animation == 0) OrAnimation(board, numbers, animation, &hm_animation);
        else
        {
            Animations(animation, direction, &hm_animation, &finish, image, reset, board, numbers);

            if (hm_animation == finish) // kết thúc hoạt ảnh
            {
            hm_animation = finish = 0;
            for (int i = 0; i <NUMBER_CHAMBERS*NUMBER_CHAMBERS; i++) reset[i] = FALSE;
            animation_init(animation);
            random_2(numbers, board);
            }
        }
        SDL_UpdateTexture(image.texture, NULL, image.screen->pixels, image.screen->pitch);
        SDL_RenderClear(image.renderer);
        SDL_RenderCopy(image.renderer, image.texture, NULL, NULL);
        SDL_RenderPresent(image.renderer);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) close = TRUE; // thoát - thoát khỏi trò chơi
                    if (hm_animation == 0 && victory == FALSE)
                    {
                        if (event.key.keysym.sym == SDLK_n)
                        {
                            plansza_init(board);
                            random_2(numbers, board);
                            random_2(numbers, board);
                            points = 0;
                        }
                        else if (event.key.keysym.sym == SDLK_LEFT)
                        {
                            direction = LEFT;
                            transition = TRUE;

                        }
                        else if (event.key.keysym.sym == SDLK_RIGHT)
                        {
                            direction = RIGHT;
                            transition = TRUE;
                        }
                        else if (event.key.keysym.sym == SDLK_UP)
                        {
                            direction = UP;
                            transition = TRUE;
                        }
                        else if (event.key.keysym.sym == SDLK_DOWN)
                        {
                            direction = DOW;
                            transition = TRUE;
                        }
                        else if (event.key.keysym.sym == SDLK_u) for_traval = TRUE;
                    }
                break;
                case SDL_QUIT:
                close = TRUE;
                break;
            }
        }
    }
    release_memory(numbers, encoding, image);
    free(board);
    free(undoboard);
    free(numbers);
    free(reset);
    free(animation);
    return 0;
}


void release_memory(cell_t *numbers, SDL_Surface *encoding, main_t image)
{
    SDL_FreeSurface(encoding);
    SDL_FreeSurface(image.screen);
    SDL_DestroyTexture(image.texture);
    SDL_DestroyRenderer(image.renderer);
    SDL_DestroyWindow(image.window);
    for (int i = 0; i <NUMBER_NUMBERS; i ++) SDL_FreeSurface(numbers[i].picture);
    SDL_Quit();
}

