#include "Table.h"


void insert_plansze (main_t image, board_cell_t **board, cell_t *numbers, discri_t *victory)
{
    int cell_colour = SDL_MapRGB (image.screen->format, 0xD3, 0xD3, 0xD3);
    int plan_colour = SDL_MapRGB (image.screen->format, 0xA9, 0xA9, 0xA9);
    int start = SCREEN_WIDTH / 4;
    int i, j, it, x, y;
    // vẽ một hình vuông lớn tối hơn làm nền cho các ô
    DrawRectangle(image.screen, start, BEG_HEIGHT_PLAN, BOARD_BOARD_SIZE, BOARD_BOARD_SIZE, plan_colour, plan_colour);
    for (i = 0; i <NUMBER_CHAMBERS; i++)
    {
        for (j = 0; j <NUMBER_CHAMBERS; j++)
        {
            board[i][j].combined = FALSE;
            if (board[i][j].value == NO_PICTURE || board[i][j].unchanged == FALSE)
            {
                // nếu giá trị là 0 có nghĩa là hình ảnh không được nằm trên ô này
                // nếu nó luôn là False, có nghĩa là trong ô này sẽ có một bức ảnh có hoạt ảnh vẫn đang được xử lý
                DrawRectangle(image.screen, board[i][j].coordinates.first, board[i][j].coordinates.second, CHAMBER_SIZE, CHAMBER_SIZE, cell_colour, cell_colour);
            }
            else if (board[i][j].unchanged == TRUE)
            {
            // đối với những hình ảnh không có hoạt ảnh và được cho là - giá trị của chúng khác 0
            // xác định tọa độ
            // + CHAMBER_SIZE / 2 - vì DrawSurface lấy tâm của hình ảnh
            x = board[i][j].coordinates.first + CHAMBER_SIZE / 2;
            y = board[i][j].coordinates.second + CHAMBER_SIZE / 2;
            if (board[i][j].value == GAME_END)(* victory) = TRUE;
            it = log2(double(board[i][j].value)) - 1; // xác định chỉ số trong bảng số dựa trên giá trị ô
            DrawSurface(image.screen, numbers[it].picture, x, y); // ve bảng
            }
        }
    }
}

void plansza_init (board_cell_t **board)
{

    int start = SCREEN_WIDTH / 4;
    int i, j, shift, row;
    for (i = 0; i <NUMBER_CHAMBERS; i++)
    {
        row = i * (CHAMBER_SIZE + SPLIT_SUMP_KOMORKI) + SPLIT_SUMP_KOMORKI;
        for (j = 0; j <NUMBER_CHAMBERS; j++)
        {
            shift = SPLIT_SUMP_KOMORKI * (j + 1) + CHAMBER_SIZE * j;
            board[i][j].coordinates.first = start + shift;
            board[i][j].coordinates.second = BEG_HEIGHT_PLAN + row;
            board[i][j].new_coordinates = {};
            board[i][j].value = NO_PICTURE;
            board[i][j].combined = FALSE;
            board[i][j].unchanged = TRUE;
        }
    }
}

void copy_board(board_cell_t **board, board_cell_t **board_cop)
{
    int i, j;
    for (i = 0; i <NUMBER_CHAMBERS; i++)
    {
        for (j = 0; j <NUMBER_CHAMBERS; j++)
        {
            board_cop[i][j].value = board[i][j].value;
            board_cop[i][j].new_coordinates = {};
            board_cop[i][j].unchanged = TRUE;
            board_cop[i][j].combined = FALSE;
        }
    }
}


