#include<stdio.h>
#include<stdlib.h>
# define MAX_VERTEX 10
#define STACK_SIZE 10
#define MAX_QUEUE_SIZE 11
typedef struct node
{
	int vertex;
	struct node* next;
}Node;
typedef struct
{
	int visit[MAX_VERTEX];
	Node* nearlist[MAX_VERTEX];
	int n;
}Graph;
void initilizeGraph(Graph** g);
void printGraph(Graph* g);
void insertvertex(Graph* g, int num);
void insertEdge(Graph* g, int v1, int v2);
void Print_Graph();
void freeGraph(Graph* g);
void DFS(Graph* g, int n);
void BFS(Graph* g, int n);

int Sempty();
int Sfull();
void push(int n);
int pop();
int stack[STACK_SIZE] = { 0, };
int top = -1;

int Qempty();
int Qfull();
int deQueue();
void enQueue(int item);
int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int main()
{
	char command;
    int ver_num = 0;
	int ver1, ver2;
	int ver;
	
	Graph* G=NULL;
	printf("[----- [�����] [2021041070] -----]\n");
	do {
		printf("\n----------------------------------------------------------------\n");
		printf("                        Graph  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph    = z                               \n");
		printf(" Insert  Vertex      = i         Insert Edge          = e \n");
		printf(" Depth First Search  = d         Breath First Search = b\n");
		printf(" Print Graph         = p         Quit                = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z': case 'Z':
			initilizeGraph(&G);
			break;
		case 'i': case 'I':
			printf("vertex : ");
			scanf(" %d", &ver_num);
			insertvertex(G, ver_num);
			break;
		case 'b': case 'B':
			printf("Start number : ");
			scanf(" %d", &ver);
			BFS(G, ver);
			break;
		case 'e': case 'E':
			printf("vertices (x, y) ");
			scanf(" %d", &ver1);
			scanf(" %d", &ver2);
			insertEdge(G, ver1, ver2);
			insertEdge(G, ver2, ver1);
			break;
		case 'd': case 'D':
			printf("Start number = ");
			scanf(" %d", &ver);
			DFS(G, ver);
			break;
		case 'p': case 'P':
			Print_Graph(G);
			break;
        case 'q': case 'Q':
            freeGraph(G);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');
	return 1;
}


void initilizeGraph(Graph** g)//�ʱ�ȭ �Լ�, ���� ������ �ʱ�ȭ �����־�� �ϹǷ� ���������ͷ� �޴´�
{
	 if (*g != NULL)//�׷����� �����ҽ�
    	 freeGraph(*g); //���� 
	*g = (Graph*)malloc(sizeof(Graph));
	(*g)->n = 0;//vertex ���� 0
	for (int n = 0; n < MAX_VERTEX; n++)//��������Ʈ NULL�ʱ�ȭ
	{
		(*g)->nearlist[n] = NULL;
	}

}

void insertvertex(Graph* g, int num)//vertex�� ������ ���ϴ� �Լ�
{
	for (int i = 0; i < num; i++)
	{
		if (g->n >= MAX_VERTEX)//������ �� �ִ� vertex�� ���� �ʰ��� ��
		{
			printf("���� �ʰ�\n");
			return;
		}
		g->n++;//vertex���� �Ѱ��� �ø���
	}
	printf(" %d�� vertex �����Ϸ�\n", g->n);
}

void insertEdge(Graph* g, int v1, int v2)
{
	Node* vertexnode;
	Node* sort;//��������Ʈ�� ������������ �����ϱ� ���� ����
	sort = g->nearlist[v1];//������ ù ��° ��带 ����Ű�� ���� ����
	if (v1 >= g->n || v2 >= g->n)// ������ ������ 
	{
		printf("\n�ش� ������ ����X\n");
		return;
	}
	vertexnode = (Node*)malloc(sizeof(Node));
	vertexnode->vertex = v2;

	if (sort != NULL)// ��������Ʈ�� ��尡 �����Ҷ� 
	{
		if (sort->vertex >= vertexnode->vertex) //��������Ʈ ù��°��尡 �߰��Ϸ��� vertex���� Ŭ��
		{
			vertexnode->next = g->nearlist[v1]; //vertexnode�� ������带 ���� ù��° ���� ���� ����
			g->nearlist[v1] = vertexnode;//ù��° ���� ��带 vertexnode�� ����
			return;
		}
		else//��������Ʈ ù��°��尡 �߰��Ϸ��� vertex���� ������
		{
			while (sort->next != NULL)//sort ������ �ݺ�
			{
				if (sort->next->vertex >= vertexnode->vertex)//���� sort����� �� ����� vertex���� ���������ϴ� vertex������ ũ�ų� ���ٸ�
				{
					vertexnode->next = sort->next;
					sort->next = vertexnode;
					return;
				}
				sort = sort->next; //sort ��带 �������� �̵�
			}

			sort->next = vertexnode;//vertex��带 �Ǹ������� �����Ѵ�
			vertexnode->next = NULL;
			return;
		}
	}

	else//��������Ʈ�� ���������
	{
		vertexnode->next = g->nearlist[v1];
		g->nearlist[v1] = vertexnode;
	}

	return;
}

void BFS(Graph* g, int n)//�ʺ� �켱 Ž��
{
	Node* p;
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		g->visit[i] = 0;         //�湮�� vertex �迭 ��� 0���� �ʱ�ȭ
	}
	printf("%3d", n); 
	g->visit[n] = 1;//���� vertex�� �湮�� ����ϱ����� 1�� ����   
	enQueue(n); //ť�� ����vertex ����
	while (Qempty() != 1) { // ť�� ��������
		n = deQueue(); // ť���� ������
		for (p = g->nearlist[n]; p; p = p->next)//�� ������ �پ��ִ� ������ NULL���� ���ö����� �̵��ϸ鼭 �ݺ��Ѵ�
		{
			if (!g->visit[p->vertex])//�湮�ߴ� ��尡 �ƴ϶��
			{
				printf("%3d", p->vertex);//�ش�vertex���
				enQueue(p->vertex);//ť�� �߰��Ѵ�
				g->visit[p->vertex] = 1;//�湮 ����� ���� 1�� ����
			}
		}
	}
}

void DFS(Graph* g, int n)//���̿켱Ž��
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		g->visit[i] = 0;  //�湮�� vertex �迭 ��� 0���� �ʱ�ȭ
	}


	Node* p;
	push(n);//ù ������ �ι� �־� ���ÿ� �����ִ� ���¸� ���������ش�
	push(n);
	g->visit[n] = 1;   //ù �湮 ��� 1�� �ʱ�ȭ
	printf("%3d", n);


	while (Sempty() != 1) //������ ��������
	{

		n = pop();// ���ÿ��� ������
		p = g->nearlist[n];//vertex������ ������带 p�� ����      

		while (p)//p�� 0�϶�����
		{
			if (g->visit[p->vertex] == 0) //��带 �湮�� �� ������
			{
				n = p->vertex;//n�� ���� �������
				push(n);//n�� ���ÿ� ����  
				g->visit[n] = 1;//�湮�����Ƿ� 1�� ���� 
				printf("%3d", n); 
				p = g->nearlist[n];//���� vertex�� ���� �������� p�� ����
			}
			else//��尡 �湮�� �� ���� ��
			{

				p = p->next; //���� ���� �������� �ٲ��ش�
			}
		}
	}
}

int Sempty() 
{
	if (top == -1) {  // ������ ��á�ٸ�
		return 1;
	}
	return 0;
}


int Sfull() 
{
	if (top >= STACK_SIZE - 1) {    // ������ ����ٸ� 
		return 1;
	}
	return 0;
}

void push(int n) // ���ÿ� ����
{
	if (Sfull() == 1) {
		printf("STACK full\n");
		return;
	}
	stack[++top] = n;
}

int pop() { // ���ÿ��� ������
	if (Sempty() == 1) {
		return 0;
	}
	return stack[top--];
}


int Qempty() {
	if (front == rear) {  // ť�� ��������� front�� rear�� �����ϹǷ�
		printf("\nQueue empty\n");
		return 1;
	}
	return 0;
}

int Qfull() { 
	if ((rear + 1) % MAX_QUEUE_SIZE == front) { //rear+1�� front�� �ִ��� Ȯ��
		printf("Queue full\n");
		return 1;
	}
	return 0;
}
void enQueue(int item)
{
	if (Qfull()) //ť�� ��á�������� Ȯ��
	{      
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE; //���� rear���� ��ĭ ����
		// ����ť�̱� ������ ť ������� ũ�� �ٽ� ó������ ���Ұ� ���ԵǾ����. �׷��Ƿ� ť ������� ������ ����
	queue[rear] = item;
}

int deQueue() //ť���� front�� ���� ��ȯ �ϴ� �Լ�
{
	int item = 0;
	if (Qempty()) {   //ť�� ����ִ������� Ȯ��
		return 1;
	}
	front = (front + 1) % MAX_QUEUE_SIZE; // // front�� ��ĭ �������� �� ���Ҹ� ����
	item = queue[front];
	return item;


}

void Print_Graph(Graph* g)
{
	Node* p;//��带 ���� �����ͺ���
	for (int i = 0; i < g->n; i++)//vertex ���� ��ŭ �ݺ�
	{
		printf("adjlist of vertex %d: ", i);
		p = g->nearlist[i];//�ش� vertex�� ������� p�� ����
		while (p != NULL) {  //�ش� vertex�� ������� NULL���� ���ö����� �ݺ�
			printf(", %3d", p->vertex);
			p = p->next;   //���� ���� �̵�
		}
		printf("\n");
	}
}

void freeGraph(Graph* g)//�����Ҵ� ���� �Լ�
{
	Node* cur, * next;//������� ������� ���� 
	for (int i = 0; i < g->n; ++i)//vertex ����ŭ �ݺ�
	{
		cur = g->nearlist[i];//ù ��° vertex ������带 cur�� ����
		while (cur != NULL)//cur= NULL�� �ɶ����� �ݺ�
		{
			next = cur->next;// next�� ������带 ����
			free(cur);//������ �����Ҵ� ����
			cur = next;//������带 ������� �����Ѵ�
		}
	}
	free(g); 
}

