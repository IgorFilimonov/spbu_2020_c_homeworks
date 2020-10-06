#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n = 0;
    printf("Enter n:\n");
    scanf("%d", &n);
    if (n < 0)
        return 0;

    bool* isPrime = (bool*)malloc((n + 1) * sizeof(bool));
    memset(isPrime, true, (n + 1) * sizeof(bool));
    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = 2 * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (isPrime[i])
            printf("%d ", i);
    }
    free(isPrime);
    return 0;
}