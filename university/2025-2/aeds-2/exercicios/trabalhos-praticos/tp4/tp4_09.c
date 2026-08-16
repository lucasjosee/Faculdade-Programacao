/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 04 - Q9 - Trie com Lista Flexível em C
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

typedef struct NoFilho
{
    char c;
    struct NoTrie* filho;
    struct NoFilho* prox;
} NoFilho;

typedef struct NoTrie
{
    Restaurante* restaurante;
    NoFilho* filhos;
} NoTrie;

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

NoTrie* novo_no_trie();
NoTrie* buscar_filho(NoFilho* lista, char c, int* comparacoes);
void inserir_filho(NoTrie* pai, char c, NoTrie* filho);
void inserir(NoTrie* raiz, Restaurante* r);
void pesquisar(NoTrie* raiz, char nome[], int* comparacoes);
void liberar_trie(NoTrie* no);

/*---- Main ----*/

int main()
{
    Colecao_Restaurantes* c = ler_csv();
    NoTrie* raiz = novo_no_trie();

    int id;
    while(scanf("%d", &id) == 1 && id != -1)
    {
        Restaurante* r = get_restaurante_by_id(c, id);
        if(r) inserir(raiz, r);
    }

    int comparacoes = 0;
    clock_t inicio = clock();

    char nome[MAX_STR];
    while(scanf(" %[^\n]", nome) == 1)
    {
        int len = strlen(nome);
        if(len > 0 && nome[len-1] == '\r') nome[len-1] = '\0';
        if(strcmp(nome, "FIM") == 0) break;
        pesquisar(raiz, nome, &comparacoes);
    }

    long tempo = (long)(((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);

    gerar_log("892665", "arvore_trie_lista", comparacoes, tempo);

    liberar_trie(raiz);
    free_colecao(c);
    return 0;
}

/*---- Funções da Trie com Lista ----*/

NoTrie* novo_no_trie()
{
    NoTrie* no = (NoTrie*) malloc(sizeof(NoTrie));
    no->restaurante = NULL;
    no->filhos = NULL;
    return no;
}

NoTrie* buscar_filho(NoFilho* lista, char c, int* comparacoes)
{
    while(lista != NULL)
    {
        (*comparacoes)++;
        if(lista->c == c) return (NoTrie*) lista->filho;
        lista = lista->prox;
    }
    return NULL;
}

void inserir_filho(NoTrie* pai, char c, NoTrie* filho)
{
    NoFilho* nf = (NoFilho*) malloc(sizeof(NoFilho));
    nf->c = c;
    nf->filho = (struct NoTrie*) filho;
    nf->prox = pai->filhos;
    pai->filhos = nf;
}

void inserir(NoTrie* raiz, Restaurante* r)
{
    NoTrie* atual = raiz;
    int dummy = 0;
    for(int i = 0; r->nome[i] != '\0'; i++)
    {
        char c = r->nome[i];
        NoTrie* proximo = buscar_filho(atual->filhos, c, &dummy);
        if(proximo == NULL)
        {
            proximo = novo_no_trie();
            inserir_filho(atual, c, proximo);
        }
        atual = proximo;
    }
    atual->restaurante = r;
}

void pesquisar(NoTrie* raiz, char nome[], int* comparacoes)
{
    NoTrie* atual = raiz;
    int primeiro = 1;

    for(int i = 0; nome[i] != '\0'; i++)
    {
        char c = nome[i];

        NoTrie* proximo = buscar_filho(atual->filhos, c, comparacoes);
        if(proximo == NULL)
        {
            printf(" NAO\n");
            return;
        }

        if(!primeiro) printf(" ");
        printf("%c", c);
        primeiro = 0;
        atual = proximo;
    }

    if(atual->restaurante != NULL)
    {
        char buffer[MAX_BUFFER];
        formatar_restaurante(atual->restaurante, buffer);
        printf(" SIM %s\n", buffer);
    }
    else printf(" NAO\n");
}

void liberar_trie(NoTrie* no)
{
    if(no == NULL) return;

    NoFilho* filho = no->filhos;
    while(filho != NULL)
    {
        NoFilho* prox = filho->prox;
        liberar_trie((NoTrie*) filho->filho);
        free(filho);
        filho = prox;
    }

    free(no);
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
