#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "DisSquare.h"
#include "Surface.h"

//chức năng chèn biểu đồ và vẽ liên tục các hình ảnh
void insert_plansze(main_t image, board_cell_t **board, cell_t *numbers, discri_t *victory);
void plansza_init(board_cell_t **board);   // hàm đặt lại nội dung của bảng bảng và tính toán tọa độ của các ô riêng lẻ


//chức năng sao chép nội dung của bảng sang bảng thứ hai, bảng phụ - được sử dụng khi hoàn tác chuyển động
void copy_board(board_cell_t **board, board_cell_t **board_cop);

#endif // TABLE_H_INCLUDED
