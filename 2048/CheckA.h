#ifndef CHECKA_H_INCLUDED
#define CHECKA_H_INCLUDED

#include "ResetG.h"

//kiểm tra nơi một ô nhất định có thể tiếp cận, nó kết nối các ô
void walk(board_cell_t **board, direction_t direction, int *points);

//kiểm tra xem hình ảnh động sẽ được thực hiện
void OrAnimation(board_cell_t **board, cell_t *numbers, board_cell_t *animation, int *hm_to_animation);


#endif // CHECKA_H_INCLUDED
