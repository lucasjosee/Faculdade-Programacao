/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 04 - Q7 - Árvore Binária de Lista em C
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

typedef struct NoCelula
{
    Restaurante* restaurante;
    struct NoCelula* prox;
} NoCelula;

typedef struct No
{
    char chave;
    NoCelula* lista;
    struct No* esq;
    struct No* dir;
} No;

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

No* novo_no_arvore(char chave);
void inserir_lista(NoCelula** lista, Restaurante* r);
No* inserir_rec(No* no, Restaurante* r);
void inserir(Restaurante* r);
int pesquisar_rec(char nome[], No* no, int* comparacoes);
void pesquisar(char nome[], int* comparacoes);
void liberar_lista(NoCelula* lista);
void liberar_arvore(No* no);

No* raiz;

/*---- Main ----*/

int main()
{
    Colecao_Restaurantes* c = ler_csv();
    raiz = NULL;

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

    gerar_log("892665", "hibrida_arvore_lista", comparacoes, tempo);

    liberar_arvore(raiz);
    free_colecao(c);
    return 0;
}

/*---- Funções da Árvore de Lista ----*/

No* novo_no_arvore(char chave)
{
    No* no = (No*) malloc(sizeof(No));
    no->chave = chave;
    no->lista = NULL;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

void inserir_lista(NoCelula** lista, Restaurante* r)
{
    NoCelula* nova = (NoCelula*) malloc(sizeof(NoCelula));
    nova->restaurante = r;
    nova->prox = NULL;

    if(*lista == NULL || strcmp(r->nome, (*lista)->restaurante->nome) < 0)
    {
        nova->prox = *lista;
        *lista = nova;
        return;
    }

    NoCelula* atual = *lista;
    while(atual->prox != NULL && strcmp(r->nome, atual->prox->restaurante->nome) > 0)
        atual = atual->prox;
    nova->prox = atual->prox;
    atual->prox = nova;
}

No* inserir_rec(No* no, Restaurante* r)
{
    char chave = r->nome[0];

    if(no == NULL)
    {
        no = novo_no_arvore(chave);
        inserir_lista(&no->lista, r);
    }
    else if(chave < no->chave)
    {
        no->esq = inserir_rec(no->esq, r);
    }
    else if(chave > no->chave)
    {
        no->dir = inserir_rec(no->dir, r);
    }
    else
    {
        inserir_lista(&no->lista, r);
    }

    return no;
}

void inserir(Restaurante* r)
{
    raiz = inserir_rec(raiz, r);
}

int pesquisar_rec(char nome[], No* no, int* comparacoes)
{
    if(no == NULL)
    {
        printf("NAO\n");
        return 0;
    }

    char chave = nome[0];
    (*comparacoes)++;

    if(chave < no->chave)
    {
        printf("ESQ ");
        return pesquisar_rec(nome, no->esq, comparacoes);
    }
    else if(chave > no->chave)
    {
        printf("DIR ");
        return pesquisar_rec(nome, no->dir, comparacoes);
    }
    else
    {
        NoCelula* atual = no->lista;
        while(atual != NULL)
        {
            (*comparacoes)++;
            int cmp = strcmp(atual->restaurante->nome, nome);
            if(cmp == 0)
            {
                char buffer[MAX_BUFFER];
                formatar_restaurante(atual->restaurante, buffer);
                printf("SIM %s\n", buffer);
                return 1;
            }
            if(cmp > 0) break;
            printf("%s ", atual->restaurante->nome);
            atual = atual->prox;
        }
        printf("NAO\n");
        return 0;
    }
}

void pesquisar(char nome[], int* comparacoes)
{
    printf("RAIZ ");
    pesquisar_rec(nome, raiz, comparacoes);
}

void liberar_lista(NoCelula* lista)
{
    while(lista != NULL)
    {
        NoCelula* prox = lista->prox;
        free(lista);
        lista = prox;
    }
}

void liberar_arvore(No* no)
{
    if(no != NULL)
    {
        liberar_arvore(no->esq);
        liberar_arvore(no->dir);
        liberar_lista(no->lista);
        free(no);
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
