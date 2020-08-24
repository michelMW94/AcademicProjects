#ifndef ___FUNCTIONS4____
#define ___FUNCTIONS4____
/***** INCLUDES *****/
#include "functions1.h"
#include "functions2.h"
#include "functions3.h"

/******************* Function Prototypes *******************/
void addmove(movesList *moves, char cols, char rows);// add move f
movesList findPathCoveringAllBoard(char** board, boardPos* startingPosition, movesList** moves_list_mat);// finf all path f
#endif

