/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 04 - Q2 - Árvore Bicolor (Red-Black Tree) em C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TIPOS 10
#define MAX_STR 200
#define MAX_TIPO_STR 50
#define MAX_BUFFER 2048

typedef struct
{
    int hora;
    int minuto;
} Hora;

typedef struct
{
    int ano;
    int mes;
    int dia;
} Data;

typedef struct
{
    int id;
    char nome[MAX_STR];
    char cidade[MAX_STR];
    int capacidade;
    double avaliacao;
    char tipos_cozinha[MAX_TIPOS][MAX_TIPO_STR];
    int n_tipos_cozinha;
    int faixa_preco;
    Hora horario_abertura;
    Hora horario_fechamento;
    Data data_abertura;
    int aberto;
} Restaurante;

typedef struct { int tamanho; Restaurante** restaurantes; } Colecao_Restaurantes;

Hora parse_hora(char s[]);
void formatar_hora(Hora* hora, char buffer[]);
Data parse_data(char s[]);
void formatar_data(Data* data, char buffer[]);
void string_to_array(char s[], char tipos[][MAX_TIPO_STR], int* n);
Restaurante* parse_restaurante(char s[]);
void formatar_restaurante(Restaurante* r, char buffer[]);
void ler_csv_colecao(Colecao_Restaurantes* c, char path[]);
Colecao_Restaurantes* ler_csv();
Restaurante* get_restaurante_by_id(Colecao_Restaurantes* c, int id);
void free_restaurante(Restaurante* r);
void free_colecao(Colecao_Restaurantes* c);
void gerar_log(char matricula[], char algoritmo[], int comparacoes, long tempo);

/*---- Árvore Bicolor ----*/

typedef enum { RED, BLACK } Cor;

typedef struct No
{
    Restaurante* restaurante;
    struct No* esq;
    struct No* dir;
    struct No* pai;
    Cor cor;
} No;

No* NIL_NO;
No* raiz;

No* novo_no(Restaurante* r);
void iniciar();
void rotacao_esquerda(No* x);
void rotacao_direita(No* y);
void inserir_fixup(No* z);
void inserir(Restaurante* r);
int pesquisar_rec(char nome[], No* i, int* comparacoes);
void pesquisar(char nome[], int* comparacoes);
void caminhar_central(No* i);
void liberar_arvore(No* i);

/*---- Main ----*/

int main()
{
    Colecao_Restaurantes* c = ler_csv();
    iniciar();

    int id;
    while(scanf("%d", &id) == 1 && id != -1)
    {
        Restaurante* r = get_restaurante_by_id(c, id);
        if(r) inserir(r);
    }

    int comparacoes = 0;
    clock_t inicio = clock();

    char nome[MAX_STR];
    while(scanf(" %[^\n]", nome) == 1)
    {
        int len = strlen(nome);
        if(len > 0 && nome[len-1] == '\r') nome[len-1] = '\0';
        if(strcmp(nome, "FIM") == 0) break;
        pesquisar(nome, &comparacoes);
    }

    long tempo = (long)(((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);

    caminhar_central(raiz);

    gerar_log("892665", "arvore_bicolor", comparacoes, tempo);

    liberar_arvore(raiz);
    free(NIL_NO);
    free_colecao(c);

    return 0;
}

/*---- Funções da Árvore Bicolor ----*/

No* novo_no(Restaurante* r)
{
    No* no = (No*) malloc(sizeof(No));
    no->restaurante = r;
    no->esq = NIL_NO;
    no->dir = NIL_NO;
    no->pai = NIL_NO;
    no->cor = RED;
    return no;
}

void iniciar()
{
    NIL_NO = (No*) malloc(sizeof(No));
    NIL_NO->cor = BLACK;
    NIL_NO->esq = NIL_NO;
    NIL_NO->dir = NIL_NO;
    NIL_NO->pai = NIL_NO;
    NIL_NO->restaurante = NULL;
    raiz = NIL_NO;
}

void rotacao_esquerda(No* x)
{
    No* y = x->dir;
    x->dir = y->esq;
    if(y->esq != NIL_NO) y->esq->pai = x;
    y->pai = x->pai;
    if(x->pai == NIL_NO) raiz = y;
    else if(x == x->pai->esq) x->pai->esq = y;
    else x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

void rotacao_direita(No* y)
{
    No* x = y->esq;
    y->esq = x->dir;
    if(x->dir != NIL_NO) x->dir->pai = y;
    x->pai = y->pai;
    if(y->pai == NIL_NO) raiz = x;
    else if(y == y->pai->dir) y->pai->dir = x;
    else y->pai->esq = x;
    x->dir = y;
    y->pai = x;
}

void inserir_fixup(No* z)
{
    while(z->pai->cor == RED)
    {
        if(z->pai == z->pai->pai->esq)
        {
            No* tio = z->pai->pai->dir;
            if(tio->cor == RED)
            {
                z->pai->cor = BLACK;
                tio->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;
            }
            else
            {
                if(z == z->pai->dir)
                {
                    z = z->pai;
                    rotacao_esquerda(z);
                }
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                rotacao_direita(z->pai->pai);
            }
        }
        else
        {
            No* tio = z->pai->pai->esq;
            if(tio->cor == RED)
            {
                z->pai->cor = BLACK;
                tio->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;
            }
            else
            {
                if(z == z->pai->esq)
                {
                    z = z->pai;
                    rotacao_direita(z);
                }
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                rotacao_esquerda(z->pai->pai);
            }
        }
    }
    raiz->cor = BLACK;
}

void inserir(Restaurante* r)
{
    No* z = novo_no(r);
    No* y = NIL_NO;
    No* x = raiz;

    while(x != NIL_NO)
    {
        y = x;
        int cmp = strcmp(r->nome, x->restaurante->nome);
        if(cmp < 0) x = x->esq;
        else if(cmp > 0) x = x->dir;
        else
        {
            free(z);
            return;
        }
    }

    z->pai = y;
    if(y == NIL_NO) raiz = z;
    else if(strcmp(r->nome, y->restaurante->nome) < 0) y->esq = z;
    else y->dir = z;

    inserir_fixup(z);
}

int pesquisar_rec(char nome[], No* i, int* comparacoes)
{
    if(i == NIL_NO) return 0;

    (*comparacoes)++;
    if(strcmp(nome, i->restaurante->nome) == 0) return 1;

    (*comparacoes)++;
    if(strcmp(nome, i->restaurante->nome) < 0)
    {
        printf("esq ");
        return pesquisar_rec(nome, i->esq, comparacoes);
    }
    else
    {
        printf("dir ");
        return pesquisar_rec(nome, i->dir, comparacoes);
    }
}

void pesquisar(char nome[], int* comparacoes)
{
    printf("raiz ");
    int resp = pesquisar_rec(nome, raiz, comparacoes);
    if(resp) printf("SIM\n");
    else printf("NAO\n");
}

void caminhar_central(No* i)
{
    if(i != NIL_NO)
    {
        caminhar_central(i->esq);
        char buffer[MAX_BUFFER];
        formatar_restaurante(i->restaurante, buffer);
        printf("%s\n", buffer);
        caminhar_central(i->dir);
    }
}

void liberar_arvore(No* i)
{
    if(i != NIL_NO)
    {
        liberar_arvore(i->esq);
        liberar_arvore(i->dir);
        free(i);
    }
}

/*---- Infraestrutura ----*/

Hora parse_hora(char s[])
{
    Hora h;
    sscanf(s, "%d:%d", &h.hora, &h.minuto);
    return h;
}

void formatar_hora(Hora* hora, char buffer[])
{
    sprintf(buffer, "%02d:%02d", hora->hora, hora->minuto);
}

Data parse_data(char s[])
{
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

void formatar_data(Data* data, char buffer[])
{
    sprintf(buffer, "%02d/%02d/%04d", data->dia, data->mes, data->ano);
}

void string_to_array(char s[], char tipos[][MAX_TIPO_STR], int* n)
{
    char copia[MAX_STR];
    strcpy(copia, s);
    *n = 0;
    char* token = strtok(copia, ";");
    while(token != NULL)
    {
        strcpy(tipos[*n], token);
        (*n)++;
        token = strtok(NULL, ";");
    }
}

Restaurante* parse_restaurante(char s[])
{
    Restaurante* r = (Restaurante*) malloc(sizeof(Restaurante));
    char linha[4096];
    strcpy(linha, s);
    char tokens[12][512];
    int n_tokens = 0;
    char* tok = strtok(linha, ",");
    while(tok != NULL && n_tokens < 12)
    {
        strcpy(tokens[n_tokens++], tok);
        tok = strtok(NULL, ",");
    }
    r->id = atoi(tokens[0]);
    strcpy(r->nome, tokens[1]);
    strcpy(r->cidade, tokens[2]);
    r->capacidade = atoi(tokens[3]);
    r->avaliacao = atof(tokens[4]);
    string_to_array(tokens[5], r->tipos_cozinha, &r->n_tipos_cozinha);
    r->faixa_preco = strlen(tokens[6]);
    char h_abertura[10], h_fechamento[10];
    sscanf(tokens[7], "%[^-]-%s", h_abertura, h_fechamento);
    r->horario_abertura = parse_hora(h_abertura);
    r->horario_fechamento = parse_hora(h_fechamento);
    r->data_abertura = parse_data(tokens[8]);
    r->aberto = (strcmp(tokens[9], "true") == 0) ? 1 : 0;
    return r;
}

void formatar_restaurante(Restaurante* r, char buffer[])
{
    char tipos[500];
    tipos[0] = '\0';
    strcat(tipos, "[");
    for(int i = 0; i < r->n_tipos_cozinha; i++)
    {
        strcat(tipos, r->tipos_cozinha[i]);
        if(i < r->n_tipos_cozinha - 1) strcat(tipos, ",");
    }
    strcat(tipos, "]");

    char faixa[10];
    faixa[0] = '\0';
    for(int i = 0; i < r->faixa_preco; i++) strcat(faixa, "$");

    char h_abertura[10], h_fechamento[10], data[15];
    formatar_hora(&r->horario_abertura, h_abertura);
    formatar_hora(&r->horario_fechamento, h_fechamento);
    formatar_data(&r->data_abertura, data);

    sprintf(buffer, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
        r->id, r->nome, r->cidade, r->capacidade, r->avaliacao,
        tipos, faixa, h_abertura, h_fechamento, data,
        r->aberto ? "true" : "false");
}

void ler_csv_colecao(Colecao_Restaurantes* c, char path[])
{
    FILE* f = fopen(path, "r");
    if(!f)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    char linha[4096];
    int cont = 0;
    fgets(linha, sizeof(linha), f);
    while(fgets(linha, sizeof(linha), f) != NULL) cont++;
    c->tamanho = cont;
    c->restaurantes = (Restaurante**) malloc(cont * sizeof(Restaurante*));
    rewind(f);
    int i = 0;
    fgets(linha, sizeof(linha), f);
    while(fgets(linha, sizeof(linha), f) != NULL)
    {
        int len = strlen(linha);
        while(len > 0 && (linha[len-1] == '\n' || linha[len-1] == '\r')) linha[--len] = '\0';
        c->restaurantes[i++] = parse_restaurante(linha);
    }
    fclose(f);
}

Colecao_Restaurantes* ler_csv()
{
    Colecao_Restaurantes* c = (Colecao_Restaurantes*) malloc(sizeof(Colecao_Restaurantes));
    ler_csv_colecao(c, "/tmp/restaurantes.csv");
    return c;
}

Restaurante* get_restaurante_by_id(Colecao_Restaurantes* c, int id)
{
    for(int i = 0; i < c->tamanho; i++)
        if(c->restaurantes[i]->id == id) return c->restaurantes[i];
    return NULL;
}

void free_restaurante(Restaurante* r)
{
    if(r) free(r);
}

void free_colecao(Colecao_Restaurantes* c)
{
    if(c)
    {
        if(c->restaurantes)
        {
            for(int i = 0; i < c->tamanho; i++) free_restaurante(c->restaurantes[i]);
            free(c->restaurantes);
        }
        free(c);
    }
}

void gerar_log(char matricula[], char algoritmo[], int comparacoes, long tempo)
{
    char filename[100];
    sprintf(filename, "%s_%s.txt", matricula, algoritmo);
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s\t%d\t%ld", matricula, comparacoes, tempo);
    fclose(f);
}
