#ifndef ___FUNCTIONS5____
#define ___FUNCTIONS5____
/***** INCLUDES *****/
#include "functions2.h"

/***** DEFINES *****/
#define SIZE_POS_ARR 5
#define BINARY_DIV 2
#define SHIFT_RIGHT_TO_END 7
#define BYTE_SIZE 8
 /******************* Function Prototypes *******************/
boardPos *build_pos_arr();// build pos arr f
void saveListTOBinFile(char* file_name, boardPos* pos_arr);// save pos list to bin file f
int Log2(double n);// calc log2 of number
BOOL check_pos(boardPos pos);// check pos f
#endif
