/** Name: Max Halbert
    Date: 4/6/2020
    Title: matrix_multiplication
    Description: In this program it will use threads to perform a parallel 2D matrix multiply.
        Matrix A x Matrix B = Matrix C.
        Each thread is to compute and store each column value of a row in matrix C. 
**/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// Following is usede for testing purpose

/**
#define M 2
#define N 3
#define L 4
**/


#define M 1024      // Number of columns in A and rows in B
#define N 1024      // Number of rows in A and C
#define L 1024      // Number of columns in B and C



double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

pthread_t threads[N];
int thread_row[N];

void initialize_matrices();
void print_matrix(int row, int col, double *m);

void *row_col_multiply(void *row);


// pass argument p if want to print content of matrices
int main(int argc, char *argv[])
{
    int i;
   
    initialize_matrices();   // elements in Matrix A and B
    
    // N number of threads will be created to do matrix multiplication
    for (i = 0; i < N; i++)
    {
        thread_row[i] = i;  // row number that the created thread to compute
        
        if (pthread_create(&threads[i], NULL, row_col_multiply, &thread_row[i]))
        {
            // computer system failed to create thread
            printf("failed thread create!\n");
            return 0;
        }
        //printf("thread %u is created for row %d.\n", (int)threads[i], thread_row[i]);
    }
    
    // Wait for all the threads to be done before printing the result
    for (i = 0; i < N; i++) 
    {        
        pthread_join(threads[i],NULL);
        //printf("Thread %d returned\n", i);
    }
    
    printf("\nAll the %d threads are done - Matrix multiplication completed!\n", N);
    
    // contents of matrix A, B and C will be printed if there is a 'p' argument
    // when program is executed
    if (argc >1 && (*argv[1] == 'p'))
    {
        printf("\nMatrix A\n");
        print_matrix(N, M, (double *)matrixA);
        printf("\nMatrix B\n");
        print_matrix(M, L, (double *)matrixB);
        printf("\nMatrix C\n");
        print_matrix(N, L, (double *)matrixC);
    }
    
    printf("\nMain thread done.\n");
    
    return 0;
}

// Function to initialize matrix A and B
void initialize_matrices()
{
    int i,j;
    
    srand(time(NULL));  // seed for the random number generator
    
    // initialize matrix A
    for (i=0; i<N; i++)
    {
        for (j = 0; j < M; j++)
        {
            matrixA[i][j] = rand(); // random number for each element
        }
    }
    
    // initialize matrix B
    for (i=0; i<M; i++)
    {
        for (j = 0; j < L; j++)
        {
            matrixB[i][j] = rand(); // random number for each element
        }
    }
        
}

// Function to print out the content of a matrix
void print_matrix(int row, int col, double *m)
{
    int i, j;
    // print out row by row
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%.0f\t", m[i*col + j]);
        }
        printf("\n");
    }
}

// thread function to compute a row in matrix C
void *row_col_multiply(void *row)
{
    int i = *(int *)row;    // the row that the thread will compute
    int j, k;
    double temp;
    
    //printf("Hello from thread %u with iteration %d\n", (int)pthread_self(), i);
    
    // compute every column at row i
    for (j = 0; j < L; j++)
    {
        temp = 0;
        for (k = 0; k < M; k++)
        {
            temp += matrixA[i][k] * matrixB[k][j];
        }
        matrixC[i][j] = temp;
    } 
    
    return 0;
}