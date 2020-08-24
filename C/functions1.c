#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include "functions1.h"
/******************* Static Function Prototypes *******************/
static boardPosArray** createPosArr();// create pointer to arr of board positions function
									  // update single moves cell funcion
static void UpdateMoves(Move** move, unsigned int* size, char** board, unsigned int row, unsigned int col);
static Move* del_move(Move* move, unsigned int size, unsigned int new_size);// delete move function
static void fill_move_arr(movesArray*** move_arr);// fill example to move arr f
static void fill_board(char *** board);// fill example board f
static void UpdateMoveArr(char** board, movesArray*** moves_arr);// update move arr function
static Move* CreateMove(unsigned int size);// create moves f
static boardPos* build_positions(unsigned int size, Move* move, unsigned int row, unsigned int col);// build position function

																									/******************* Function Implementation *******************/
boardPosArray** validMoves(char** board, movesArray** moves_arr)// create valid moves board pos arr function
{
	// decleration of variables
	unsigned int row, col;
	boardPosArray** valid_moves_arr;
	valid_moves_arr = createPosArr();// create pos arr
	UpdateMoveArr(board, &moves_arr);// updating move arr to only valid moves
	for (row = 0; row < N; row++)// loop that fills each cell in arr pos
	{
		for (col = 0; col < M; col++)
		{
			valid_moves_arr[row][col].size = moves_arr[row][col].size;// calc size
																	  // building postions according to the size
			valid_moves_arr[row][col].positions = build_positions(valid_moves_arr[row][col].size, moves_arr[row][col].moves, row, col);
		}
	}
	return valid_moves_arr;//output
}
static void UpdateMoveArr(char** board, movesArray*** moves_arr)// update move arr function
{
	// decleration of variables
	unsigned int row, col;
	movesArray** temp;
	temp = *moves_arr;
	for (row = 0; row < N; row++)//loop that updates each cell in move arr
	{
		for (col = 0; col < M; col++)
		{
			UpdateMoves(&(temp[row][col].moves), &(temp[row][col].size), board, row, col);//updating cell
		}
	}
	*moves_arr = temp;
}
// update single moves cell funcion
static void UpdateMoves(Move** move, unsigned int* size, char** board, unsigned int row, unsigned int col)
{
	// decleration of variables
	Move* temp;
	unsigned int new_size, index, new_row, new_col;
	new_size = *size;
	temp = *move;
	for (index = 0; index < *size; index++)// loop that checks each move validity
	{
		new_row = row + temp[index].rows;// calc of row
		new_col = col + temp[index].cols;// calc of cell
		if (!(check_cell_on_board(board, new_row, new_col)))// check cell on board
		{
			//if not valid
			new_size--;// decreasing size
			temp[index].rows = 0;
			temp[index].cols = 0;
		}
	}
	temp = del_move(temp, *size, new_size);// updating the move cell
	*size = new_size;
	*move = temp;
}
void allocation_check(void *ptr)//allocation check function
{
	if (!ptr)
	{
		fprintf(stderr, "Allocation error\n");
		exit(-1);
	}
}
BOOL check_cell_on_board(char** board, unsigned int row, unsigned int col)// check cell on board function
{
	// decleration of variables
	BOOL res;
	res = FALSE;
	if ((row >= 0 && row < N) && (col >= 0 && col < M))// check if values arr in the board range
	{
		if (board[row][col] != CANT_MOVE)//check if the cell has '*';
			res = TRUE;
	}
	return res;//output
}
static Move* del_move(Move* move, unsigned int size, unsigned int new_size)// delete move function
{
	// decleration of variables
	unsigned int index_old, index_new = 0, move_col, move_row;
	Move* new_move = (Move*)malloc((new_size) * sizeof(Move));// memory alloc
	allocation_check(new_move);// alloc check
	for (index_old = 0; index_old < size; index_old++)// loop that updates moves
	{
		move_row = move[index_old].rows;
		move_col = move[index_old].cols;
		if (move_row != 0 || move_col != 0)// if move is empty = not valid
		{
			new_move[index_new] = move[index_old];// del
			index_new++;
		}
	}
	return new_move;//output
}
static boardPosArray** createPosArr()// create pointer to arr of board positions function
{
	// decleration of variables
	int index;
	boardPosArray** new_arr;
	new_arr = (boardPosArray**)malloc((N) * sizeof(boardPosArray*));//memory alloc rows
	allocation_check(new_arr);//alloc check
	for (index = 0; index < N; index++)// loop that alloc each row
	{
		new_arr[index] = (boardPosArray*)malloc((M) * sizeof(boardPosArray));// memory alloc col
		allocation_check(new_arr[index]);//alloc check 
	}
	return new_arr;//output
}
static boardPos* build_positions(unsigned int size, Move* move, unsigned int row, unsigned int col)// build position function

{
	// decleration of variables
	unsigned int index, calc_row, calc_col;
	boardPos* cel = (boardPos*)malloc((size) * sizeof(boardPos));//memory allc
	allocation_check(cel);// alloc cell
	for (index = 0; index < size; index++)// build each pos loop
	{
		calc_row = move[index].rows + row;// calc row
		calc_col = move[index].cols + col;// calc row
		cel[index][0] = 'A' + calc_row;
		printf("%c", cel[index][0]);
		cel[index][1] = '1' + calc_col;
		printf("%c ", cel[index][1]);
	}
	return cel;//output
}

movesArray** BuildMoveArrey()// build move arr
{
	// decleration of variables
	int index;
	movesArray** move_arr;
	move_arr = (movesArray**)malloc((N) * sizeof(movesArray*));// memory alloc
	allocation_check(move_arr);//alloc check
	for (index = 0; index < N; index++)// create cols for each row
	{
		move_arr[index] = (movesArray*)malloc((M) * sizeof(movesArray));
		allocation_check(move_arr[index]);
	}
	fill_move_arr(&move_arr);// fill board
	return move_arr;
}
static void fill_move_arr(movesArray*** move_arr)// fill moves arr exam f
{
	// decleration of variables
	unsigned int row, col, size = 5;
	movesArray** temp = *move_arr;
	for (row = 0; row < N; row++) {
		for (col = 0; col < M; col++) {
			temp[row][col].size = size;
			temp[row][col].moves = CreateMove(temp[row][col].size);
		}
	}
	*move_arr = temp;
}
static Move* CreateMove(unsigned int size) {// create moves for each cell in moves arr
											// decleration of variables
	Move* new_move;
	new_move = (Move*)malloc((size) * sizeof(Move));
	allocation_check(new_move);
	new_move[0].rows = -1, new_move[0].cols = 1;
	new_move[1].rows = 1, new_move[1].cols = -1;
	new_move[2].rows = 2, new_move[2].cols = 0;
	new_move[3].rows = 0, new_move[3].cols = 2;
	new_move[4].rows = 0, new_move[3].cols = 1;
	return new_move;//ouput
}
static void fill_board(char *** board)// fill board
{
	// decleration of variables
	unsigned int row, col;
	char** temp;
	temp = *board;
	for (row = 0; row < N; row++)
	{
		for (col = 0; col < M; col++)
		{
			temp[row][col] = CAN_MOVE;
		}
	}
	temp[0][0] = CANT_MOVE;
	temp[1][0] = CANT_MOVE;
	temp[2][2] = CANT_MOVE;
	*board = temp;
}
char** BuildBoard()// build board f
{
	// decleration of variables
	unsigned int index;
	char** board;
	board = (char**)malloc((N) * sizeof(char*));// memo alloc
	allocation_check(board);// alloc check
	for (index = 0; index < N; index++)
	{
		board[index] = (char*)malloc((M) * sizeof(char));
		allocation_check(board[index]);
	}
	fill_board(&board);
	return board;//output
}
void free_board(char ** arr)
{
	// decleration of variables
	unsigned int index;
	for (index = 0; index < N; index++)
	{
		free(arr[index]);
	}
	free(arr);
}
void free_pos_mat(boardPosArray** arr)
{
	// decleration of variables
	unsigned int index;
	for (index = 0; index < N; index++)
	{
		free(arr[index]);
	}
	free(arr);
}
void free_moves_mat(movesArray** arr)
{
	// decleration of variables
	unsigned int index;
	for (index = 0; index < N; index++)
	{
		free(arr[index]->moves);
		free(arr[index]);
	}
	free(arr);
}