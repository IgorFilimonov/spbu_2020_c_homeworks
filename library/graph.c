#include "graph.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
    int start;
    int end;
    int weight;
    bool oriented;
};

struct Graph {
    int** matrix;
    int countVertex;
    int countEdges;
};

Edge* createEdge(int start, int end, int weight, bool oriented)
{
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->start = start;
    newEdge->end = end;
    newEdge->weight = weight;
    newEdge->oriented = oriented;
    return newEdge;
}

void initializeMatrix(Graph* graph, Edge** edges);

Graph* createGraph(int countEdges, int countVertex, Edge** edges)
{
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));
    newGraph->countVertex = countVertex;
    newGraph->countEdges = countEdges;
    initializeMatrix(newGraph, edges);
    return newGraph;
}

void initializeMatrix(Graph* graph, Edge** edges)
{
    graph->matrix = (int**)malloc(graph->countVertex * sizeof(int*));
    for (int i = 0; i < graph->countVertex; ++i)
        graph->matrix[i] = (int*)calloc(graph->countVertex, sizeof(int));

    for (int i = 0; i < graph->countEdges; ++i) {
        graph->matrix[edges[i]->start][edges[i]->end] = edges[i]->weight;
        if (!edges[i]->oriented)
            graph->matrix[edges[i]->end][edges[i]->start] = edges[i]->weight;
    }
}

bool depthFirstSearch(Graph* graph, int currentVertex, int* vertexState)
{
    vertexState[currentVertex] = 1;
    for (int i = 0; i < graph->countVertex; i++) {
        if (graph->matrix[currentVertex][i] != 0) {
            if (vertexState[i] == 1 || vertexState[i] == 0 && depthFirstSearch(graph, i, vertexState))
                return true;
        }
    }

    vertexState[currentVertex] = 2;
    return false;
}

bool isConnected(int firstVertex, int secondVertex, Graph* graph)
{
    int* vertexState = (int*)calloc(graph->countVertex, sizeof(int));
    depthFirstSearch(graph, firstVertex, vertexState);
    bool isConnected = vertexState[secondVertex] > 0;
    free(vertexState);
    return isConnected;
}

bool isCycled(Graph* graph)
{
    int* vertexState = (int*)calloc(graph->countVertex, sizeof(int));
    bool isCycled = false;
    for (int i = 0; i < graph->countVertex; ++i) {
        if (vertexState[i] == 0 && depthFirstSearch(graph, i, vertexState)) {
            isCycled = true;
            break;
        }
    }

    free(vertexState);
    return isCycled;
}

int findNearestVacantVertex(int vertex, Graph* graph, bool* isVertexVacant, int* distanceToNearestVertex)
{
    int nearestVacantVertex = -1;
    *distanceToNearestVertex = 0;
    for (int i = 0; i < graph->countVertex; ++i) {
        if (graph->matrix[vertex][i] != 0 && isVertexVacant[i]) {
            if (nearestVacantVertex == -1 || graph->matrix[vertex][i] < *distanceToNearestVertex) {
                nearestVacantVertex = i;
                *distanceToNearestVertex = graph->matrix[vertex][i];
            }
        }
    }

    return nearestVacantVertex;
}

void destroyEdge(Edge* edge)
{
    free(edge);
}

void destroyGraph(Graph* graph)
{
    for (int i = 0; i < graph->countVertex; ++i)
        free(graph->matrix[i]);
    free(graph);
}

void findComponentsRecursive(Graph* graph, int currentVertex, int** componentNumbers, int currentComponent);

int* findComponents(Graph* graph)
{
    int* componentNumbers = (int*)malloc(graph->countVertex * sizeof(int));
    memset(componentNumbers, -1, graph->countVertex * sizeof(int));
    int currentComponent = 0;
    for (int i = 0; i < graph->countVertex; ++i) {
        if (componentNumbers[i] == -1) {
            findComponentsRecursive(graph, i, &componentNumbers, currentComponent);
            ++currentComponent;
        }
    }

    return componentNumbers;
}

void findComponentsRecursive(Graph* graph, int currentVertex, int** componentNumbers, int currentComponent)
{
    (*componentNumbers)[currentVertex] = currentComponent;
    for (int i = 0; i < graph->countVertex; ++i) {
        if (graph->matrix[currentVertex][i] != 0 && (*componentNumbers)[i] == -1)
            findComponentsRecursive(graph, i, componentNumbers, currentComponent);
    }
}

int getNumberOfVertex(Graph* graph)
{
    return graph->countVertex;
}
