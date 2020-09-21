#include <stdio.h>
#include <stdlib.h>
int main()
{
    int firstStringSize = 0, secondStringSize = 0;
    scanf("%d%d", &firstStringSize, &secondStringSize);
    char *s1, *s2;
    s1 = malloc(sizeof(*s1) * (firstStringSize + 1));
    s2 = malloc(sizeof(*s2) * (secondStringSize + 1));
    fgets(s1, firstStringSize + 1, stdin);
    fgets(s2, secondStringSize + 1, stdin);
    int answer = 0;
    for (int i = 0; i < firstStringSize; i++) {
        for (int j = 0; j < secondStringSize && i + j < firstStringSize; j++) {
            if (s1[i + j] != s2[j])
                break;
            if (j + 1 == secondStringSize)
                answer++;
        }
    }
    printf("%d", answer);
    return 0;
}