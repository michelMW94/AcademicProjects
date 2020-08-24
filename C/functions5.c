#define _CRT_SECURE_NO_WARNINGS
/***** INCLUDES *****/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions5.h"
#include <math.h> 

/******************* Static Function Prototypes *******************/
static short int calc_num_pos(boardPos* pos_arr);// calc num pos f
static char* build_buffer(int size_buffer, int log2n, int log2m, boardPos* pos_arr);//build buffer f
static char *int2bin(int a, char *buffer, int buf_size);// calc in to bin f
static void file_check5(void *ptr);//file check function
								   /******************* Function Implementation *******************/

int Log2(double n)
{
	//decleration of variables
	double calc_res = log(n) / log(2);// log(n)/log(2) is log2. 
	calc_res = ceil(calc_res);// ceil of number
	return (int)calc_res;//output
}
static char *int2bin(int a, char *buffer, int buf_size) {
	//decleration of variables
	int index;
	for (index = buf_size - 1; index >= 0; index--)
	{
		if (a % BINARY_DIV == 0)
		{
			buffer[index] = '0';
		}
		else
		{
			buffer[index] = '1';
		}
		a = a / BINARY_DIV;
	}

	return buffer;//output
}
boardPos *build_pos_arr()// build pos arr example
{
	//decleration of variables
	boardPos * pos_arr;
	pos_arr = (boardPos *)malloc((SIZE_POS_ARR) * sizeof(boardPos));//memory alloacation
	allocation_check(pos_arr);//alloc check
	pos_arr[0][0] = 'C';
	pos_arr[0][1] = '2';
	pos_arr[1][0] = 'A';
	pos_arr[1][1] = '3';
	pos_arr[2][0] = 'B';
	pos_arr[2][1] = '3';
	pos_arr[3][0] = 'C';
	pos_arr[3][1] = '1';
	pos_arr[4][0] = 'C';
	pos_arr[4][1] = '3';
	return pos_arr;
}
static char* build_buffer(int size_buffer, int log2n, int log2m, boardPos* pos_arr)
{
	//decleration of variables
	int  row_num, col_num, index, index2, num_bit_pos;
	char* buffer;
	buffer = (char*)malloc((size_buffer + 1) * sizeof(char));//memory alloc
	allocation_check(buffer);// alloc check
	buffer[size_buffer] = '\0';
	index2 = 0;
	num_bit_pos = log2n + log2m;
	for (index = 0; index < size_buffer; index += num_bit_pos)// fill buffer from posv arr
	{
		row_num = pos_arr[index2][0] - 'A';
		col_num = pos_arr[index2][1] - '1';
		int2bin(row_num, buffer + index, log2n);
		int2bin(col_num, buffer + index + log2n, log2m);
		index2++;

	}
	return buffer;//output

}
void saveListTOBinFile(char* file_name, boardPos* pos_arr)
{
	//decleration of variables
	FILE *out_fptr;
	char* buffer;
	int index, index2, index3, log_2_N, log_2_M, size_buffer, shift_left, num_bit_pos;
	short int num_pos;
	unsigned char row, col, b = 0, c[BYTE_SIZE] = "00000000", d = 1;
	log_2_N = Log2(N);// calc of log2N & log2M
	log_2_M = Log2(M);
	num_bit_pos = log_2_N + log_2_M;
	out_fptr = fopen(file_name, "wb");// file open
	file_check5(out_fptr);// file check
	num_pos = calc_num_pos(pos_arr); //num pos calc
	row = N;
	col = M;
	fwrite(&num_pos, sizeof(short int), 1, out_fptr);// write num pos
	size_buffer = num_pos*(log_2_N + log_2_M);// calc size buffer
	buffer = build_buffer(size_buffer, log_2_N, log_2_M, pos_arr);// build buffer
	fwrite(&row, sizeof(unsigned char), 1, out_fptr);// write num row
	fwrite(&col, sizeof(unsigned char), 1, out_fptr);// write num col
	index2 = 0;
	for (index = 0; index < SIZE_POS_ARR; index++) {//writing  the cordintes  in the file
		if (check_pos(pos_arr[index])) {
			b = 0;
			for (index3 = 0; index3 < BYTE_SIZE && index2 < size_buffer; index3++) {//copy to arr of 8 char
				c[index3] = buffer[index2];
				index2++;
			}
			shift_left = SHIFT_RIGHT_TO_END;
			for (index3 = 0; index3 <BYTE_SIZE; index3++) {// shift number and create bite from arr
				if (c[index3] == '1')
					b = b | (d) << shift_left;
				shift_left--;
				c[index3] = '0';
			}
			fputc(b, out_fptr);// put chr in file
		}
		else// else for non valid number
			index2 -= num_bit_pos;
	}
	fclose(out_fptr);// close file
}
BOOL check_pos(boardPos pos)
{
	//decleration of variables
	BOOL res = FALSE;
	int row, col;
	row = pos[0] - 'A';
	col = pos[1] - '1';
	if (row < N && col < M)// check place
		res = TRUE;
	return res;//output
}
static short int calc_num_pos(boardPos* pos_arr)
{
	//decleration of variables
	short int res = 0;
	unsigned int index;
	for (index = 0; index < SIZE_POS_ARR; index++)//loop that calc num pos
	{
		if (check_pos(pos_arr[index]))
			res++;
	}
	return res;//output
}
static void file_check5(void *ptr)
{
	//decleration of variables
	if (!ptr)
	{
		fprintf(stderr, "Error opening file");
		exit(2);
	}
}