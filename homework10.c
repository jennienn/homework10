/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;               // 노드의 키 값
	struct node *left;     // 왼쪽 서브트리 루트 노드의 포인터
	struct node *right;    // 오른쪽 서브트리 루트 노드의 포인터
} Node;

/* 스택을 위한 변수들 */
#define MAX_STACK_SIZE	20
Node* stack[MAX_STACK_SIZE];
int top = -1;

/* 큐를 위한 변수들 */
#define MAX_QUEUE_SIZE	20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1; 


int initializeBST(Node** h);           /* 이진 탐색 트리를 초기화 하는 함수 */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();                           // 스택에서 노드를 팝하는 함수
void push(Node* aNode);                // 스택에 노드를 푸시하는 함수
Node* deQueue();                    // 큐에서 노드를 디큐하는 함수
void enQueue(Node* aNode);          // 큐에 노드를 인큐하는 함수

/* you may add your own defined functions if necessary */


void printStack(); // 출력하는 함수


int main()
{
	char command; /* 입력받은 명령어를 저장하는 변수 */
	int key; /* 입력받은 키 값을 저장하는 변수 */
	Node* head = NULL;

    printf("[----- [김예진]  [2022041035] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {
    /* 만약 트리가 비어있지 않다면, 트리에서 할당된 모든 노드를 제거 */
    if (*h != NULL)
        freeBST(*h);

    /* 헤드 노드를 생성 */
    *h = (Node*)malloc(sizeof(Node));

    // 헤드 노드의 초기 설정
    (*h)->left = NULL;  // 루트 노드는 아직 삽입되지 않았으므로 NULL로 설정
    (*h)->right = *h;  // 헤드 노드의 오른쪽 자식은 자기 자신을 가리킨다
    (*h)->key = -9999; // 헤드 노드의 키 값을 -9999로 설. 실제 키 값이 아닌 헤드 노드임을 나타내는 임의의 값

    top = -1;   // 스택의 top을 -1로 초기화

    front = rear = -1;  // 큐의 front와 rear를 -1로 초기화

    return 1;
}


void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);    // 현재 노드의 왼쪽 서브트리를 재귀적으로 중위 순회
		printf(" [%d] ", ptr->key);    // 현재 노드의 키를 출력
		recursiveInorder(ptr->right);   // 현재 노드의 오른쪽 서브트리를 재귀적으로 중위 순회
	}
}


/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
    for (;;)
    {
        // 왼쪽 자식 노드들을 스택에 push하면서 가장 왼쪽 노드로 이동
        for (; node; node = node->left)
            push(node);
        
        // 스택에서 노드를 pop하여 방문하고, 오른쪽 자식 노드로 이동
        node = pop();

        if (!node) break; // 노드가 NULL이면 종료

        printf(" [%d] ", node->key); // 노드의 값을 출력

        node = node->right; // 오른쪽 자식 노드로 이동
    }
}


/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(!ptr) return; /* 트리가 비어있는 경우 */

	enQueue(ptr); /* 루트 노드를 큐에 삽입 */

	for(;;)
	{
		ptr = deQueue(); /* 큐에서 노드를 하나 꺼냄 */
		if(ptr) {
			printf(" [%d] ", ptr->key); /* 노드의 키 값을 출력 */

			if(ptr->left)
				enQueue(ptr->left); /* 왼쪽 자식 노드를 큐에 삽입 */
			if(ptr->right)
				enQueue(ptr->right); /* 오른쪽 자식 노드를 큐에 삽입 */
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	// 새로운 노드 생성
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		// 트리가 비어있는 경우 새로운 노드를 루트로 설정
		head->left = newNode;
		return 1;
	}

	// head->left가 루트 노드
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		// 동일한 키를 가진 노드가 이미 있는 경우
		if(ptr->key == key) return 1;

		// 자식 노드로 이동해야 함
		// 부모 노드를 parentNode로 추적하여 유지
		parentNode = ptr;

		// 현재 노드의 키와 입력된 키를 비교하여
		// 작으면 왼쪽 서브트리로 이동하고, 크면 오른쪽 서브트리로 이동
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	// 새로운 노드를 부모 노드와 연결
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteNode(Node* head, int key)
{
    if (head == NULL) {
        printf("\n Nothing to delete!!\n");
        return -1;
    }

    if (head->left == NULL) {
        printf("\n Nothing to delete!!\n");
        return -1;
    }

    // head->left는 루트를 가리킴
    Node* root = head->left;

    Node* parent = NULL;
    Node* ptr = root;

    // 삭제할 노드를 찾기 위해 트리를 탐색
    while ((ptr != NULL) && (ptr->key != key)) {
        if (ptr->key != key) {
            parent = ptr;    // 부모 노드를 저장

            // 현재 노드의 키와 찾는 키를 비교하여 이동 방향 결정
            if (ptr->key > key)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
    }

    // 삭제할 노드가 없는 경우
    if (ptr == NULL) {
        printf("No node for key [%d]\n ", key);
        return -1;
    }

    // case 1: 삭제할 노드가 리프 노드인 경우
    if (ptr->left == NULL && ptr->right == NULL) {
        if (parent != NULL) {
            // 부모 노드의 왼쪽 또는 오른쪽 링크를 NULL로 조정
            if (parent->left == ptr)
                parent->left = NULL;
            else
                parent->right = NULL;
        } else {
            // 부모가 없는 경우, 즉 삭제할 노드가 루트인 경우
            head->left = NULL;
        }

        free(ptr);  // 노드 메모리 해제
        return 1;
    }

    // case 2: 삭제할 노드가 한 개의 자식을 가지는 경우
    if (ptr->left == NULL || ptr->right == NULL) {
        Node* child;
        if (ptr->left != NULL)
            child = ptr->left;
        else
            child = ptr->right;

        if (parent != NULL) {
            // 부모 노드와 연결을 수정하여 자식 노드를 대체
            if (parent->left == ptr)
                parent->left = child;
            else
                parent->right = child;
        } else {
            // 부모가 없는 경우, 즉 삭제할 노드가 루트이고 자식이 하나인 경우
            root = child;  // 자식 노드를 새로운 루트로 설정
        }

        free(ptr);  // 노드 메모리 해제
        return 1;
    }

    // case 3: 삭제할 노드가 두 개의 자식을 가지는 경우
    Node* candidate;
    parent = ptr;

    candidate = ptr->right;

    // 가장 작은 키를 가진 노드를 오른쪽 서브트리에서 찾음
    while (candidate->left != NULL) {
        parent = candidate;
        candidate = candidate->left;
    }

    // candidate는 삭제될 오른쪽 서브트리의 가장 왼쪽에 있는 노드
    if (parent->right == candidate)
        parent->right = candidate->right;
    else
        parent->left = candidate->right;

    // ptr의 키를 candidate의 키로 대체하고 candidate 노드를 삭제함
    ptr->key = candidate->key;

    free(candidate);  // 노드 메모리 해제
    return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);  // 왼쪽 자식 노드 해제
		freeNode(ptr->right); // 오른쪽 자식 노드 해제
		free(ptr);            // 노드 메모리 해제
	}
}

int freeBST(Node* head)
{
	if(head->left == head)
	{
		free(head); // 헤드 노드 메모리 해제
		return 1;
	}

	Node* p = head->left;

	freeNode(p); // 모든 노드 메모리 해제

	free(head); // 헤드 노드 메모리 해제
	return 1;
}

Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--]; // 스택의 가장 위에 있는 노드를 반환하고, 스택에서 제거
}

void push(Node* aNode)
{
	stack[++top] = aNode; // 스택에 노드를 추가
}

void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); // 스택의 요소를 출력
	}
}

Node* deQueue()
{
	if (front == rear) {
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front]; // 큐의 가장 앞에 있는 노드를 반환하고, 큐에서 제거
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // 큐에 노드를 추가
}
