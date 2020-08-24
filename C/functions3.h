#ifndef ___FUNCTIONS3____
#define ___FUNCTIONS3____
/***** INCLUDES *****/
#include "functions1.h"
#include "functions2.h"

/***** TYPEDEFS *****/
/***** tree node data structure *****/
typedef struct _treeNode {
	boardPos position;
	unsigned char num_of_children;
	struct _treeNode ** next_possible_positions;
}treeNode;

/******************* Function Prototypes *******************/
treeNode* findAllPossiblePaths(char** board, boardPos* startingPosition, movesList** moves_list_mat);// build tree function
BOOL check_cell_on_board_q3(char** board, int row, int col);// check cell on board function
char** BuildBoard_q3();// build example board f
movesList** build_moves_list_mat();// build move list mat f
void fill_move_list_mat(movesList*** moves_list_mat);// fill move list mat
void fill_board_q3(char *** board);// fil board f 
void makeEmptyList(movesList* list);// making empty list function
void insertDataToEndList(movesList* list, char  row, char col);// insertation of new cell to list function
void printTree(treeNode* root);//print tree ff
void calc_row_col(int row, int col, char add_to_rows, char add_to_cols, int* new_row, int* new_col);// calc new row and coll function
void free_board(char ** arr); // free board f
void free_move_lst_mat(movesList** arr);// free move list mat f
void FreeTree(treeNode* root); // free tree f
treeNode *  create_tree_node(boardPos position);// build tree node function
void update_root_children(treeNode *root, unsigned int *index);// update children size function
boardPos* build_positions(int row, int col);// build position function
movesList create_moves_list_mat();// create move list mat example for each cell f
moveCell* create_new_move_cell(moveCell* prev, char row, char col);// creat move list cell f
void findAllPossiblePathsAux(treeNode *root, char** board, boardPos* startingPosition, movesList** moves_list_mat, int row, int col);// build tree help function 
void resizing_children_arr(treeNode * root, unsigned char *curr_capacity);// reasizing arr of children function
#endif
