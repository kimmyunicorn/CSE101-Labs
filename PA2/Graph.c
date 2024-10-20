/* 
 * File:   Graph.c
 * Author: kimberlycamanero
 *
 * Created on October 15, 2024, 5:54 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
#include "Graph.h"


//struct for the graph
typedef struct GraphObj{
    List *adjacency_list; //An array of Lists whose ?th element contains the neighbors of vertex ?
    int size;  //the number of edges (called the size of the graph),
    int order; // the number of vertices (called the order of the graph),
    int source; //the label of the vertex that was most recently used as source for BFS
    int *color;  //An array of ints  whose ?th element is the color (white, gray, black) of vertex ?
    int *distance; //An array of ints whose ?th element is the distance from the (most recent) source to vertex ?
    int *parent; //An array of ints whose ?th element is the parent of vertex ?
}GraphObj;


/*** Constructors-Destructors ***/
Graph newGraph(int n){

    //It is recommended that all arrays be of length ? + 1, where ? is the number of vertices in the graph, and that only indices 1
    //through ? be used.  This is so that array indices can be directly identified with vertex labels.

    Graph G = malloc(sizeof(GraphObj)); //allocating memory for the graph
    G->adjacency_list = malloc(sizeof(List)); //allocating memory for the list
    G->size = 0;
    G->order = n; //n number of vertices
    G->source = NIL; //NIL means 0
    G->color = malloc((n+1) * sizeof(int)); //stores what type of color graph node will be
    G->distance =  malloc((n+1) * sizeof(int)); //stores the distance of that graph node to another
    G->parent =  malloc((n+1) * sizeof(int)); //stores the parent node of the vertex

    //allocate a value for each ith member of the adjacency list and create a list for each
    for(int i = 1; i<=n; i++) {
        G->adjacency_list[i] = newList();
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    return G;
}
void freeGraph(Graph* pG){

    if(pG == NULL || *pG == NULL ) {
        printf("Error trying to call freeGraph on non-existent graph\n");
        exit(1);
    }
    if(*pG != NULL && pG != NULL) {
        for(int i = 1; i <= (*pG)->size; i++) {
            freeList(&(*pG)->adjacency_list[i]);
        }
        free((*pG)->adjacency_list);
        free((*pG)->color);
        free((*pG)->distance);
        free((*pG)->parent);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/
int getOrder(Graph G){

    return G->order;
}
int getSize(Graph G){

    return G->size;

}
int getSource(Graph G){

    return G->source;
}
int getParent(Graph G, int u){

    return G->parent[u]; //since parent is an array, n u want to access the parent of the specified "uth" node
}
int getDist(Graph G, int u){

    return G->distance[u];//since distance  is an array, n u want to access the distance of the specified "uth" node
}
void getPath(List L, Graph G, int u){

    //diff error exception handling
    if(L == NULL) {
        printf("Error trying to get path from non-existent list\n");
        exit(1);
    }
    if(G == NULL){
        printf("Error trying to get path from non-existent graph\n");
        exit(1);
    }
    if(getSource(G) == NIL) {
        printf("Error: Trying to call getPath() before checking for relations w/ BFS\n");
        exit(1);
    }
    //checking if the bounds of the integer r valid
    if(u <1 || u > G->order) {
        printf("Error: Calling getPath() w/ invalid bounds\n");
        exit(1);
    }
    
    if(u == G->source) {
        append(L,G->source);
    }else if(G->parent[u] == NIL) {
        append(L,NIL);
    }else {
        getPath(L,G,G->parent[u]);
        append(L,u);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){

    for(int i =1; i<=G->order; i++) {
        clear(G->adjacency_list[i]);
    }
    G->size = 0; //reset the size
}
void addEdge(Graph G, int u, int v){


}
void addArc(Graph G, int u, int v){


}
void BFS(Graph G, int s){


}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){

    //traverse through the graph
    for(int i = 1; i <= G->order; i++) {
        fprintf(out, "%d-", i);
        printList(out,G->adjacency_list[i]); //prints the adjacency list of each
        fprintf(out, "\n");
    }
}

   
  


