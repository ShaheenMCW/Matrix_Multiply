#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int **matrix_multiply_ijk(int **A, int **B, int size);
int **matrix_multiply_ikj(int **A, int **B, int size);
int **matrix_multiply_jik(int **A, int **B, int size);
int **matrix_multiply_kij(int **A, int **B, int size);
int **matrix_multiply_kji(int **A, int **B, int size);
void free_matrix(int **matrix, int size);

#define BASE_DIR "Unit_test"

// read a matrix
int **read_matrix(const char *filename, int *size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        return NULL;
    }

    fscanf(file, "%d", size);

    int **matrix = (int **)malloc((*size) * sizeof(int *));
    for (int i = 0; i < *size; i++)
    {
        matrix[i] = (int *)malloc((*size) * sizeof(int));
        for (int j = 0; j < *size; j++)
        {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

// compare
int compare_matrices(int **A, int **B, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (A[i][j] != B[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}


int main()
{
    struct dirent *entry;
    DIR *dir = opendir(BASE_DIR);
    FILE *output_file = fopen("result/matrix_multiplication_results.csv", "w");

    if (!dir)
    {
        perror("Unable to open Unit_test directory");
        return 1;
    }

    if (!output_file)
    {
        perror("Unable to open output file");
        return 1;
    }

    fprintf(output_file, "Test Case,Matrix Size,Method,Time Taken (Seconds)\n");

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR && strncmp(entry->d_name, "unit_", 5) == 0)
        {
            char unit_path[256];
            snprintf(unit_path, sizeof(unit_path), "%s/%s", BASE_DIR, entry->d_name);

            char file_A[256], file_B[256], file_C[256];
            snprintf(file_A, sizeof(file_A), "%s/A.txt", unit_path);
            snprintf(file_B, sizeof(file_B), "%s/B.txt", unit_path);
            snprintf(file_C, sizeof(file_C), "%s/C.txt", unit_path);

            printf("\n--- Processing %s ---\n", entry->d_name);

            int size_A, size_B, size_C;
            int **A = read_matrix(file_A, &size_A);
            int **B = read_matrix(file_B, &size_B);
            int **C = read_matrix(file_C, &size_C);

            if (A && B && C)
            {
                char *methods[] = {"ijk", "ikj", "jik", "kij", "kji"};
                int **result;

                for (int m = 0; m < 5; m++)
                {
                    
                    switch (m)
                    {
                    case 0:
                        result = matrix_multiply_ijk(A, B, size_A);
                        break;
                    case 1:
                        result = matrix_multiply_ikj(A, B, size_A);
                        break;
                    case 2:
                        result = matrix_multiply_jik(A, B, size_A);
                        break;
                    case 3:
                        result = matrix_multiply_kij(A, B, size_A);
                        break;
                    case 4:
                        result = matrix_multiply_kji(A, B, size_A);
                        break;
                    }

                    if (compare_matrices(result, C, size_A))
                    {
                        printf("%s method: Matrix multiplication result matches the expected matrix.\n", methods[m]);
                    }
                    else
                    {
                        printf("%s method: Matrix multiplication result does NOT match the expected matrix.\n", methods[m]);
                    }

                    fprintf(output_file, "%s,%d,%s,%.6f\n", entry->d_name, size_A, methods[m], 0.0); 

                    free_matrix(result, size_A);
                }

                free_matrix(A, size_A);
                free_matrix(B, size_B);
                free_matrix(C, size_C);
            }
            else
            {
                printf("Error reading matrices in %s\n", unit_path);
            }
        }
    }

    closedir(dir);
    fclose(output_file);

    return 0;
}
