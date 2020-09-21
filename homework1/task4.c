#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int n, *isPrime;
    scanf("%d", &n);
    if (n < 0)
        return 0;
    isPrime = (int*)malloc((n + 1) * sizeof(int));
    memset(isPrime, 1, (n + 1) * sizeof(int));
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = 2 * i; j <= n; j += i)
                isPrime[j] = 0;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (isPrime[i])
            printf("%d ", i);
    }
    return 0;
}