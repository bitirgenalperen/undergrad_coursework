#include <stdio.h>
#include "../the2.h"

int main()
{
    double **matrix, **covariance_matrix;
    int row_size = 0, row_count = 0;

    matrix = initialize_the_data(&row_count, &row_size);
    covariance_matrix = calculate_covariance_matrix(matrix, row_count, row_size);

    print_first_n_row(covariance_matrix, row_size, row_size);

    return 0;
}