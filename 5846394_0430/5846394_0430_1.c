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
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int main(void) {
	QueueType queue;
	int choice, element;

	init_queue(&queue);

	while (1) {
		printf("1. ť�� ���Ҹ� ����\n");
		printf("2. ť���� ���Ҹ� ����\n");
		printf("3. ť�� ���Ҹ� ���\n");
		printf("4. ����\n");
		printf("�޴��� �����ϼ���: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("������ �Է��Ͻÿ�: ");
			scanf("%d", &element);
			enqueue(&queue, element);
			queue_print(&queue);
			break;
		case 2:
			if (!is_empty(&queue)) {
				element = dequeue(&queue);
				printf("������ ����: %d\n", element);
				queue_print(&queue);
			}
			else {
				printf("ť�� ��������Դϴ�.\n");
			}
			break;
		case 3:
			queue_print(&queue);
			break;
		case 4:
			return 0;
		default:
			printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���.\n");
		}
	}
	return 0;
}