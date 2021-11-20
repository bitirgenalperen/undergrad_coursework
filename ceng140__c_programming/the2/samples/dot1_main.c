#include <stdio.h>
#include "../the2.h"

int main()
{
    double **matrix;
    int row_size = 0, row_count = 0;

    matrix = initialize_the_data(&row_count, &row_size);

    calculate_dot_product(matrix, row_size, 1, 3);

    return 0;
}