#include "fixstring.h"
#include <stdio.h>

void print_mf16(const mf16 *matrix)
{
    if (matrix->errors)
    {
        printf("MATRIX ERRORS: %d\n", matrix->errors);
    }
    
    int row, column;
    for (row = 0; row < matrix->rows; row++)
    {
        for (column = 0; column < matrix->columns; column++)
        {
            printf("%.6f ", matrix->data[row][column]);
        }
        printf("\n");
    }
}
