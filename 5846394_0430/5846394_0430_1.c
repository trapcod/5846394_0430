#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q) {
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int main(void) {
	QueueType queue;
	int choice, element;

	init_queue(&queue);

	while (1) {
		printf("1. 큐에 원소를 삽입\n");
		printf("2. 큐에서 원소를 삭제\n");
		printf("3. 큐의 원소를 출력\n");
		printf("4. 종료\n");
		printf("메뉴를 선택하세요: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("정수를 입력하시오: ");
			scanf("%d", &element);
			enqueue(&queue, element);
			queue_print(&queue);
			break;
		case 2:
			if (!is_empty(&queue)) {
				element = dequeue(&queue);
				printf("삭제된 원소: %d\n", element);
				queue_print(&queue);
			}
			else {
				printf("큐가 공백상태입니다.\n");
			}
			break;
		case 3:
			queue_print(&queue);
			break;
		case 4:
			return 0;
		default:
			printf("잘못된 선택입니다. 다시 입력해주세요.\n");
		}
	}
	return 0;
}