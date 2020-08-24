#define _CRT_SECURE_NO_WARNINGS
/***** INCLUDES *****/
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include "functions4.h"
/******************* Static Function Prototypes *******************/
static movesList *findPathCoveringAllBoardAux(treeNode* root, movesList* moves, unsigned int *num, boardPos* startingPosition);
static void freemoveslist(movesList *moves);// free move list function
 /******************* Function Implementation *******************/
movesList findPathCoveringAllBoard(char** board, boardPos* startingPosition, movesList** moves_list_mat)// find all path covering board f
{
	//decleration of variables
	boardPos* start = startingPosition;
	unsigned int movesNum = 0;
	treeNode* root;
	movesList *moves;
	moves = (movesList*)malloc(sizeof(movesList));// memory alloc
	allocation_check(moves);// alloc check
	moves->head = NULL;
	moves->tail = NULL;
	root = findAllPossiblePaths(board, startingPosition, moves_list_mat);// create tree
	printTree(root);// print tree
	moves = findPathCoveringAllBoardAux(root, moves, &movesNum, start); // creating moves
	printf("\n");
	if (movesNum == N * M)
	{
		printf("there is a move set that cover all the board \n");
		return *moves;
	}
	else
	{
		printf("no way to fill the board \n");
		freemoveslist(moves);
		return *moves;
	}
	FreeTree(root);
}
// recursive aux f 
static movesList *findPathCoveringAllBoardAux(treeNode* root, movesList* moves, unsigned int *num, boardPos* startingPosition)
{
	char rows, cols;
	unsigned int index, size = N * M;
	if (!root)// stop point
	{
		return moves;
	}
	(*num)++;
	cols = root->position[0] - startingPosition[0][0];
	rows = root->position[1] - startingPosition[0][1];
	addmove(moves, cols, rows);
	if ((*num) == size)
	{
		return moves;
	}
	else
	{
		for (index = 0; index < (root->num_of_children); index++)
		{
			if ((*num) == size)
			{
				return moves;
			}
			moves = findPathCoveringAllBoardAux(root->next_possible_positions[index], moves, num, &(root->position));
		}
	}
	if ((*num) != size)
		(*num)--;
	return moves;
}
void addmove(movesList *moves, char cols, char rows)// add move 
{
	if (rows == 0 && cols == 0)
	{
		return;
	}
	moveCell *temp;
	temp = (moveCell*)malloc(sizeof(moveCell));
	allocation_check(temp);
	temp->move.cols = cols;
	temp->move.rows = rows;
	if (!(moves->head))
	{

		moves->head = temp;
		temp->next = NULL;
		temp->prev = NULL;

	}
	else if (!(moves->tail))
	{
		moves->head->next = temp;
		temp->prev = moves->head;
		temp->next = NULL;
		moves->tail = temp;
	}
	else
	{
		moves->tail->next = temp;
		temp->prev = moves->tail;
		temp->next = NULL;
		moves->tail = temp;
	}
}
static void freemoveslist(movesList *moves)// free move list function
{
	//decleration of variables
	moveCell *temp, *temp2;
	temp = moves->head;
	temp2 = temp->next;
	moves->head = NULL;
	moves->tail = NULL;
	while (temp)
	{
		free(temp);
		temp = temp2;
		if (temp && temp->next)
			temp2 = temp->next;
		else
			temp2 = NULL;
	}
}