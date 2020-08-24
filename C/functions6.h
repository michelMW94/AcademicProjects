#ifndef ___FUNCTIONS6___
#define ___FUNCTIONS6___
/***** INCLUDES *****/
#include "functions2.h"
#include "functions5.h"
#include "functions4.h"
/***** DEFINES *****/
#define NUM_OF_MOVES 5
/******************* Function Prototypes *******************/
int checkAndDisplayPathFromFile(char* file_name, char** board, movesArray **moves_arr);			// program main function,checks if a list of positons 
																								// from a file is ligal and if it fills the board.
movesArray** BuildMoveArrey_q6();									//  allocated and build move arrey;
char** build_a_board();											//  allocated and build a board;
boardPos *build_pos_arr_from_bin_file(char *file_name, int* posnumtoreturn); // funtion that extracts from file the board positions into a list and list length.
#endif
