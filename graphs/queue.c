#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"


void init_queue(queue *q, int size)
{
  q->A = (int *)malloc(sizeof(int) * size);
  q->size = size;
  q->front = q->rear = -1;
  return;
}


int is_queue_full(queue q)
{

  if ( (q.front == 0 && q.rear == q.size - 1) || (q.front == q.rear +1) )
    return 1;

  return 0;
}


int is_queue_empty(queue q)
{
  if (q.front == -1)
    return 1;

  return 0;
}

void enqueue(queue *q, int n)
{
  if (is_queue_full(*q))
  {
    return;
  }
  if (q->front == -1)
    q->front++;
  q->rear = (q->rear + 1) % q->size;
  q->A[q->rear] = n;
  
  return;  
}


int dequeue(queue *q)
{
  int x = INT_MIN;
  if (is_queue_empty(*q))
  {
    return x;
  }

  x = q->A[q->front];
  if (q->front == q->rear)
  {
    q->front = q->rear = -1;
    return x;
  }
  q->front = (q->front + 1) % q->size;
  return x;
  
}