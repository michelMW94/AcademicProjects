#ifndef ___FUNCTIONS2____
#define ___FUNCTIONS2____
/***** INCLUDES *****/
#include "functions1.h"

/***** TYPEDEFS *****/
typedef struct _moveCell {				//struct that represent dual linked Move cell
	Move move;
	struct _moveCell *next, *prev;
}moveCell;
typedef struct _movesList {				// struct that represents dual linked list (w/head and tail)
	moveCell *head;
	moveCell *tail;
}movesList;
/******************* Function Prototypes *******************/
int display(char **board, boardPos start, movesList *moves_list); // program main function, displays board with Moves list applied.
																  //returns deleted moves amount.
moveCell *allocatemovecell(Move move);							// allocate a Move cell.			
void allocateMove(Move *move, char row, char col);				// utility tool. inserts row and col to specific Move.
movesList *allocatemovesList();									// allocate a Moves list.
char** initiateboard();						// allocate and initiate a board
movesList *initiate_list();                // allocate and initiate a Moves list
void free_move_lst(movesList* moves_list);//free move list f
moveCell *RemoveMoveCell(moveCell *prev, movesList *moves_list); // removes Move cell from Moves list;
int* translateBoardPos(boardPos a);							//translate the board cell name to board location
void printboard(char **board);									// funtion that prints the board			
int display(char **board, boardPos start, movesList *moves_list); // program main function, displays board with Moves list applied.
																  //returns deleted Moves amount.
#endif
