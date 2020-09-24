#include <stdio.h>
#include <stdlib.h>

int main()
{
    int firstStringSize = 0, secondStringSize = 0;
    printf("Enter sizes of strings:\n");
    scanf("%d%d", &firstStringSize, &secondStringSize);
    char *s1 = NULL, *s2 = NULL, *forEnter = NULL;
    s1 = malloc(sizeof(*s1) * (firstStringSize + 1));
    s2 = malloc(sizeof(*s2) * (secondStringSize + 1));
    forEnter = malloc(sizeof(*forEnter) * 2);
    printf("Enter each string on a separate line:\n");
    fgets(forEnter, 2, stdin);
    fgets(s1, firstStringSize + 1, stdin);
    fgets(forEnter, 2, stdin);
    fgets(s2, secondStringSize + 1, stdin);
    free(forEnter);

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
    free(s1);
    free(s2);
    return 0;
}