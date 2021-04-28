#ifndef RESETG_H_INCLUDED
#define RESETG_H_INCLUDED

#include "CONST.h"
#include "Surface.h"

void animation_init(board_cell_t *animation);  ////khởi tạo mảng hoạt hình

//đặt thời điểm bắt đầu lặp lại trên bảng khi kiểm tra tùy thuộc vào hướng
order_t set_start (order_t start, direction_t direction);

order_t converting(order_t coordinates);
void Animations(board_cell_t *animation, direction_t discri, int *hm_to_animation , int *hm_posed,
                   main_t image, discri_t *reset, board_cell_t **board, cell_t *numbers);
//hoạt ảnh bao gồm hiển thị tất cả các hình ảnh cho đến khi tất cả các hình ảnh đến ô mục tiêu


#endif // RESETG_H_INCLUDED
