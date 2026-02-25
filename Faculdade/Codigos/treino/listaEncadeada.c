#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int n;
	struct Node* next;
}Node;

typedef struct List
{
	Node* primeiro;
	Node* ultimo;
}List;

Node* newNode(int number);
List* newList();
void inserirInicio(int number, List* list);
void inserirFim(int number, List* list);
void mostrar(List* list);


int main()
{
	List* list1 = newList();
	

	inserirInicio(8, list1);
	inserirInicio(5, list1);
	inserirInicio(4, list1);
	inserirInicio(1, list1);
	inserirFim(7, list1);
	inserirFim(9, list1);
	mostrar(list1);

	
}

Node* newNode(int number)
{
	Node* temp = (Node*) malloc(sizeof(Node));
	temp->next = NULL;
	temp->n = number;
	return temp;
}

List* newList()
{
	List* temp = (List*) malloc(sizeof(List));
	temp->primeiro = (Node*) malloc(sizeof(Node));
	temp->ultimo = temp->primeiro;
	return temp;
}

void inserirInicio(int number, List* list)
{
	Node* temp = newNode(number);
	if(list->primeiro == list->ultimo)
	{
		list->primeiro->next = temp;
		list->ultimo = temp;
		temp = NULL;
	}
	else
	{
		temp->next = list->primeiro->next;
		list->primeiro->next = temp;
		temp = NULL;
	}
	
}

void inserirFim(int number, List* list)
{
	Node* temp = newNode(number);
	list->ultimo->next = temp;
	list->ultimo = temp;
	temp = NULL;
}

void mostrar(List* list)
{
	Node* ptr = NULL;
	for (ptr = list->primeiro->next; ptr != NULL; ptr = ptr->next)
	{
		printf("%d ", ptr->n);
	}
	printf("\n");
}
















