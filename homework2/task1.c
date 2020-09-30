#include <stdio.h>
#include <stdlib.h>

void generatePartition(int number, int sizeOfPartition, int* partition)
{
    if (number == 0) {
        for (int i = 0; i < sizeOfPartition - 1; i++)
            printf("%d+", partition[i]);
        printf("%d\n", partition[sizeOfPartition - 1]);
        return;
    }

    int additionTerm = 0;
    if (sizeOfPartition != 0)
        additionTerm = partition[sizeOfPartition - 1];
    else
        additionTerm = 1;
    for ( ; additionTerm <= number; ++additionTerm) {
        partition[sizeOfPartition] = additionTerm;
        generatePartition(number - additionTerm, sizeOfPartition + 1, partition);
    }
}

int main()
{
    int n = 0;
    printf("Enter n:\n");
    scanf("%d", &n);
    int* partition = (int*)calloc(n, sizeof(int));
    generatePartition(n, 0, partition);
    free(partition);
    return 0;
}