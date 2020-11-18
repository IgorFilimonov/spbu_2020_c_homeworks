#ifndef SPBU_2020_C_HOMEWORKS_GRAPH_H
#define SPBU_2020_C_HOMEWORKS_GRAPH_H

#include <stdbool.h>

typedef struct Edge Edge;

typedef struct Graph Graph;

Edge* createEdge(int start, int end, int weight, bool oriented);

Graph* createGraph(int countEdges, int countVertex, Edge** edges);

bool depthFirstSearch(Graph* graph, int currentVertex, int* vertexState);

bool isConnected(int firstVertex, int secondVertex, Graph* graph);

bool isCycled(Graph* graph);

bool findNearestVacantVertex(Graph* graph, int vertex, bool* isVertexVacant, int* nearestVacantVertex, int* distanceToNearestVertex);

void destroyEdge(Edge* edge);

void destroyGraph(Graph* graph);

#endif //SPBU_2020_C_HOMEWORKS_GRAPH_H
