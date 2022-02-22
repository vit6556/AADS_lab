#include <stdio.h>
#include <stdlib.h>

int input_num() {
    int num, status, temp;
    status = scanf("%d", &num);
    while(status != 1){
        while((temp = getchar()) != EOF && temp != '\n');
        printf("Incorrect number... please try again: ");
        status = scanf("%d", &num);
    }

    return num;
}

void allocate_memory(int m, int n, int *matrix[], int **ans) {
    for (int i = 0; i < m; ++i) {
        matrix[i] = calloc(n, sizeof(int));
    }
    *ans = calloc(n, sizeof(int));
}

void free_memory(int m, int n, int *matrix[], int *ans) {
    for (int i = 0; i < m; ++i) {
        free(matrix[i]);
    }
    free(ans);
}

void input_matrix(int m, int n, int *matrix[]) {
    for (int i = 0 ; i < m; ++i)  {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void find_ans(int m, int n, int *matrix[], int *ans) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > matrix[(i + m - 1) % m][j]) {
                ans[j] += matrix[i][j];
            }
        }
    }
}

void print_ans(int m, int n, int *matrix[], int *ans) {
    printf("\nInput matrix:\n");
    for (int i = 0 ; i < m; ++i)  {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nAnswer vector:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}


int main() {
    int m, n;
    printf("Amount of rows: ");
    m = input_num();
    printf("Amount of cols: ");
    n = input_num();

    int *matrix[n], *ans;
    allocate_memory(m, n, matrix, &ans);

    printf("Matrix:\n");
    input_matrix(m, n, matrix);
    find_ans(m, n, matrix, ans);
    print_ans(m, n, matrix, ans);

    free_memory(m, n, matrix, ans);
}