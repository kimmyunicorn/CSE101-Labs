//defining infinity and nil
//a color ?????[?] which may be white, gray, or black;
#define INF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3



typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n); //returns a Graph pointing to a newly created GraphObj representing a graph having ? vertices and no edges.

void freeGraph(Graph* pG); //frees all heap memory associated with the Graph *pG,then sets the handle *pG to NULL.


/*** Access functions ***/

int getOrder(Graph G); //return the corresponding field values

int getSize(Graph G); //return the corresponding field values

int getSource(Graph G); //returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called. 

int getParent(Graph G, int u); //will return the parent of vertex ? in the BFS tree created by BFS(), or NIL if BFS() has not yet been called.

int getDist(Graph G, int u); //returns the distance from the most recent BFS source to vertex ?, or INF if BFS() has not yet been called. 

void getPath(List L, Graph G, int u); //appends to the List ? the vertices of a shortest path in ? from source to ?, or appends to ? the value NIL if no such path exists. getPath() has the precondition getSource(G)!=NIL, so BFS() must be called before getPath() is called.

//Functions getParent(), getDist() and getPath() all have the precondition 1 ? ? ? getOrder(?).


/*** Manipulation procedures ***/

void makeNull(Graph G); //deletes all edges of ?, restoring it to its original (no edge) state. (This is called a null graph in graph theory literature).

void addEdge(Graph G, int u, int v); //inserts a new edge joining ? to ?, i.e. ? is added to the adjacency List of ?, and ? to the adjacency List of ?. Your program is required to maintain these lists in sorted order by increasing labels.

void addArc(Graph G, int u, int v); //inserts a new directed edge from ? to ?, i.e. ? is added to the adjacency List of ? (but not ? to the adjacency List of ?). Both addEdge() and addArc() have the precondition that their two int arguments must lie in the range 1 to getOrder(G).

void BFS(Graph G, int s); //runs the BFS algorithm on the Graph ? with source ?, setting the color, distance, parent, and source fields of ? accordingly. It also has the precondition that the int argument ? liesin the range 1 to getOrder(G). 


/*** Other operations ***/

void printGraph(FILE* out, Graph G); //prints the adjacency list representation of ? to the file pointed to by out. The format of this representation should match the above examples, so all that is required by the client is a single call to printGraph().
