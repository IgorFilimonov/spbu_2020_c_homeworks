#include "../library/graph.h"
#include "../library/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph* readGraph(FILE* inputFile, int countCities, int countRoads)
{
    Edge** roads = (Edge**)malloc(countRoads * sizeof(Edge*));
    for (int i = 0; i < countRoads; ++i) {
        int firstCity = 0, secondCity = 0, length = 0;
        fscanf(inputFile, "%d%d%d", &firstCity, &secondCity, &length);
        roads[i] = createEdge(firstCity - 1, secondCity - 1, length, false);
    }

    Graph* graph = createGraph(countRoads, countCities, roads);
    for (int i = 0; i < countRoads; ++i)
        destroyEdge(roads[i]);
    free(roads);
    return graph;
}

List** readCapitals(FILE* inputFile, int countStates)
{
    List** citiesOfStates = (List**)malloc(countStates * sizeof(List*));
    for (int i = 0; i < countStates; ++i) {
        citiesOfStates[i] = createList();
        int capital = 0;
        fscanf(inputFile, "%d", &capital);
        insert(createListElement(capital - 1), 0, citiesOfStates[i]);
    }

    return citiesOfStates;
}

bool addNearbyCities(List** citiesOfStates, Graph* graph, int countStates, int sizeOfTheLargestState, bool* isCityVacant)
{
    bool isAnyCityAdded = false;
    for (int i = 0; i < countStates; ++i) {
        if (getSize(citiesOfStates[i]) != sizeOfTheLargestState) // if true, it wasn't possible to increase the state last time
            continue;

        int nearestVacantCity = -1, distanceToNearestCity = 0;
        ListElement* currentCity = head(citiesOfStates[i]);
        for (int j = 0; j < sizeOfTheLargestState; ++j) {
            int possibleDistanceToNearestCity = 0;
            int possibleNearestVacantCity = findNearestVacantVertex(getValue(currentCity), graph, isCityVacant, &possibleDistanceToNearestCity);
            if (possibleNearestVacantCity != -1) {
                if (nearestVacantCity == -1 || possibleDistanceToNearestCity < distanceToNearestCity) {
                    nearestVacantCity = possibleNearestVacantCity;
                    distanceToNearestCity = possibleDistanceToNearestCity;
                }
            }
            currentCity = getNextElement(currentCity);
        }

        if (nearestVacantCity != -1) {
            insert(createListElement(nearestVacantCity), sizeOfTheLargestState, citiesOfStates[i]);
            isCityVacant[nearestVacantCity] = false;
            isAnyCityAdded = true;
        }
    }

    return isAnyCityAdded;
}

void printListsOfCities(List** citiesOfStates, int countStates)
{
    for (int i = 0; i < countStates; ++i) {
        ListElement* currentCity = head(citiesOfStates[i]);
        printf("State number %d includes cities: %d", i + 1, getValue(currentCity) + 1);
        for (int j = 1; j < getSize(citiesOfStates[i]); ++j) {
            currentCity = getNextElement(currentCity);
            printf(", %d", getValue(currentCity) + 1);
        }
        printf("\n");
    }
}

int main()
{
    FILE* inputFile = fopen("../homework7/input.txt", "r");
    if (inputFile == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    int countCities = 0, countRoads = 0;
    fscanf(inputFile, "%d%d", &countCities, &countRoads);
    Graph* graph = readGraph(inputFile, countCities, countRoads);
    int countStates = 0;
    fscanf(inputFile, "%d", &countStates);
    List** citiesOfStates = readCapitals(inputFile, countStates);
    fclose(inputFile);

    bool* isCityVacant = (bool*)malloc(countCities * sizeof(bool));
    memset(isCityVacant, true, countCities * sizeof(bool));
    for (int i = 0; i < countStates; ++i)
        isCityVacant[getValue(head(citiesOfStates[i]))] = false;
    for (int sizeOfTheLargestState = 1; sizeOfTheLargestState <= countCities; ++sizeOfTheLargestState) {
        if (!addNearbyCities(citiesOfStates, graph, countStates, sizeOfTheLargestState, isCityVacant))
            break;
    }
    free(isCityVacant);

    printListsOfCities(citiesOfStates, countStates);

    destroyGraph(graph);
    for (int i = 0; i < countStates; ++i)
        removeList(citiesOfStates[i]);
    free(citiesOfStates);
    return 0;
}
