#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

const int ALPHABET_SIZE = 26;

int* countLetters(FILE* inputFile)
{
    int* quantitiesOfLetters = (int*)calloc(ALPHABET_SIZE, sizeof(int));
    char currentChar = fgetc(inputFile);
    while (feof(inputFile) == 0) {
        if (islower(currentChar))
            quantitiesOfLetters[currentChar - 'a']++;
        currentChar = fgetc(inputFile);
    }

    return quantitiesOfLetters;
}

int main()
{
    FILE* inputFile = fopen("../test2/input.txt", "r");
    if (inputFile == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    int* quantitiesOfLetters = countLetters(inputFile);
    fclose(inputFile);

    FILE* outputFile = fopen("../test2/output.txt", "w");
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (quantitiesOfLetters[i] > 0)
            fprintf(outputFile, "%c -- %d\n", 'a' + i, quantitiesOfLetters[i]);
    }
    fclose(outputFile);
    free(quantitiesOfLetters);

    return 0;
}
