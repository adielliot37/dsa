typedef struct node {
  int toNode;
  int weight;
  struct node *next;
} node;


typedef struct graph {
  node **A;     //A is pointer to an array of pointers
  int n;
} graph;


typedef struct edge {
  int start, dest, wt;
} edge;


void init_graph(graph *, char *file);
void display_list(graph);
void DisplayMatrix(graph g);
void BFS(graph, int);
void DFS(graph, int);
int out_degree(graph, int);
int in_degree(graph, int);
int is_directed(graph);
edge *PrimsMST(graph , int );
void Dijkstra(graph, int);
void driver(char *);

