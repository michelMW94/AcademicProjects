#define _CRT_SECURE_NO_WARNINGS
/***** INCLUDES *****/
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include "functions1.h"
#include "functions2.h"
#include "functions3.h"
#include "functions4.h"
#include "functions5.h"
#include "functions6.h"
int main()
{
	// decleration of variables
	char** board_q1, **board_q2, **board_q3, ** board_q4, fname[] = "filename.bin", **board_q6;
	movesArray** move_arr_1, **moves_arr_6;
	boardPosArray** valid_moves_arr;
	boardPos startingPosition_2, startingPosition_3, startingPosition_4, *pos_arr;
	int num, num_q6;
	movesList *moves_list, ** moves_list_mat_q3, ** moves_list_mat_q4, moves_q4;
	treeNode* root;
	//////////////////////////////////////////////////////Q1
	printf("Question number 1:\n\n");
	board_q1 = BuildBoard();// build board
	move_arr_1 = BuildMoveArrey();// build move arr
	valid_moves_arr = validMoves(board_q1, move_arr_1);// build valid moves pos arr
    //free memory alloc
	free_board(board_q1);
	free_pos_mat(valid_moves_arr);
	free_moves_mat(move_arr_1);
	printf("\n\n");
	//////////////////////////////////////////////////////Q2
	printf("Question number 2:\n\n");
	board_q2 = initiateboard();		//builds a board
	moves_list = initiate_list();	// 	build Moves list

	startingPosition_2[0] = 'B';					// starting position
	startingPosition_2[1] = '3';
	num = display(board_q2, startingPosition_2, moves_list);
	printf("number of deleted moves is: %d \n", num);
	//free memory alloc
	free_move_lst(moves_list);
	free_board(board_q2);
	printf("\n");
	//////////////////////////////////////////////////////Q3
	printf("Question number 3:\n\n");
	board_q3 = BuildBoard_q3(); //build board
	startingPosition_3[0] = 'A';// starting pos example
	startingPosition_3[1] = '2';
	moves_list_mat_q3 = build_moves_list_mat();//create move list mat
	root = findAllPossiblePaths(board_q3, &startingPosition_3, moves_list_mat_q3);// create tree
	printTree(root);			//print tree							
	//free memory alloc
	free_board(board_q3);
	free_move_lst_mat(moves_list_mat_q3);
	FreeTree(root);
	printf("\n\n");
	//////////////////////////////////////////////////////Q4
	printf("Question number 4:\n\n");
	board_q4 = BuildBoard_q3();     // build a board.
	startingPosition_4[0] = 'A';    // starting position.
	startingPosition_4[1] = '3';
	moves_list_mat_q4 = build_moves_list_mat();  // builds move list mat
	moves_q4 = findPathCoveringAllBoard(board_q4, &startingPosition_4, moves_list_mat_q4);   //main program.
	free_board(board_q4);// free board and moves_list mat
	 //free memory alloc
	free_move_lst_mat(moves_list_mat_q4);
	printf("\n");
	//////////////////////////////////////////////////////Q5
	pos_arr = build_pos_arr();// build  pos arr
	saveListTOBinFile(fname, pos_arr);// save pos list to bin file
	free(pos_arr);// free pos arr
	//////////////////////////////////////////////////////Q6
	printf("Question number 6:\n\n");
	board_q6 = build_a_board();				// builds a board
	moves_arr_6 = BuildMoveArrey_q6();		// builds an array
	num_q6 = checkAndDisplayPathFromFile(fname, board_q6, moves_arr_6); //main program functuion.
	printf("answer is: %d \n", num_q6);
	//free memory alloc
	free_board(board_q6);
	free_moves_mat(moves_arr_6);
	return 0;
}