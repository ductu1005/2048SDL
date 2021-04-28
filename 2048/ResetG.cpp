#include "ResetG.h"

void animation_init (board_cell_t *animation)
{
    for (int i = 0; i <NUMBER_CHAMBERS * NUMBER_CHAMBERS; i++)
    {
        animation[i].coordinates = {};
        animation[i].new_coordinates = {};
        animation[i].value = NO_PICTURE;
        animation[i].combined = FALSE;
    }
}

order_t set_start (order_t start, direction_t direction)
{
    //đặt thời điểm bắt đầu lặp lại bảng
    //bỏ qua hàng/cột cuối cùng/đầu tiên vì bạn không thể di chuyển các ô từ đó
    switch (direction)
    {
        case LEFT:
            start.first = 0;
            start.second = 1;
        break;

        case RIGHT:
            start.first = 0;
            start.second = HEADER_STEP - 2;
        break;

        case UP:
            start.first = 1;
            start.second = 0;
        break;

        case DOW:
            start.first = HEADER_STEP - 2;
            start.second = 0;
        break;
    }
    return start;
}


order_t converting(order_t coordinates)
{
    // hàm chuyển đổi tọa độ bảng điều khiển thành các chỉ mục trong bảng bảng
    order_t result;
    result.first = (coordinates.second - BEG_HEIGHT_PLAN - SPLIT_SUMP_KOMORKI) / (CHAMBER_SIZE + SPLIT_SUMP_KOMORKI);
    result.second = (coordinates.first - SCREEN_WIDTH / 4 - SPLIT_SUMP_KOMORKI) / (CHAMBER_SIZE + SPLIT_SUMP_KOMORKI);
    return result;
}

void Animations(board_cell_t *animation, direction_t direction, int *hm_to_animation , int *hm_posed,
                   main_t image, discri_t *reset, board_cell_t **board, cell_t *numbers)
{
    int i = 0, it;
    order_t indexes;
    for (i = 0; i < (*hm_to_animation); i++)
    {
        // nếu hoạt ảnh đã hoàn thành
        if (animation[i].coordinates.first == animation[i].new_coordinates.first && animation[i].coordinates.second == animation[i].new_coordinates.second)
        {
            if (reset[i] == FALSE) //không đánh dấu nó đã kết thúc
            {
                (*hm_posed)++;
                reset[i] = TRUE; //lưu ý rằng hoạt ảnh đã kết thúc
                // bây giờ ô này là hằng số, vì vậy nó sẽ được hiển thị trong hàm insert_plansze
                indexes = converting(animation[i].new_coordinates);
                board[indexes.first][indexes.second].unchanged = TRUE;
            }
        }
        else
        {
            //tăng tọa độ tùy thuộc vào hướng
            if (direction == RIGHT) animation[i].coordinates.first += 10;
            if (direction == LEFT) animation[i].coordinates.first -= 10;
            if (direction == UP) animation[i].coordinates.second -= 10;
            if (direction == DOW) animation[i].coordinates.second += 10;
            // in hình
            it = log2((double)(animation[i].value)) - 1;
            DrawSurface(image.screen, numbers[it].picture, animation[i].coordinates.first, animation[i].coordinates.second);
        }
    }
}
