#include "../library/graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* readGraph(FILE* inputFile)
{
    int countVertex = 0, countEdges = 0;
    fscanf(inputFile, "%d%d", &countVertex, &countEdges);
    int** incidenceMatrix = (int**)calloc(countVertex, sizeof(int*));
    for (int i = 0; i < countVertex; ++i) {
        incidenceMatrix[i] = (int*)calloc(countEdges, sizeof(int));
        for (int j = 0; j < countEdges; ++j)
            fscanf(inputFile, "%d", &incidenceMatrix[i][j]);
    }

    Edge** edges = (Edge**)calloc(countEdges, sizeof(Edge*));
    for (int i = 0; i < countEdges; ++i) {
        int startVertex = -1, finishVertex = -1;
        for (int j = 0; j < countVertex; ++j) {
            if (incidenceMatrix[j][i] == 1)
                startVertex = j;
            if (incidenceMatrix[j][i] == -1)
                finishVertex = j;
            if (startVertex != -1 && finishVertex != -1)
                break;
        }
        edges[i] = createEdge(startVertex, finishVertex, 1, true);
    }

    Graph* graph = createGraph(countEdges, countVertex, edges);

    for (int i = 0; i < countVertex; ++i)
        free(incidenceMatrix[i]);
    free(incidenceMatrix);
    for (int i = 0; i < countEdges; ++i)
        destroyEdge(edges[i]);
    free(edges);

    return graph;
}

int main()
{
    FILE* inputFile = fopen("../test2/input.txt", "r");
    if (inputFile == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    Graph* graph = readGraph(inputFile);
    int vertex = 0;
    fscanf(inputFile, "%d", &vertex);
    fclose(inputFile);

    int countVertex = getNumberOfVertex(graph);
    int* vertexState = (int*)calloc(countVertex, sizeof(int));
    depthFirstSearch(graph, vertex - 1, vertexState);

    printf("Here is a list of vertex unreachable from a given:\n");
    for (int i = 0; i < countVertex; ++i) {
        if (vertexState[i] == 0)
            printf("%d ", i + 1);
    }

    destroyGraph(graph);
    free(vertexState);
    return 0;
}
