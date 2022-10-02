typedef struct queue{
  int *A;
  int front, rear, size;
} queue;


void init_queue(queue *, int);
void enqueue(queue *, int );
int dequeue(queue *);
int is_queue_empty(queue);
int is_queue_full(queue);


