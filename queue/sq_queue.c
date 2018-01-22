#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 20

struct sq_queue {
	int *base;
	int front;
	int rear;
};

struct sq_queue* init_sq_queue(void)
{
	struct sq_queue *queue = NULL;
	
	queue = (struct sq_queue*)malloc(sizeof(struct sq_queue));
	if (!queue) {
		printf("malloc memory space failed for sq_queue\n");
		return NULL;
	}
	
	queue->base = (int *)malloc(sizeof(int) * MAX_QUEUE_SIZE);
	queue->front = queue->rear = 0;

	return queue;
}

int queue_is_full(struct sq_queue *queue)
{
	int ret = 0;
	if (((queue->rear + 1) % MAX_QUEUE_SIZE) == queue->front) {
		ret = 1;
		return ret;
	}
	return ret;
}

int queue_is_empty(struct sq_queue *queue)
{
	int ret = 0;
	if (queue->rear == queue->front) {
		ret = 1;
		return ret;
	}
	return ret;
}

int enqueue(struct sq_queue *queue, int data)
{
	int ret = 0;

	if (queue_is_full(queue)) {
		printf("The queue_is_full,can not inserted\n");
		ret = -1;
		return ret;
	}

	queue->base[queue->rear] = data;
	queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	printf("rear = %d\n", queue->rear);
	return ret;
}

int dequeue(struct sq_queue *queue, int *data)
{
	int ret = 0;

	if (queue_is_empty(queue)) {
		printf("The queue_is_empty,no data\n");
		ret = -1;
		return ret;
	}

	*data = queue->base[queue->front];
	printf("dequeue data:%d\n", *data);
	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
	return ret;
}

void dump_queue(struct sq_queue *queue)
{
	int tmp_front, tmp_rear;

	tmp_front = queue->front;
	tmp_rear = queue->rear;
	while(tmp_front != tmp_rear) {
		printf("queue[%d] = %d\n", tmp_front, queue->base[tmp_front]);
		tmp_front = (tmp_front + 1) % MAX_QUEUE_SIZE;
	}
}
int create_sq_queue(struct sq_queue *queue)
{
	int ret = 0, i;

	for (i = 0; i < 15; i++) {
		enqueue(queue, i);	
	}

	return ret;

}

int main(int argc, const char *argv[])
{
	struct sq_queue *sq_queue = NULL;
	int data;

	sq_queue = init_sq_queue();
	printf("***************** create queue ************************\n");
	create_sq_queue(sq_queue);
	dump_queue(sq_queue);
	printf("\n");

	printf("***************** entry queue ************************\n");
	enqueue(sq_queue, 100);
	enqueue(sq_queue, 156);
	enqueue(sq_queue, 146);
	dump_queue(sq_queue);
	printf("\n");

	printf("***************** delete queue ************************\n");
	dequeue(sq_queue, &data);
	dequeue(sq_queue, &data);
	dump_queue(sq_queue);

	free(sq_queue->base);
	free(sq_queue);
	return 0;
}
