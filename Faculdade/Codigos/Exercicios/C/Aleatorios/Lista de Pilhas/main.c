#include <stdio.h>
#include <stdlib.h>

typedef struct NoPilha
{
	struct NoPilha* prox;
	int valor;
}NoPilha;

typedef struct Pilha
{
	NoPilha* topo;
}Pilha;

typedef struct NoLista
{
	struct NoLista* prox;
	Pilha* p;
}NoLista;

typedef struct Lista
{
	NoLista* primeiro;
	NoLista* ultimo;
}Lista;

Pilha* criarPilha()
{
	Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
	pilha->topo = (NoPilha*) malloc(sizeof(NoPilha));
	pilha->topo->prox = NULL;
	return pilha;
}

void push(Pilha* pilha, int valor)
{
	NoPilha* temp = (NoPilha*) malloc(sizeof(NoPilha));
	temp->valor = valor;
	temp->prox = pilha->topo->prox;
	pilha->topo->prox = temp;
	temp = NULL;
}

void imprimirPilha(Pilha* pilha)
{
	NoPilha* i = pilha->topo->prox;
	
	while(i != NULL)
	{
		printf("%d ", i->valor);
		i = i->prox;
	}
	printf("NULL\n");
}

Lista* criarLista()
{
	Lista* lista = (Lista*) malloc(sizeof(Lista));
	NoLista* cabeca = (NoLista*) malloc(sizeof(NoLista));
	cabeca->prox = NULL;
	cabeca->p = NULL;
	lista->primeiro = cabeca;
	lista->ultimo = cabeca;
	
	return lista;
}

void inserirPilhaNoFim(Lista* lista)
{
	NoLista* temp = (NoLista*) malloc (sizeof(NoLista));
	temp->prox = NULL;
	temp->p = criarPilha();
	
	lista->ultimo->prox = temp;
	
	lista->ultimo = temp;
}

int main()
{
    // 1. Cria a sua lista principal
    Lista* minhaLista = criarLista();
    
    // 2. Vamos adicionar 3 nós na lista. Cada um terá sua própria pilha.
    inserirPilhaNoFim(minhaLista); // 1º nó (com a 1ª pilha)
    inserirPilhaNoFim(minhaLista); // 2º nó (com a 2ª pilha)
    inserirPilhaNoFim(minhaLista); // 3º nó (com a 3ª pilha)

    // 3. Agora, vamos acessar essas pilhas e adicionar dados
    
    // Acessando a PRIMEIRA pilha
    // (Lembre-se de pular o nó cabeça!)
    NoLista* primeiroNo = minhaLista->primeiro->prox;
    if (primeiroNo != NULL)
    {
        printf("Populando Pilha 1:\n");
        push(primeiroNo->p, 10);
        push(primeiroNo->p, 20);
        imprimirPilha(primeiroNo->p);
    }
    
    // Acessando a SEGUNDA pilha
    NoLista* segundoNo = primeiroNo->prox;
    if (segundoNo != NULL)
    {
        printf("\nPopulando Pilha 2:\n");
        push(segundoNo->p, 99);
        imprimirPilha(segundoNo->p);
    }

    // Acessando a TERCEIRA pilha
    NoLista* terceiroNo = segundoNo->prox;
    if (terceiroNo != NULL)
    {
        printf("\nPopulando Pilha 3:\n");
        push(terceiroNo->p, 500);
        push(terceiroNo->p, 600);
        push(terceiroNo->p, 700);
        imprimirPilha(terceiroNo->p);
    }

    /*
    Saída esperada:
    
    Populando Pilha 1:
    (Topo) -> 20 -> 10 -> NULL
    
    Populando Pilha 2:
    (Topo) -> 99 -> NULL
    
    Populando Pilha 3:
    (Topo) -> 700 -> 600 -> 500 -> NULL
    */
    
    // Não se esqueça de implementar a função 'free()' 
    // para liberar toda essa memória (que seria complexa!)

    return 0;
}
























