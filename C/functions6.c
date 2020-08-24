#define _CRT_SECURE_NO_WARNINGS
/***** INCLUDES *****/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions6.h"
#include <math.h> 

/******************* Static Function Prototypes *******************/
static void allocation_check6(void *ptr);   // specific to this question allocation check. (returns -2)
static int bin2int(char *buffer, int buf_size);												//translate a binary code from file to a int or char depends on file coding.
static void fill_move_arr(movesArray*** move_arr);								//fills moves arrey
static Move* CreateMove(unsigned int size);								// fills A move "list" (not moveList),
static void file_check6(void *ptr);										// check if the file exist returns -1 if not.

																		
	/******************* Function Implementation *******************/

movesArray** BuildMoveArrey_q6() // allocate and send to build a moves array 
{
	//decleration of variables
	int index;
	movesArray** move_arr;
	move_arr = (movesArray**)malloc((N) * sizeof(movesArray*));//memoery alloc
	allocation_check6(move_arr);//alloc check
	for (index = 0; index < N; index++)
	{
		move_arr[index] = (movesArray*)malloc((M) * sizeof(movesArray));
		allocation_check6(move_arr[index]);
	}
	fill_move_arr(&move_arr);
	return move_arr;//output
}
static void fill_move_arr(movesArray*** move_arr) // fills the move array.
{
	//decleration of variables
	unsigned int row, col, size = NUM_OF_MOVES;
	movesArray** temp = *move_arr;
	for (row = 0; row < N; row++) {
		for (col = 0; col < M; col++) {
			temp[row][col].size = size;
			temp[row][col].moves = CreateMove(temp[row][col].size);
		}
	}
	*move_arr = temp;
}
static Move* CreateMove(unsigned int size) // fills A move "list" (not moveList),
{
	//decleration of variables
	Move* new_move;
	new_move = (Move*)malloc((size) * sizeof(Move));
	allocation_check6(new_move);
	new_move[0].rows = 1, new_move[0].cols = 0;
	new_move[1].rows = 1, new_move[1].cols = -1;
	new_move[2].rows = 1, new_move[2].cols = -4;
	new_move[3].rows = 0, new_move[3].cols = 2;
	new_move[4].rows = 0, new_move[4].cols = 1;
	return new_move;
}

static void file_check6(void *ptr)//allocation check functin
{
	if (!ptr)
	{
		fprintf(stderr, "Error opening file");
		exit(-1);
	}
}


static void allocation_check6(void *ptr)  //allocation check functin specific to this question because it returns -2.
{
	if (!ptr)
	{
		fprintf(stderr, "Allocation error\n");
		exit(-2);
	}
}

static void printboard(char **board) // print board.
{
	//decleration of variables
	char temp = 'A';
	printf(" ");
	for (int t = 1; t <= M; t++)
		printf("  %d", t);
	printf("\n");
	for (int i = 0; i < N; i++)
	{
		temp = ('A' + i);
		printf("%c ", temp);
		for (int j = 0; j < M; j++)
		{
			printf("|%c|", board[i][j]);
		}
		printf("\n");
	}
}
int checkAndDisplayPathFromFile(char* file_name, char** board, movesArray **moves_arr) // program main function.
{
	//decleration of variables
	int legal = 0, legalcheck = 1, row, col, displayoutput, poselistsize;
	char rowtemp, coltemp;
	unsigned int i;
	movesList *list;
	boardPos *poslist;
	poslist = build_pos_arr_from_bin_file(file_name, &poselistsize);     // a funtion that analyze a binary file. 
																		 // puts locations in a list. and list size in an int.
	list = allocatemovesList();
	row = poslist[0][0] - 'A';					//col and row point to the current board position the func "look at"
	col = poslist[0][1] - '1';
	for (int j = 0; j < poselistsize-1; j++)// j is position index
	{
		if (row < N && col < M)				// check if the new position is inside the board
		{
			for (i = 0; i < moves_arr[row][col].size; i++)		// check if there is a move that gets us to the new position.
			{
				rowtemp = poslist[j + 1][0] - poslist[j][0];
				coltemp = poslist[j + 1][1] - poslist[j][1];
				if (moves_arr[row][col].moves[i].cols == coltemp && moves_arr[row][col].moves[i].rows == rowtemp)
				{

					addmove(list, moves_arr[row][col].moves[i].cols, moves_arr[row][col].moves[i].rows);
					legal = 1;     // check if the specific move is legal 
					break;
				}
			}
		}
		if (legal == 0)
		{
			addmove(list, coltemp, rowtemp); // adds a illigal move if its inside the board.
			legalcheck = 0; // check if the entire move list is ligal.
		}
		legal = 0;
		row = poslist[j + 1][0] - 'A'; // new position loop apply.
		col = poslist[j + 1][1] - '1';
	}
	displayoutput = display(board, poslist[0], list);

	//answer conditions.
	if (displayoutput == 0 && legalcheck && poselistsize == M * N) // check if no deleted moves and board is full.
	{
		return 1;
	}
	else if (((poselistsize - displayoutput) != M * N) && legalcheck != 0)  //check if board is not full and list legal.
	{
		return 2;
	}
	else if (((poselistsize - displayoutput) == M * N) && legalcheck == 0)  //check if board is full but the list is illegal.
	{
		return 3;
	}
	else                              // board not full and list illegal.
	{
		return 4;
	}
}

boardPos *build_pos_arr_from_bin_file(char *file_name, int* posnumtoreturn) // funtion that extracts from file the board positions into a list and list length.
{
	//decleration of variables
	char* buffer;
	FILE *in_fptr;
	boardPos *pos_arr;
	int size_buffer, index2, row_num, col_num, num_bit_pos;
	short int num_pos;
	unsigned char row, col, single_byte, zero = 0, one = 1;
	double log_2_N, log_2_M, n, m, num_of_bytes;
	int shift_right;
	in_fptr = fopen(file_name, "rb");//file open
	file_check6(in_fptr);
	fread(&num_pos, sizeof(short int), 1, in_fptr);// get num of pos
	*posnumtoreturn = num_pos;
	pos_arr = (boardPos *)malloc((num_pos) * sizeof(boardPos));//memory alloacation
	allocation_check6(pos_arr);
	fread(&row, sizeof(unsigned char), 1, in_fptr);// get num of rows and cols
	fread(&col, sizeof(unsigned char), 1, in_fptr);
	n = row;
	m = col;
	log_2_N = Log2(n);
	log_2_M = Log2(m);
	num_bit_pos = (int)(log_2_N + log_2_M);// calc num of bits
	size_buffer = num_pos * (int)(log_2_N + log_2_M);// size of buffer
	num_of_bytes = ceil((size_buffer / 8));
	if (size_buffer % 8)// grt num of bytes in the file
	{
		num_of_bytes++;
	}
	buffer = (char*)malloc((size_buffer + 1) * sizeof(char));// create buffer
	allocation_check6(buffer);
	buffer[size_buffer] = '\0';
	index2 = 0;
	for (int i = 0; i < num_of_bytes; i++)
	{
		fread(&single_byte, sizeof(unsigned char), 1, in_fptr);
		shift_right = 7;
		for (int j = 0; j < 8 && buffer[index2]; j++)
		{
			if (((single_byte << j) >> shift_right)  & one)// create buffer from each byte
			{
				buffer[index2] = '1';
			}
			else
			{
				buffer[index2] = '0';

			}
			index2++;
		}
	}
	index2 = 0;
	for (int index = 0; index < size_buffer; index += num_bit_pos)//fill buffer
	{
		row_num = bin2int(buffer + index, (int)log_2_N);
		col_num = bin2int(buffer + index + (int)log_2_N, (int)log_2_M);
		pos_arr[index2][0] = row_num + 'A';
		printf("%c", pos_arr[index2][0]);
		pos_arr[index2][1] = col_num + '1';
		printf("%c\n", pos_arr[index2][1]);
		index2++;
	}
	fclose(in_fptr);
	return pos_arr;
}
static int bin2int(char *buffer, int buf_size) {// bin num to decimal num
	int index, res;
	double temp = 0, exp = 0;
	for (index = buf_size - 1; index >= 0; index--)
	{
		if (buffer[index] == '1')
		{
			temp = temp + pow(2, exp);
		}
		exp++;
	}
	res = (int)temp;
	return res;
}

char** build_a_board()
{
	char** board;
	board = (char**)malloc(sizeof(char*)*N);
	if (!board)
	{
		printf("error alloc");
		exit(-1);
	}
	for (int t = 0; t < N; t++)
	{
		board[t] = (char*)malloc(sizeof(char)*M);
		if (!board[t])
		{
			printf("error alloc");
			exit(-1);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			board[i][j] = ' ';
		}
	}
	return board;
}
