#ifndef CORNER_FIT_2_H
#define CORNER_FIT_2_H
#include "../include/board.h"
#include "../include/tetromino.h"

/*
@requires bag is a valid pointer to a bag of tetrominos
@assigns the board b
@ensures places on the board the single tetromino in the bag that minimises its distance with the corner of the board b
*/
int corner_fit_2(board* b, int num_pieces);

#endif 
