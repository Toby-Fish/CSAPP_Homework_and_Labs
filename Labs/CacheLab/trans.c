/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, ii, jj, a0, a1, a2, a3, a4, a5, a6, a7;
	if (M == 32) {
		for (i = 0; i < N; i += 8) {
			for (j = 0; j < M; j += 8) {
				if (i == j) {
					a0 = A[i + 0][j + 0], a1 = A[i + 0][j + 1], a2 = A[i + 0][j + 2], a3 = A[i + 0][j + 3];
					a4 = A[i + 0][j + 4], a5 = A[i + 0][j + 5], a6 = A[i + 0][j + 6], a7 = A[i + 0][j + 7];
					B[i + 0][j + 0] = a0, B[i + 0][j + 1] = a1, B[i + 0][j + 2] = a2, B[i + 0][j + 3] = a3;
					B[i + 0][j + 4] = a4, B[i + 0][j + 5] = a5, B[i + 0][j + 6] = a6, B[i + 0][j + 7] = a7;

					a0 = A[i + 1][j + 0], a1 = A[i + 1][j + 1], a2 = A[i + 1][j + 2], a3 = A[i + 1][j + 3];
					a4 = A[i + 1][j + 4], a5 = A[i + 1][j + 5], a6 = A[i + 1][j + 6], a7 = A[i + 1][j + 7];
					B[i + 1][j + 0] = B[i + 0][j + 1], B[i + 0][j + 1] = a0;
					B[i + 1][j + 1] = a1, B[i + 1][j + 2] = a2, B[i + 1][j + 3] = a3;
					B[i + 1][j + 4] = a4, B[i + 1][j + 5] = a5, B[i + 1][j + 6] = a6, B[i + 1][j + 7] = a7;

					a0 = A[i + 2][j + 0], a1 = A[i + 2][j + 1], a2 = A[i + 2][j + 2], a3 = A[i + 2][j + 3];
					a4 = A[i + 2][j + 4], a5 = A[i + 2][j + 5], a6 = A[i + 2][j + 6], a7 = A[i + 2][j + 7];
					B[i + 2][j + 0] = B[i + 0][j + 2], B[i + 0][j + 2] = a0;
					B[i + 2][j + 1] = B[i + 1][j + 2], B[i + 1][j + 2] = a1;
					B[i + 2][j + 2] = a2, B[i + 2][j + 3] = a3;
					B[i + 2][j + 4] = a4, B[i + 2][j + 5] = a5, B[i + 2][j + 6] = a6, B[i + 2][j + 7] = a7;

					a0 = A[i + 3][j + 0], a1 = A[i + 3][j + 1], a2 = A[i + 3][j + 2], a3 = A[i + 3][j + 3];
					a4 = A[i + 3][j + 4], a5 = A[i + 3][j + 5], a6 = A[i + 3][j + 6], a7 = A[i + 3][j + 7];
					B[i + 3][j + 0] = B[i + 0][j + 3], B[i + 0][j + 3] = a0;
					B[i + 3][j + 1] = B[i + 1][j + 3], B[i + 1][j + 3] = a1;
					B[i + 3][j + 2] = B[i + 2][j + 3], B[i + 2][j + 3] = a2;
					B[i + 3][j + 3] = a3;
					B[i + 3][j + 4] = a4, B[i + 3][j + 5] = a5, B[i + 3][j + 6] = a6, B[i + 3][j + 7] = a7;

					a0 = A[i + 4][j + 0], a1 = A[i + 4][j + 1], a2 = A[i + 4][j + 2], a3 = A[i + 4][j + 3];
					a4 = A[i + 4][j + 4], a5 = A[i + 4][j + 5], a6 = A[i + 4][j + 6], a7 = A[i + 4][j + 7];
					B[i + 4][j + 0] = B[i + 0][j + 4], B[i + 0][j + 4] = a0;
					B[i + 4][j + 1] = B[i + 1][j + 4], B[i + 1][j + 4] = a1;
					B[i + 4][j + 2] = B[i + 2][j + 4], B[i + 2][j + 4] = a2;
					B[i + 4][j + 3] = B[i + 3][j + 4], B[i + 3][j + 4] = a3;
					B[i + 4][j + 4] = a4, B[i + 4][j + 5] = a5, B[i + 4][j + 6] = a6, B[i + 4][j + 7] = a7;

					a0 = A[i + 5][j + 0], a1 = A[i + 5][j + 1], a2 = A[i + 5][j + 2], a3 = A[i + 5][j + 3];
					a4 = A[i + 5][j + 4], a5 = A[i + 5][j + 5], a6 = A[i + 5][j + 6], a7 = A[i + 5][j + 7];
					B[i + 5][j + 0] = B[i + 0][j + 5], B[i + 0][j + 5] = a0;
					B[i + 5][j + 1] = B[i + 1][j + 5], B[i + 1][j + 5] = a1;
					B[i + 5][j + 2] = B[i + 2][j + 5], B[i + 2][j + 5] = a2;
					B[i + 5][j + 3] = B[i + 3][j + 5], B[i + 3][j + 5] = a3;
					B[i + 5][j + 4] = B[i + 4][j + 5], B[i + 4][j + 5] = a4;
					B[i + 5][j + 5] = a5, B[i + 5][j + 6] = a6, B[i + 5][j + 7] = a7;

					a0 = A[i + 6][j + 0], a1 = A[i + 6][j + 1], a2 = A[i + 6][j + 2], a3 = A[i + 6][j + 3];
					a4 = A[i + 6][j + 4], a5 = A[i + 6][j + 5], a6 = A[i + 6][j + 6], a7 = A[i + 6][j + 7];
					B[i + 6][j + 0] = B[i + 0][j + 6], B[i + 0][j + 6] = a0;
					B[i + 6][j + 1] = B[i + 1][j + 6], B[i + 1][j + 6] = a1;
					B[i + 6][j + 2] = B[i + 2][j + 6], B[i + 2][j + 6] = a2;
					B[i + 6][j + 3] = B[i + 3][j + 6], B[i + 3][j + 6] = a3;
					B[i + 6][j + 4] = B[i + 4][j + 6], B[i + 4][j + 6] = a4;
					B[i + 6][j + 5] = B[i + 5][j + 6], B[i + 5][j + 6] = a5;
					B[i + 6][j + 6] = a6, B[i + 6][j + 7] = a7;

					a0 = A[i + 7][j + 0], a1 = A[i + 7][j + 1], a2 = A[i + 7][j + 2], a3 = A[i + 7][j + 3];
					a4 = A[i + 7][j + 4], a5 = A[i + 7][j + 5], a6 = A[i + 7][j + 6], a7 = A[i + 7][j + 7];
					B[i + 7][j + 0] = B[i + 0][j + 7], B[i + 0][j + 7] = a0;
					B[i + 7][j + 1] = B[i + 1][j + 7], B[i + 1][j + 7] = a1;
					B[i + 7][j + 2] = B[i + 2][j + 7], B[i + 2][j + 7] = a2;
					B[i + 7][j + 3] = B[i + 3][j + 7], B[i + 3][j + 7] = a3;
					B[i + 7][j + 4] = B[i + 4][j + 7], B[i + 4][j + 7] = a4;
					B[i + 7][j + 5] = B[i + 5][j + 7], B[i + 5][j + 7] = a5;
					B[i + 7][j + 6] = B[i + 6][j + 7], B[i + 6][j + 7] = a6;
					B[i + 7][j + 7] = a7;
				}
				else {
					for (ii = i; ii < i + 8; ii++) {
						a0 = A[ii][j + 0];
						a1 = A[ii][j + 1];
						a2 = A[ii][j + 2];
						a3 = A[ii][j + 3];
						a4 = A[ii][j + 4];
						a5 = A[ii][j + 5];
						a6 = A[ii][j + 6];
						a7 = A[ii][j + 7];
						B[j + 0][ii] = a0;
						B[j + 1][ii] = a1;
						B[j + 2][ii] = a2;
						B[j + 3][ii] = a3;
						B[j + 4][ii] = a4;
						B[j + 5][ii] = a5;
						B[j + 6][ii] = a6;
						B[j + 7][ii] = a7;
					}
				}
			}
		}
	} 
	else if (M == 64) {
		for (i = 0; i < N; i += 8) {
			for (j = 0; j < M; j += 8) {
				for (ii = i; ii < i + 4; ii++) {
					a0 = A[ii][j + 0], a1 = A[ii][j + 1], a2 = A[ii][j + 2], a3 = A[ii][j + 3];
					a4 = A[ii][j + 4], a5 = A[ii][j + 5], a6 = A[ii][j + 6], a7 = A[ii][j + 7];
					B[j + 0][ii + 0] = a0, B[j + 1][ii + 0] = a1, B[j + 2][ii + 0] = a2, B[j + 3][ii + 0] = a3;
					B[j + 0][ii + 4] = a4, B[j + 1][ii + 4] = a5, B[j + 2][ii + 4] = a6, B[j + 3][ii + 4] = a7;
				}
				for (jj = j; jj < j + 4; jj++) {
					a0 = A[i + 4][jj], a1 = A[i + 5][jj], a2 = A[i + 6][jj], a3 = A[i + 7][jj];
					a4 = B[jj][i + 4], a5 = B[jj][i + 5], a6 = B[jj][i + 6], a7 = B[jj][i + 7];
					B[jj][i + 4] = a0, B[jj][i + 5] = a1, B[jj][i + 6] = a2, B[jj][i + 7] = a3;
					B[jj + 4][i + 0] = a4, B[jj + 4][i + 1] = a5, B[jj + 4][i + 2] = a6, B[jj + 4][i + 3] = a7;
				}
				for (ii = i + 4; ii < i + 8; ii++) {
					a0 = A[ii][j + 4], a1 = A[ii][j + 5], a2 = A[ii][j + 6], a3 = A[ii][j + 7];
					B[j + 4][ii] = a0, B[j + 5][ii] = a1, B[j + 6][ii] = a2, B[j + 7][ii] = a3;
				} 
			}
		}
	}
	else {
		for (i = 0; i < M; i += 16) {
			for (j = 0; j < N; j += 16) {
				for (jj = j; jj < j + 16 && jj < N; jj++) {
					for (ii = i; ii < i + 16 && i < M; ii++) {
						B[ii][jj] = A[jj][ii];
					}
				}


			}
		}
	}
}
/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

char trans_desc0[] = "Improved version 1";
void trans0(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, ii, a0, a1, a2, a3, a4, a5, a6, a7;
	for (i = 0; i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			for (ii = i; ii < i + 8; ii++) {
				a0 = A[ii][j + 0];
				a1 = A[ii][j + 1];
				a2 = A[ii][j + 2];
				a3 = A[ii][j + 3];
				a4 = A[ii][j + 4];
				a5 = A[ii][j + 5];
				a6 = A[ii][j + 6];
				a7 = A[ii][j + 7];
				B[j + 0][ii] = a0;
				B[j + 1][ii] = a1;
				B[j + 2][ii] = a2;
				B[j + 3][ii] = a3;
				B[j + 4][ii] = a4;
				B[j + 5][ii] = a5;
				B[j + 6][ii] = a6;
				B[j + 7][ii] = a7;
			}
		}
	}
}

char trans_desc1[] = "4 x 4";
void trans1(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, ii, a0, a1, a2, a3;
	for (i = 0; i < N; i += 4) {
		for (j = 0; j < M; j += 4) {
			for (ii = i; ii < i + 4; ii++) {
				a0 = A[ii][j + 0];
				a1 = A[ii][j + 1];
				a2 = A[ii][j + 2];
				a3 = A[ii][j + 3];
				B[j + 0][ii] = a0;
				B[j + 1][ii] = a1;
				B[j + 2][ii] = a2;
				B[j + 3][ii] = a3;
			}
		}
	}
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 
	//registerTransFunction(trans0, trans_desc0);
	//registerTransFunction(trans1, trans_desc1);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}



