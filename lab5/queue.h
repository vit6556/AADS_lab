#ifndef QUEUE_H
#define QUEUE_H

Queue* createQueue(unsigned capacity);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);
#endif