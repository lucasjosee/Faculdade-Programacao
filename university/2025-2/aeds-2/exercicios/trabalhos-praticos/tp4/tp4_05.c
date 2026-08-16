/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 04 - Q5 - Tabela Hash Indireta com Lista Simples em C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TIPOS 10
#define MAX_STR 200
#define MAX_TIPO_STR 50
#define MAX_BUFFER 2048
#define TAM_TAB 31

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

typedef struct Celula
{
    Restaurante* restaurante;
    struct Celula* prox;
} Celula;

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

int ascii_sum(char nome[]);
void iniciar();
void inserir(Restaurante* r);
void pesquisar(char nome[], int* comparacoes);
void liberar_tabela();

Celula* tabela[TAM_TAB];

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

    gerar_log("892665", "hash_indireta", comparacoes, tempo);

    liberar_tabela();
    free_colecao(c);
    return 0;
}

/*---- Funções da Hash Indireta ----*/

int ascii_sum(char nome[])
{
    int soma = 0;
    for(int i = 0; nome[i] != '\0'; i++) soma += (unsigned char) nome[i];
    return soma;
}

void iniciar()
{
    for(int i = 0; i < TAM_TAB; i++) tabela[i] = NULL;
}

void inserir(Restaurante* r)
{
    int h = ascii_sum(r->nome) % TAM_TAB;
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->restaurante = r;
    nova->prox = tabela[h];
    tabela[h] = nova;
}

void pesquisar(char nome[], int* comparacoes)
{
    int h = ascii_sum(nome) % TAM_TAB;
    Celula* atual = tabela[h];

    while(atual != NULL)
    {
        (*comparacoes)++;
        if(strcmp(atual->restaurante->nome, nome) == 0)
        {
            char buffer[MAX_BUFFER];
            formatar_restaurante(atual->restaurante, buffer);
            printf("%d %s\n", h, buffer);
            return;
        }
        atual = atual->prox;
    }

    printf("-1\n");
}

void liberar_tabela()
{
    for(int i = 0; i < TAM_TAB; i++)
    {
        Celula* atual = tabela[i];
        while(atual != NULL)
        {
            Celula* prox = atual->prox;
            free(atual);
            atual = prox;
        }
        tabela[i] = NULL;
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
