#include "CheckA.h"

order_t set_begin(order_t start, direction_t direction)
{
    // đặt thời điểm bắt đầu lặp lại bảng
    // bỏ qua hàng/cột cuối cùn/đầu tiên vì không thể di chuyển các ô từ đó
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

discri_t condition(int it, direction_t direction)
{
    // điều kiện xác định sự kết thúc của lặp tùy thuộc vào hướng
    discri_t flag = TRUE;
    if (direction == LEFT || direction == UP)
    if (it >= NUMBER_CHAMBERS) flag = FALSE;
    if (direction == RIGHT || direction == DOW)
    if (it < 0) flag = FALSE;
    return flag;
}


direction_t directions(direction_t direction)
{
    // xác định hướng ngược lại
    if (direction == RIGHT) return LEFT;
    if (direction == LEFT) return RIGHT;
    if (direction == UP) return DOW;
    if (direction == DOW) return UP;
}

int iteration(int it, direction_t direction)
{
    // lặp lại tùy thuộc vào hướng
    if (direction == LEFT || direction == UP) it ++;
    if (direction == RIGHT || direction == DOW) it--;
    return it;
}

void walk(board_cell_t **board, direction_t direction, int *points)
{
    order_t start = {};
    start = set_begin(start, direction);
    direction_t inverted = directions(direction); // thiết lập hướng đảo ngược
    int i, j, k;
    board_cell_t *CursorMove ;

    if (direction == LEFT || direction == RIGHT)
    {
        for (i = start.first; i <NUMBER_CHAMBERS; i++)
        {
            for (j = start.second; condition(j, direction); j = iteration(j, direction))
            {
                if (board[i][j].value != NO_PICTURE)
                {
                    CursorMove = &(board[i][j]);
                    k = iteration(j, inverted);
                    while (condition(k, inverted))
                    {
                        // nếu các giá trị giống nhau và không trỏ đến một ô kết hợp
                        if (board[i][k].value == CursorMove->value && CursorMove->combined == FALSE)
                        {
                            board[i][k].value = 2 * CursorMove->value; // giá trị trong ô mới được ghi lại nhiều gấp đôi
                            CursorMove->combined = TRUE; //chỉ định rằng một cái trước đó sẽ được chọn, để không có thêm cái nào được liên kết
                            *points += board[i][k].value; // cộng điểm
                            board[i][j].new_coordinates = board[i][k].coordinates; //thay đổi các tọa độ mới, tức là những tọa độ sẽ đến trong quá trình đặt tên
                            CursorMove->value = NO_PICTURE; // hình ảnh đã di chuyển vì vậy không có hình ảnh trong ô ban đầu
                            CursorMove->unchanged = TRUE; //  ô ban đầu là không đổi
                            CursorMove =&(board[i][k]); // đến ô tiếp theo
                            CursorMove->combined = TRUE;
                            CursorMove->unchanged = FALSE;
                        }
                        else if (board[i][k].value  == NO_PICTURE) // nếu ô tiếp theo không có hình ảnh
                        {
                            board[i][k].value = CursorMove->value; //ghi giá trị vào nó
                            board[i][j].new_coordinates = board[i][k].coordinates; //lưu các tọa độ cho hoạt ảnh
                            CursorMove->value = NO_PICTURE; //di chuyển bức tranh
                            CursorMove->unchanged = TRUE; //ô ban đầu sẽ không đổi
                            CursorMove = &(board[i][k]); //  đến ô tiếp theo
                            CursorMove->unchanged = FALSE; // hình sẽ ở đó
                        }
                        else break;
                        k = iteration(k, inverted);
                    }
                }
            }
        }
    }
    else
    {
        for (j = start.second; j <NUMBER_CHAMBERS; j++)
        {
            for (i = start.first; condition(i, direction); i = iteration(i, direction))
            {
                if (board[i][j].value != NO_PICTURE) // nếu có hình
                {
                    CursorMove = &(board[i][j]);
                    k = iteration(i, inverted); // continue
                    while (condition (k, inverted))
                    {
                        if (board[k][j].value == CursorMove->value && CursorMove->combined == FALSE)
                        {
                            board[k][j].value = 2 * CursorMove->value; //nhân đôi giá trị của mình
                            CursorMove->combined = TRUE;
                            *points += board[k][j].value;
                            board[i][j].new_coordinates = board[k][j].coordinates;
                            CursorMove->unchanged = TRUE;
                            CursorMove->value = NO_PICTURE;
                            CursorMove = &(board[k][j]);
                            CursorMove->combined = TRUE;
                            CursorMove->unchanged = FALSE;
                        }
                        else if (board[k][j].value == NO_PICTURE)
                        {
                            board[k][j].value = CursorMove->value;
                            board[i][j].new_coordinates = board[k][j].coordinates;
                            CursorMove->value = NO_PICTURE;
                            CursorMove->unchanged = TRUE;
                            CursorMove = &(board[k][j]);
                            CursorMove->unchanged = FALSE;
                        }
                        else break;
                        k = iteration(k, inverted);
                    }
                }
            }
        }
    }
}


void OrAnimation(board_cell_t **board, cell_t *numbers, board_cell_t *animation, int *hm_to_animation)
{
    int i, j, it, x, y;
    order_t new_comb;
    int it_animation = 0;
    for (i = 0; i <NUMBER_CHAMBERS; i++)
    {
        for (j = 0; j <NUMBER_CHAMBERS; j++)
        {
            // ô được làm động
            if (board[i][j].new_coordinates.first != 0 && board[i][j].new_coordinates.second != 0)
            {
                (*hm_to_animation)++; //tăng số lượng cho hoạt ảnh
                animation[it_animation].coordinates.first = board[i][j].new_coordinates.first + CHAMBER_SIZE / 2;
                animation[it_animation].coordinates.second = board[i][j].new_coordinates.second + CHAMBER_SIZE / 2;
                // chuyển đổi thành các chỉ mục trong mảng bảng
                new_comb = converting(board[i][j].new_coordinates);
                // xác định tọa độ của các hoạt ảnh cuối cùng
                x = board[new_comb.first][new_comb.second].coordinates.first + CHAMBER_SIZE / 2;
                y = board[new_comb.first][new_comb.second].coordinates.second + CHAMBER_SIZE / 2;
                animation[it_animation].new_coordinates.first = x;
                animation[it_animation].new_coordinates.second = y;
                board[i][j].new_coordinates = {}; // đặt lại tọa độ mới
                // tính chỉ số trong mảng số
                it = log2(double(board[new_comb.first][new_comb.second].value)) - 1;
                board[new_comb.first][new_comb.second].value = numbers[it].value;
                animation[it_animation].value = numbers[it].value;
                it_animation++;
            }
        }
    }
}
