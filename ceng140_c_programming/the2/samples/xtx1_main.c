#include <stdio.h>
#include "../the2.h"

int main()
{
    double **matrix, **result;
    int row_size = 0, row_count = 0;

    matrix = initialize_the_data(&row_count, &row_size);
    result = calculate_x_transpose_times_x(matrix, row_count, row_size);

    print_first_n_row(result, row_size, row_size);

    return 0;
}