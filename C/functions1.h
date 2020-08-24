#ifndef ___FUNCTIONS1____
#define ___FUNCTIONS1____
/***** DEFINES *****/
#define N 3 // number of board's rows
#define M 4 // number of board's cols
#define CAN_MOVE ' '
#define CANT_MOVE '*'


/***** TYPEDEFS *****/
typedef int BOOL;// bool type defintion
#define FALSE 0
#define TRUE 1

typedef char boardPos[2];//    representations  a board's square position on the board
typedef struct _move { //   struct that represents  one move  on the board
	char rows, cols;
} Move;

typedef struct _movesArray {//   struct that represents moves  on the board
	unsigned int size;
	Move *moves;
}movesArray;
typedef struct _boardPosArray//   struct that represents board's
							 //square position on the board
{
	unsigned int size;
	boardPos *positions;
}boardPosArray;

/******************* Function Prototypes *******************/
boardPosArray** validMoves(char** board, movesArray** moves_arr);// create valid moves board pos arr function
void allocation_check(void *ptr);//allocation check function
BOOL check_cell_on_board(char** board, unsigned int row, unsigned int col);// check cell on board function
char** BuildBoard();// build board f
movesArray** BuildMoveArrey();// build mov arr f
							  // free arr functions
void free_board(char** arr);
void free_moves_mat(movesArray** arr);
void free_pos_mat(boardPosArray** arr);
#endif
