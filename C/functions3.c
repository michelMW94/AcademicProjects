#define _CRT_SECURE_NO_WARNINGS
/***** INCLUDES *****/
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include "functions3.h"
/******************* Static Function Prototypes *******************/
static void freeList(movesList* lst);// free list function
									 /******************* Function Implementation *******************/
treeNode* findAllPossiblePaths(char** board, boardPos* startingPosition, movesList** moves_list_mat)// build tree function
{
	//decleration of variables
	int row, col;
	treeNode *root;
	root = create_tree_node(*startingPosition);// create root of tree
	row = startingPosition[0][0] - 'A';// calc row & col
	col = startingPosition[0][1] - '1';
	findAllPossiblePathsAux(root, board, startingPosition, moves_list_mat, row, col);// build tree with help recursive f
	return root;//output
}
void findAllPossiblePathsAux(treeNode *root, char** board, boardPos* startingPosition, movesList** moves_list_mat, int row, int col) {// build tree help function 


																																	  // decleration of variables
	unsigned char pisical_size = 0;
	unsigned int index;
	int new_row, new_col;
	moveCell * curr;
	boardPos* next_pos;
	if (!check_cell_on_board_q3(board, row, col) || (board[row][col])) {// stoping point
		free(root);// free root
		root = NULL;
		return;
	}
	else {// else for valid or non empty root
		curr = moves_list_mat[row][col].head;
		while (curr) {// loop moves list to build few options of root's sons
			board[row][col] = 1;// setting root to non empty on board
			calc_row_col(row, col, curr->move.rows, curr->move.cols, &new_row, &new_col);// calc new row/col
			if (check_cell_on_board_q3(board, new_row, new_col) && !(board[new_row][new_col])) {// if row col is valid 
				if (pisical_size == root->num_of_children)// checking size and reasings if is needed
					resizing_children_arr(root, &pisical_size);
				update_root_children(root, &index);// updating children size
				next_pos = build_positions(new_row, new_col);// building new pos
				root->next_possible_positions[index] = create_tree_node(next_pos[0]);// creting new tree node
				findAllPossiblePathsAux(root->next_possible_positions[index], board, next_pos, moves_list_mat, new_row, new_col);// recursive call
				board[new_row][new_col] = 0;//setting root to 0 at the end of each recursive
			}
			curr = curr->next;
		}

	}
}
void update_root_children(treeNode *root, unsigned int *index)// update children size function
{
	root->num_of_children++;
	*index = root->num_of_children - 1;
}

treeNode *  create_tree_node(boardPos position)// build tree node function
{
	// decleration of variables
	treeNode *new_node;
	new_node = (treeNode*)malloc(sizeof(treeNode));// memory alloc
	allocation_check(new_node);//alloc check
	new_node->position[0] = position[0];
	new_node->position[1] = position[1];
	new_node->num_of_children = 0;
	new_node->next_possible_positions = NULL;
	return new_node;//output
}
BOOL check_cell_on_board_q3(char** board, int row, int col)// check cell on board function
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
void calc_row_col(int row, int col, char add_to_rows, char add_to_cols, int* new_row, int* new_col)// calc new row and coll function
{
	*new_row = row + add_to_rows;//calc row
	*new_col = col + add_to_cols;//calc col
}
void resizing_children_arr(treeNode * root, unsigned char *curr_capacity)// reasizing arr of children function
{
	// decleration of variables
	unsigned int size, index;
	index = *curr_capacity;
	size = (*curr_capacity) * 2 + 1;// new size
	*curr_capacity = size;
	root->next_possible_positions = (treeNode**)realloc((root->next_possible_positions), (size) * sizeof(treeNode*));//memory realloc
	allocation_check(root->next_possible_positions);//alloc check
	for (index; index < size; index++)// loop that creates new cells
	{
		root->next_possible_positions[index] = (treeNode*)malloc(sizeof(treeNode));
		allocation_check(root->next_possible_positions[index]);
	}

}
boardPos* build_positions(int row, int col)// build position function
{
	// decleration of variables
	boardPos* cel;
	cel = (boardPos*)malloc(sizeof(boardPos));//memory alloc
	allocation_check(cel); //alloc check
	cel[0][0] = 'A' + row;// calc row
	cel[0][1] = '1' + col;//calc col
	return cel;//output
}

void fill_board_q3(char *** board)// fil board f 
{
	// decleration of variables
	unsigned int row, col;
	char** temp;
	temp = *board;
	for (row = 0; row < N; row++)
	{
		for (col = 0; col < M; col++)
		{
			temp[row][col] = 0;
		}
	}
	/*temp[0][0] = CANT_MOVE; //optional obstacles
	temp[1][0] = CANT_MOVE;*/

	*board = temp;
}
char** BuildBoard_q3()//build board function
{
	// decleration of variables
	unsigned int index;
	char** board;
	board = (char**)malloc((N) * sizeof(char*));//memory alloc
	allocation_check(board);// check alloc
	for (index = 0; index < N; index++)// malloc each cell
	{
		board[index] = (char*)malloc((M) * sizeof(char));
		allocation_check(board[index]);
	}
	fill_board_q3(&board);// fil board with example
	return board;//output
}
movesList** build_moves_list_mat()// build moves list mat function
{
	// decleration of variables
	unsigned int index;
	movesList** moves_list_mat;
	moves_list_mat = (movesList**)malloc((N) * sizeof(movesList*));// memory alloc
	allocation_check(moves_list_mat);// alloc check
	for (index = 0; index < N; index++)// create cols for each row cell
	{
		moves_list_mat[index] = (movesList*)malloc((M) * sizeof(movesList));
		allocation_check(moves_list_mat[index]);
	}
	fill_move_list_mat(&moves_list_mat);// fill mat with example
	return moves_list_mat;//output
}
void fill_move_list_mat(movesList*** moves_list_mat)
{
	// decleration of variables
	unsigned int row, col;
	movesList** temp;
	temp = *moves_list_mat;
	for (row = 0; row < N; row++)
	{
		for (col = 0; col < M; col++)
		{
			temp[row][col] = create_moves_list_mat();
		}
	}
	*moves_list_mat = temp;
}
movesList create_moves_list_mat()// create move list mat example for each cell f
{
	//decleration of variables
	movesList lst;
	makeEmptyList(&lst);// make empty list
	insertDataToEndList(&lst, 1, 0);
	insertDataToEndList(&lst, -1, 0);
	insertDataToEndList(&lst, 0, 1);
	insertDataToEndList(&lst, 0, -1);
	return lst;//output
}
moveCell* create_new_move_cell(moveCell* prev, char row, char col)// create new cell function
{
	//decleration of variables
	moveCell* move_cell;
	move_cell = (moveCell*)malloc(sizeof(moveCell));
	allocation_check(move_cell);
	move_cell->move.rows = row;
	move_cell->move.cols = col;
	move_cell->next = NULL;
	move_cell->prev = prev;
	return move_cell;//output
}
void insertDataToEndList(movesList* list, char  row, char col)// insertation of new x to list function
{
	//decleration of variables
	moveCell* cell_to_add;
	cell_to_add = create_new_move_cell(list->tail, row, col);// making new cell
	if (!(list->head) && !(list->tail))// if for empty list
	{
		list->tail = list->head = cell_to_add;
	}
	else// else for non empty list
	{
		list->tail->next = cell_to_add;
		list->tail = cell_to_add;
	}
}
void makeEmptyList(movesList* list)// making empty list function
{
	list->head = list->tail = NULL;
}
void printTree(treeNode* root) {// print tree  recursive function
	unsigned int index, size = root->num_of_children;
	if (!root) {//stoping point
		return;
	}
	else
	{
		for (index = 0; index < size; index++)
		{
			printTree(root->next_possible_positions[index]);//recursive call
		}
		printf("%c", root->position[0]);
		printf("%c ", root->position[1]);
	}
}
void free_move_lst_mat(movesList** arr)// free move list mat f
{
	// decleration of variables
	unsigned int index;
	for (index = 0; index < N; index++)
	{
		freeList(arr[index]);
	}
	free(arr);
}
static void freeList(movesList* lst)// free list function
{
	//decleration of variables
	moveCell *current, *temp;
	current = lst->head;
	while (current)// free each list  cell loop
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}
void FreeTree(treeNode* root) {// free tree in order help recursive function
	unsigned int index, size = root->num_of_children;
	if (!root) {//stoping point
		return;
	}
	else
	{
		for (index = 0; index < size; index++)
		{
			printTree(root->next_possible_positions[index]);//recursive call
		}
		free(root);
	}
}