#include "../library/graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* readGraph(FILE* inputFile, int countStudents)
{
    Edge** dishonestStudents = (Edge**)calloc(countStudents - 3, sizeof(Edge*));
    int countDishonestStudents = 0;
    for (int i = 0; i < countStudents - 3; ++i) {
        int firstStudent = 0, secondStudent = 0;
        fscanf(inputFile, "%d%d", &firstStudent, &secondStudent);
        if (secondStudent != -1) {
            dishonestStudents[countDishonestStudents] = createEdge(firstStudent - 1, secondStudent - 1, 1, false);
            ++countDishonestStudents;
        }
    }

    Graph* graph = createGraph(countDishonestStudents, countStudents, dishonestStudents);
    for (int i = 0; i < countDishonestStudents; ++i)
        destroyEdge(dishonestStudents[i]);
    free(dishonestStudents);
    return graph;
}

int main()
{
    FILE* inputFile = fopen("../homework7/input.txt", "r");
    if (inputFile == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    int countStudents = 0;
    fscanf(inputFile, "%d", &countStudents);
    Graph* graph = readGraph(inputFile, countStudents);
    fclose(inputFile);

    int* numbersOfStolenWorks = findComponents(graph);
    printf("Here are the student numbers and whose work they passed:\n");
    for (int i = 0; i < countStudents; ++i) {
        if (numbersOfStolenWorks[i] > 2)
            printf("Student number %d didn't pass anything\n", i + 1);
        else
            printf("%d: %d\n", i + 1, numbersOfStolenWorks[i] + 1);
    }

    destroyGraph(graph);
    free(numbersOfStolenWorks);
    return 0;
}
