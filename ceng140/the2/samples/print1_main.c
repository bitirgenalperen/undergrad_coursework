#include <stdio.h>
#include "../the2.h"

int main()
{
    double **matrix;
    int row_size = 0, row_count = 0;

    matrix = initialize_the_data(&row_count, &row_size);
    print_first_n_row(matrix, row_count, row_size);

    return 0;
}