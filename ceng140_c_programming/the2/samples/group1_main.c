#include <stdio.h>
#include "../the2.h"

int main()
{
    double **matrix, **group_matrix;
    int row_size = 0, row_count = 0, group_count;

    matrix = initialize_the_data(&row_count, &row_size);
    group_matrix = group_by(matrix, &group_count, row_count, row_size, 2, 0);

    print_first_n_row(group_matrix, group_count, row_size);

    return 0;
}