#include <stdio.h>
#include <stdlib.h>

void generatePartition(int number, int summandIndex, int* partition)
{
    if (number == 0) {
        for (int i = 0; i < summandIndex - 1; i++)
            printf("%d+", partition[i]);
        printf("%d\n", partition[summandIndex - 1]);
        return;
    }
    for (int summand = summandIndex != 0 ? partition[summandIndex - 1] : 1; summand <= number; summand++) {
        partition[summandIndex] = summand;
        generatePartition(number - summand, summandIndex + 1, partition);
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