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
	printf("[----- [김민재] [2021041070] -----]\n");
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


void initilizeGraph(Graph** g)//초기화 함수, 직접 내용을 초기화 시켜주어야 하므로 이중포인터로 받는다
{
	 if (*g != NULL)//그래프가 존재할시
    	 freeGraph(*g); //해제 
	*g = (Graph*)malloc(sizeof(Graph));
	(*g)->n = 0;//vertex 갯수 0
	for (int n = 0; n < MAX_VERTEX; n++)//인접리스트 NULL초기화
	{
		(*g)->nearlist[n] = NULL;
	}

}

void insertvertex(Graph* g, int num)//vertex의 갯수를 정하는 함수
{
	for (int i = 0; i < num; i++)
	{
		if (g->n >= MAX_VERTEX)//설정할 수 있는 vertex의 수를 초과할 때
		{
			printf("개수 초과\n");
			return;
		}
		g->n++;//vertex갯수 한개를 늘린다
	}
	printf(" %d개 vertex 생성완료\n", g->n);
}

void insertEdge(Graph* g, int v1, int v2)
{
	Node* vertexnode;
	Node* sort;//인접리스트를 오름차순으로 정렬하기 위한 변수
	sort = g->nearlist[v1];//정점의 첫 번째 노드를 가리키는 값을 대입
	if (v1 >= g->n || v2 >= g->n)// 정점이 없을때 
	{
		printf("\n해당 정점이 존재X\n");
		return;
	}
	vertexnode = (Node*)malloc(sizeof(Node));
	vertexnode->vertex = v2;

	if (sort != NULL)// 인접리스트에 노드가 존재할때 
	{
		if (sort->vertex >= vertexnode->vertex) //인접리스트 첫번째노드가 추가하려는 vertex보다 클때
		{
			vertexnode->next = g->nearlist[v1]; //vertexnode의 다음노드를 원래 첫번째 인접 노드로 지정
			g->nearlist[v1] = vertexnode;//첫번째 인접 노드를 vertexnode로 지정
			return;
		}
		else//인접리스트 첫번째노드가 추가하려는 vertex보다 작을때
		{
			while (sort->next != NULL)//sort 끝까지 반복
			{
				if (sort->next->vertex >= vertexnode->vertex)//현재 sort노드의 옆 노드의 vertex값이 넣으려고하는 vertex값보다 크거나 같다면
				{
					vertexnode->next = sort->next;
					sort->next = vertexnode;
					return;
				}
				sort = sort->next; //sort 노드를 다음으로 이동
			}

			sort->next = vertexnode;//vertex노드를 맨마지막에 삽입한다
			vertexnode->next = NULL;
			return;
		}
	}

	else//인접리스트가 비어있을때
	{
		vertexnode->next = g->nearlist[v1];
		g->nearlist[v1] = vertexnode;
	}

	return;
}

void BFS(Graph* g, int n)//너비 우선 탐색
{
	Node* p;
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		g->visit[i] = 0;         //방문한 vertex 배열 모두 0으로 초기화
	}
	printf("%3d", n); 
	g->visit[n] = 1;//시작 vertex의 방문을 기록하기위해 1로 변경   
	enQueue(n); //큐에 시작vertex 삽입
	while (Qempty() != 1) { // 큐가 빌때까지
		n = deQueue(); // 큐에서 가져옴
		for (p = g->nearlist[n]; p; p = p->next)//한 정점에 붙어있는 노드들을 NULL값이 나올때까지 이동하면서 반복한다
		{
			if (!g->visit[p->vertex])//방문했던 노드가 아니라면
			{
				printf("%3d", p->vertex);//해당vertex출력
				enQueue(p->vertex);//큐에 추가한다
				g->visit[p->vertex] = 1;//방문 기록을 위해 1로 변경
			}
		}
	}
}

void DFS(Graph* g, int n)//깊이우선탐색
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		g->visit[i] = 0;  //방문한 vertex 배열 모두 0으로 초기화
	}


	Node* p;
	push(n);//첫 정점은 두번 넣어 스택에 남아있는 상태를 유지시켜준다
	push(n);
	g->visit[n] = 1;   //첫 방문 노드 1로 초기화
	printf("%3d", n);


	while (Sempty() != 1) //스택이 빌때까지
	{

		n = pop();// 스택에서 가져옴
		p = g->nearlist[n];//vertex정점의 인접노드를 p에 대입      

		while (p)//p가 0일때까지
		{
			if (g->visit[p->vertex] == 0) //노드를 방문한 적 없으면
			{
				n = p->vertex;//n은 현재 인접노드
				push(n);//n을 스택에 삽입  
				g->visit[n] = 1;//방문했으므로 1로 변경 
				printf("%3d", n); 
				p = g->nearlist[n];//현재 vertex에 대한 인접노드로 p를 지정
			}
			else//노드가 방문한 적 있을 때
			{

				p = p->next; //다음 인접 정점으로 바꿔준다
			}
		}
	}
}

int Sempty() 
{
	if (top == -1) {  // 스택이 꽉찼다면
		return 1;
	}
	return 0;
}


int Sfull() 
{
	if (top >= STACK_SIZE - 1) {    // 스택이 비었다면 
		return 1;
	}
	return 0;
}

void push(int n) // 스택에 삽입
{
	if (Sfull() == 1) {
		printf("STACK full\n");
		return;
	}
	stack[++top] = n;
}

int pop() { // 스택에서 가져옴
	if (Sempty() == 1) {
		return 0;
	}
	return stack[top--];
}


int Qempty() {
	if (front == rear) {  // 큐가 비어있을때 front와 rear은 동일하므로
		printf("\nQueue empty\n");
		return 1;
	}
	return 0;
}

int Qfull() { 
	if ((rear + 1) % MAX_QUEUE_SIZE == front) { //rear+1이 front에 있는지 확인
		printf("Queue full\n");
		return 1;
	}
	return 0;
}
void enQueue(int item)
{
	if (Qfull()) //큐가 꽉찼는지부터 확인
	{      
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE; //현재 rear에서 한칸 증가
		// 원형큐이기 때문에 큐 사이즈보다 크면 다시 처음부터 원소가 삽입되어야함. 그러므로 큐 사이즈로 나머지 연산
	queue[rear] = item;
}

int deQueue() //큐에서 front의 값을 반환 하는 함수
{
	int item = 0;
	if (Qempty()) {   //큐가 비어있는지부터 확인
		return 1;
	}
	front = (front + 1) % MAX_QUEUE_SIZE; // // front를 한칸 증가시켜 그 원소를 빼옴
	item = queue[front];
	return item;


}

void Print_Graph(Graph* g)
{
	Node* p;//노드를 담을 포인터변수
	for (int i = 0; i < g->n; i++)//vertex 갯수 만큼 반복
	{
		printf("adjlist of vertex %d: ", i);
		p = g->nearlist[i];//해당 vertex의 인접노드 p에 대입
		while (p != NULL) {  //해당 vertex에 인접노드 NULL값이 나올때까지 반복
			printf(", %3d", p->vertex);
			p = p->next;   //다음 노드로 이동
		}
		printf("\n");
	}
}

void freeGraph(Graph* g)//동적할당 해제 함수
{
	Node* cur, * next;//현재노드랑 다음노드 변수 
	for (int i = 0; i < g->n; ++i)//vertex 수만큼 반복
	{
		cur = g->nearlist[i];//첫 번째 vertex 인접노드를 cur에 넣음
		while (cur != NULL)//cur= NULL이 될때까지 반복
		{
			next = cur->next;// next에 다음노드를 넣음
			free(cur);//현재노드 동적할당 해제
			cur = next;//다음노드를 현재노드로 지정한다
		}
	}
	free(g); 
}

