/***** INCLUDES *****/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "functions2.h"

/******************* Function Implementation *******************/

void allocateMove(Move *move, char row, char col)  // utility function.
{
	move->cols = col;
	move->rows = row;
}

moveCell* allocatemovecell(Move move)
{
	moveCell *datacell;
	datacell = (moveCell*)malloc((sizeof(moveCell)));
	allocation_check(datacell);
	datacell->move = move;
	datacell->next = datacell->prev = NULL;
	return datacell;
}

movesList *allocatemovesList()
{
	movesList *list;
	list = (movesList*)malloc((sizeof(movesList)));
	allocation_check(list);
	list->head = list->tail = NULL;
	return list;
}

int *translateBoardPos(boardPos a)     //translate the board cell name to board location
{
	int *respond;
	respond = (int*)malloc(sizeof(int) * 2);
	allocation_check(respond);
	respond[0] = a[0] - 'A';
	respond[1] = a[1] - '1';
	return respond;
}
moveCell *RemoveMoveCell(moveCell *prev, movesList *moves_list) // removes a moveCell (devided by location on the list)
{
	moveCell *delCell;
	if (prev == NULL)			//identify head location
	{
		delCell = moves_list->head;
		moves_list->head = moves_list->head->next;
		if (moves_list->head)			//
		{
			moves_list->head->prev = NULL;
		}
		free(delCell);
		return moves_list->head;
	}
	else if (prev->next == moves_list->tail)  // identify tail location
	{
		delCell = prev->next;
		prev->next = NULL;
		moves_list->tail = prev;
		free(delCell);
		return NULL;
	}
	else                      // mid locations
	{
		delCell = prev->next;
		prev->next = delCell->next;
		prev->next->prev = prev;
		free(delCell);
		return prev->next;
	}
}
void printboard(char **board) // print board
{
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
int display(char **board, boardPos start, movesList *moves_list)
{
	int i = 0, temp1, temp0, movesRemoved = 0;
	char **board2 = board;
	moveCell *curr = moves_list->head;
	int *position = translateBoardPos(start);
	board2[position[0]][position[1]] = '#';
	while (curr)
	{
		temp0 = position[0] + (curr->move.rows);     //next position on board stored temporarly
		temp1 = position[1] + (curr->move.cols);
		if (temp0 >= 0 && temp1 >= 0 && temp0< N && temp1< M && board2[temp0][temp1] == ' ') // check moved position legality
		{
			position[0] = temp0;
			position[1] = temp1;
			board2[position[0]][position[1]] = i + '1';
			i++;
			curr = curr->next;
		}
		else
		{
			curr = RemoveMoveCell(curr->prev, moves_list);      //if next position is illigal
			movesRemoved++;
		}
	}
	printboard(board2);
	return movesRemoved;
}
char** initiateboard() // build a board
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

	for (int i = 0; i < N; i++)     //fills the board 
	{
		for (int j = 0; j<M; j++)
		{
			board[i][j] = ' ';
			/*	if (i == 1 || j == 1)      //optional for adding obstacles
			board[i][j] = '*'; */
		}
	}
	return board;
}
movesList *initiate_list() // initiate a list.
{
	movesList *moves_list;
	Move move1, move2, move3;
	moveCell *cell1, *cell2, *cell3;

	allocateMove(&move1, -1, -1);  //defines the moves in the list
	allocateMove(&move2, 2, 2);
	allocateMove(&move3, -2, 3);


	cell1 = allocatemovecell(move1);
	cell2 = allocatemovecell(move2);
	cell3 = allocatemovecell(move3);
	cell1->next = cell2;
	cell2->next = cell3;
	cell2->prev = cell1;
	cell3->prev = cell2;
	moves_list = allocatemovesList();
	moves_list->head = cell1;
	moves_list->tail = cell3;
	return moves_list;
}
void free_move_lst(movesList* moves_list)// free move list function
{
	//decleration of variables
	moveCell *curr, *temp;
	curr = moves_list->head;
	while (curr)// loop that free lisr
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(curr);
	free(moves_list);
}