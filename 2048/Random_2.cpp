#include "Random_2.h"

void random_2 (cell_t *numbers, board_cell_t **board)
{
    int empty_box = 0, i, j, drawn_index = 0;
    for (i = 0; i <NUMBER_CHAMBERS; i++)
    {
        for (j = 0; j <NUMBER_CHAMBERS; j++)
        {
            // tìm kiếm các ô trống và đếm số lượng của chúng
            if (board[i][j].value == NO_PICTURE) empty_box ++;
            }
    }
    if (empty_box > 0)  //nếu có bất kỳ ô trống nào
    {
        int random = rand() % empty_box + 1;
        for (i = 0; i < NUMBER_CHAMBERS; i++)
        {
            for (j = 0; j < NUMBER_CHAMBERS; j++)
            {
                // tìm vị trí của ô đã vẽ
                if (board[i][j].value == NO_PICTURE) drawn_index ++;
                if (drawn_index == random) // nếu tìm thấy nó, nó sẽ viết hai ở đó
                {
                    board[i][j].value = numbers[0].value;
                    return;
                }
            }
        }
    }
}
