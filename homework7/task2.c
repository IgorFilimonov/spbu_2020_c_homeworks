#include "../library/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readInputData(FILE* inputFile, int* countCities, int* countRoads, Edge*** roads, int* countStates, int*** citiesOfStates)
{
    fscanf(inputFile, "%d%d", countCities, countRoads);
    *roads = (Edge**)malloc(*countRoads * sizeof(Edge*));
    for (int i = 0; i < *countRoads; ++i) {
        int firstCity = 0, secondCity = 0, length = 0;
        fscanf(inputFile, "%d%d%d", &firstCity, &secondCity, &length);
        (*roads)[i] = createEdge(firstCity - 1, secondCity - 1, length, false);
    }

    fscanf(inputFile, "%d", countStates);
    *citiesOfStates = (int**)malloc(*countStates * sizeof(int*));
    for (int i = 0; i < *countStates; ++i) {
        (*citiesOfStates)[i] = (int*)malloc(*countCities * sizeof(int));
        memset((*citiesOfStates)[i], -1, *countCities * sizeof(int));

        int capital = 0;
        fscanf(inputFile, "%d", &capital);
        (*citiesOfStates)[i][0] = capital - 1;
    }
}

bool addNearbyCities(int countStates, int** citiesOfStates, int sizeOfTheLargestState, Graph* graph, bool* isCityVacant)
{
    bool isAnyCityAdded = false;
    for (int i = 0; i < countStates; ++i) {
        if (citiesOfStates[i][sizeOfTheLargestState - 1] == -1) // if true, it wasn't possible to increase the state last time
            continue;

        int nearestVacantCity = -1, distanceToNearestCity = 0;
        for (int j = 0; j < sizeOfTheLargestState; ++j) {
            int possibleNearestVacantCity = -1, possibleDistanceToNearestCity = 0;
            if (findNearestVacantVertex(graph, citiesOfStates[i][j], isCityVacant, &possibleNearestVacantCity, &possibleDistanceToNearestCity)) {
                if (nearestVacantCity == -1 || possibleDistanceToNearestCity < distanceToNearestCity) {
                    nearestVacantCity = possibleNearestVacantCity;
                    distanceToNearestCity = possibleDistanceToNearestCity;
                }
            }
        }

        if (nearestVacantCity != -1) {
            citiesOfStates[i][sizeOfTheLargestState] = nearestVacantCity;
            isCityVacant[nearestVacantCity] = false;
            isAnyCityAdded = true;
        }
    }

    return isAnyCityAdded;
}

void printListsOfCities(int countStates, int** citiesOfStates, int countCities)
{
    for (int i = 0; i < countStates; ++i) {
        printf("State number %d includes cities: %d", i + 1, citiesOfStates[i][0] + 1);
        for (int j = 1; j < countCities && citiesOfStates[i][j] != -1; ++j)
            printf(", %d", citiesOfStates[i][j] + 1);
        printf("\n");
    }
}

void clearMemory(int countRoads, Edge** roads, int countStates, int** citiesOfStates, Graph* graph, bool* isCityVacant)
{
    for (int i = 0; i < countRoads; ++i)
        destroyEdge(roads[i]);
    free(roads);
    for (int i = 0; i < countStates; ++i)
        free(citiesOfStates[i]);
    free(citiesOfStates);
    destroyGraph(graph);
    free(isCityVacant);
}

int main()
{
    FILE* inputFile = fopen("../homework7/input.txt", "r");
    if (inputFile == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    int countCities = 0, countRoads = 0, countStates = 0;
    Edge** roads = NULL;
    int** citiesOfStates = NULL;
    readInputData(inputFile, &countCities, &countRoads, &roads, &countStates, &citiesOfStates);
    Graph* graph = createGraph(countRoads, countCities, roads);

    bool* isCityVacant = (bool*)malloc(countCities * sizeof(bool));
    memset(isCityVacant, true, countCities * sizeof(bool));
    for (int i = 0; i < countStates; ++i)
        isCityVacant[citiesOfStates[i][0]] = false;
    bool areAllCitiesDistributed = false;
    int sizeOfTheLargestState = 1;
    while (!areAllCitiesDistributed) {
        if (!addNearbyCities(countStates, citiesOfStates, sizeOfTheLargestState, graph, isCityVacant))
            areAllCitiesDistributed = true;
        else {
            ++sizeOfTheLargestState;
            if (sizeOfTheLargestState == countCities)
                areAllCitiesDistributed = true;
        }
    }

    printListsOfCities(countStates, citiesOfStates, countCities);

    clearMemory(countRoads, roads, countStates, citiesOfStates, graph, isCityVacant);
    fclose(inputFile);
    return 0;
}
