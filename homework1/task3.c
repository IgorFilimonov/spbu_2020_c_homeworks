#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxSize = 1000;

int main()
{
    char s1[maxSize], s2[maxSize];
    for (int i = 0; i < maxSize; i++) {
        s1[i] = '0';
        s2[i] = '0';
    }
    printf("Enter each string on a separate line:\n");
    fgets(s1, maxSize, stdin);
    fgets(s2, maxSize, stdin);

    int numberOfOccurrences = 0;
    int firstStringSize = strlen(s1) - 1, secondStringSize = strlen(s2) - 1;
    for (int i = 0; i < firstStringSize; i++) {
        for (int j = 0; j < secondStringSize && i + j < firstStringSize; j++) {
            if (s1[i + j] != s2[j])
                break;
            if (j + 1 == secondStringSize)
                numberOfOccurrences++;
        }
    }
    printf("%d", numberOfOccurrences);
    return 0;
}