#include <stdlib.h>
// ijk
int **matrix_multiply_ijk(int **A, int **B, int N)
{
    int **result = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        result[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}
// ikj
int **matrix_multiply_ikj(int **A, int **B, int size)
{
    int **C = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        C[i] = (int *)malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < size; k++)
        {
            for (int j = 0; j < size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// jik
int **matrix_multiply_jik(int **A, int **B, int size)
{
    int **C = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        C[i] = (int *)malloc(size * sizeof(int));
    }

    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// kij
int **matrix_multiply_kij(int **A, int **B, int size)
{
    int **C = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        C[i] = (int *)malloc(size * sizeof(int));
    }

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// kji
int **matrix_multiply_kji(int **A, int **B, int size)
{
    int **C = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        C[i] = (int *)malloc(size * sizeof(int));
    }

    for (int k = 0; k < size; k++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int i = 0; i < size; i++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

void free_matrix(int **matrix, int N)
{
    for (int i = 0; i < N; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
