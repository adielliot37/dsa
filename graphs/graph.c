#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "queue.h"

int min_distance(int *visited, int *cost, int n); // utility function for Dijkastra's algo
void print_shortest_distance(int n, int *arr);
void DFS_repetitive(graph g, int n, int *visited);

void init_graph(graph *g, char *file)
{
  FILE *fptr;
  fptr = fopen(file, "r");
  int n;
  fscanf(fptr, "%d", &n);
  g->n = n;
  g->A = (node **)malloc(sizeof(node *) * n);
  for (int i = 0; i < n; i++)
  {
    g->A[i] = NULL;
  } // initialized the array of pointers to node to NULL

  int w;
  node *p = NULL;
  for (int i = 0; i < n; i++)
  {
    p = g->A[i];
    for (int j = 0; j < n; j++)
    {
      p = g->A[i];
      fscanf(fptr, "%d", &w);
      if (g->A[i] == NULL && w != 0)
      {
        node *temp = (node *)malloc(sizeof(node));
        temp->toNode = j;
        temp->weight = w;
        temp->next = NULL;
        g->A[i] = temp;
      }
      else if (w != 0)
      {
        while (p->next)
        {
          p = p->next;
        }
        node *temp = (node *)malloc(sizeof(node));
        temp->toNode = j;
        temp->weight = w;
        temp->next = NULL;
        p->next = temp;
      }
    }
  }
  fclose(fptr);
  return;
}

void display_list(graph g)
{
  printf("List representation :\n\n");
  for (int i = 0; i < g.n; i++)
  {
    printf("%d ", i + 1);
    node *p = g.A[i];
    while (p)
    {
      printf("--> %d ", p->toNode + 1);
      p = p->next;
    }
    printf("\n");
  }

  return;
}

void DisplayMatrix(graph g)
{
  node *p = NULL;
  int k;
  printf("\n");
  for (int i = 0; i < g.n; i++)
  {
    k = 0;
    p = g.A[i];
    while (k < g.n)
    {
      if (p && p->toNode == k)
      {
        printf("%d ", p->weight);
        p = p->next;
      }
      else
      {
        printf("0 ");
      }
      k++;
    }
    printf("\n");
  }
  printf("\n");
}

void BFS(graph g, int n)
{
  if (n >= g.n || n < 0)
  {
    printf("NODE NOT FOUND!\n\n");
    return;
  }

  int *visited = (int *)calloc(g.n, sizeof(int));
  queue q;
  init_queue(&q, g.n);
  printf("%d ", n + 1); // printing the very first node;
  enqueue(&q, n);
  visited[n] = 1;
  int u;
  node *p = NULL;

  while (!is_queue_empty(q))
  {
    u = dequeue(&q);
    node *p = g.A[u];
    while (p)
    {
      int i = p->toNode;
      if (visited[i] == 0)
      {
        printf("%d ", i + 1);
        visited[i] = 1;
        enqueue(&q, p->toNode);
      }
      p = p->next;
    }
  }
  printf("\n");

  return;
}


void DFS(graph g, int n)
{
  if (n >= g.n || n < 0)
  {
    printf("NODE NOT FOUND!\n\n");
    return;
  }
  int *visited = (int *)calloc(g.n, sizeof(int));
  DFS_repetitive(g, n, visited);
  printf("\n");
  free(visited);

  return;
}


void DFS_repetitive(graph g, int n, int *visited)
{
  printf("%d ", n + 1);
  visited[n] = 1;
  node *p = NULL;
  p = g.A[n];
  while (p)
  {
    int i = p->toNode;
    if (visited[i] == 0)
      DFS_repetitive(g, i, visited);

    p = p->next;
  }

  return;
}


int in_degree(graph g, int n)
{
  if (n >= g.n || n < 0)
  {
    printf("NODE NOT FOUND\n\n");
    return -1;
  }

  int sum = 0;
  for (int i = 0; i < g.n; i++) // to parse the array of pointers to nodes
  {
    node *p = NULL;
    p = g.A[i];
    while (p) // to parse the list corresponding to each ptr in the array
    {
      if (p->toNode == n)
        sum++;

      p = p->next;
    }
  }

  return sum;
}


int out_degree(graph g, int n)
{
  if (n >= g.n || n < 0)
  {
    printf("NODE NOT FOUND!\n\n");
    return -1;
  }

  int sum = 0;
  node *p = NULL;
  p = g.A[n];
  while (p) // catch n from the array of pointers and count the nodes in its correspondence
  {
    sum++;
    p = p->next;
  }

  return sum;
}


int is_directed(graph g)
{
  node *p = NULL;
  node *q = NULL;
  int key;
  for (int i = 0; i < g.n; i++)
  {
    key = 0;
    p = g.A[i];
    while (p)
    {
      q = g.A[p->toNode];
      while (q)
      {
        if (q->toNode == i)
        {
          key = 1;
          break;
        }
        q = q->next;
      }
      if (key == 0)
        return 1;

      key = 0;
      p = p->next;
    }
  }
  return 0;
}


edge *PrimsMST(graph g, int n)
{
  if (n >= g.n)
  {
    printf("NODE NOT FOUND!\n\n");
    return NULL;
  }
  edge *edges = (edge *)malloc(sizeof(edge) * (g.n - 1)); // allocating space for the edges
  int *visited = (int *)calloc(g.n, sizeof(int));
  int minweight;
  visited[n] = 1;
  node *p = NULL;
  for (int i = 0; i < g.n - 1; i++)
  {
    minweight = INT_MAX;
    edge minedge;
    // comparing minimum weights between every node j and t
    for (int j = 0; j < g.n; j++)
    {
      p = g.A[j];
      if (visited[j] != 0) // if jth node is not visited
      {
        while (p)
        {
          int t = p->toNode;
          if (visited[t] == 0) // if tth node is not visited
          {
            if (p->weight < minweight) // if requirement of minweight satisfied, add it to the minweight array named edges
            {
              minweight = p->weight;
              minedge.start = j;
              minedge.dest = t;
              minedge.wt = minweight;
            }
          }
          p = p->next;
        }
      }
    }
    visited[minedge.dest] = 1;
    edges[i] = minedge; // adding entry to the minimum-weight edge
  }
  return edges;
}

// Dijkstra's algorithm

int min_distance(int *visited, int *cost, int n) // parsing through all the edges and returning the min_cost index
{
  int min_index;
  int min = INT_MAX;
  for (int i = 0; i < n - 1; i++) // observe the worst case going to O(n**2)
  {
    for (int j = 0; j < n; j++)
    {
      if (visited[j] == 0 && cost[j] < min)
      {
        min = cost[j];
        min_index = j;
      }
    }
  }
  return min_index;
}


void print_shortest_distance(int n, int *arr)
{
  printf("Vertex \t min_dist_from_source\n");
  for (int i = 0; i < n; i++)
    printf("%d \t\t %d\n", i, arr[i]);

  int total_weight = 0;
  for (int i = 0; i < n; i++)
    total_weight += arr[i];

  printf("The minimum cost to visit all the nodes using Dijkstra's algorithm is %d\n", total_weight);
  return;
}


void Dijkstra(graph g, int start)
{
  if (start >= g.n || start < 0)
  {
    printf("NODE NOT FOUND!\n\n");
    return;
  }

  int *visited = (int *)calloc(g.n, sizeof(int)); // keep track of whether a node is visited or not
  int *cost = (int *)calloc(g.n, sizeof(int));    // hold minimum cost path
  node *p = g.A[start];

  for (int i = 0; i < g.n; i++) // make all costs initially infinity
    cost[i] = INT_MAX;

  while (p)
  {
    int i = p->toNode;
    cost[i] = p->weight; // here, holds the 'weights of all directly reachable nodes from the start node'
    p = p->next;
  }

  visited[start] = 1; // self
  cost[start] = 0;    // self

  int u;
  for (int i = 0; i < g.n; i++)
  {
    u = min_distance(visited, cost, g.n); // u is the index of node to which min_distance from current node is found
    visited[u] = 1;
    node *p = NULL;
    p = g.A[u];
    while (p)
    {
      int j = p->toNode;
      if (visited[j] == 0 && (cost[u] + p->weight) < cost[j]) // relaxation step
      {
        cost[j] = cost[u] + p->weight;
      }
      p = p->next;
    }
  }

  print_shortest_distance(g.n, cost);
  return;
}

void driver(char *file)
{
  graph g;
  init_graph(&g, file);
  display_list(g);
  printf("\nBFS:\n");
  BFS(g, 4);
  printf("\nDFS:\n");
  DFS(g, 4);
  printf("Is graph directed : %d\n", is_directed(g));

  printf("Prim's algorithm\n");
  int i;
  printf("\nEnter the starting node : ");
  scanf("%d", &i);
  edge *arr = PrimsMST(g, i);
  if (arr == NULL)
    printf("NULL!\n\n");
  for (int i = 0; i < g.n - 1; i++)
  {
    printf("c(%d,%d) = %d ", arr[i].start, arr[i].dest, arr[i].wt);
    printf("\n");
  }
  fflush(stdin);

  int start;
  printf("Enter the starting node : ");
  scanf("%d", &start);
  printf("The shortest distances of the nodes from the node %d are as follows:\n\n", start);
  Dijkstra(g, start);
  printf("Matrix representation : \n");
  DisplayMatrix(g);
  return;
}