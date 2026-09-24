#include <stdio.h>
#include <stdlib.h>

int* dynamicArray(int n, int queries_rows, int queries_columns,
                  int** queries, int* result_count) {

    int **seq = (int **)calloc(n, sizeof(int *));
    int *size = (int *)calloc(n, sizeof(int));
    int *capacity = (int *)calloc(n, sizeof(int));

    int lastAnswer = 0;
    int resultSize = 0;

    int *answers = (int *)malloc(queries_rows * sizeof(int));

    for (int i = 0; i < queries_rows; i++) {

        int type = queries[i][0];
        int x = queries[i][1];
        int y = queries[i][2];

        int index = (x ^ lastAnswer) % n;

        if (type == 1) {

            if (size[index] == capacity[index]) {
                capacity[index] = (capacity[index] == 0)
                                    ? 1
                                    : capacity[index] * 2;

                seq[index] = (int *)realloc(
                    seq[index],
                    capacity[index] * sizeof(int)
                );
            }

            seq[index][size[index]] = y;
            size[index]++;

        } else {

            lastAnswer = seq[index][y % size[index]];

            answers[resultSize++] = lastAnswer;
        }
    }

    *result_count = resultSize;

    for (int i = 0; i < n; i++)
        free(seq[i]);

    free(seq);
    free(size);
    free(capacity);

    return answers;
}