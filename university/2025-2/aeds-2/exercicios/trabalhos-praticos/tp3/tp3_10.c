#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TIPOS 10
#define MAX_STR 200
#define MAX_TIPO_STR 50
#define MAX_BUFFER 2048

//---- Structs ----

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

typedef struct
{
    int tamanho;
    Restaurante** restaurantes;
} Colecao_Restaurantes;

typedef struct Celula {
    Restaurante* restaurante;
    struct Celula* prox;
} Celula;

//---- Prototipos ----

// Extrai hora e minuto de uma string
Hora parse_hora(char* s);
void formatar_hora(Hora* hora, char* buffer);
// Extrai ano, mes e dia de uma string
Data parse_data(char* s);
void formatar_data(Data* data, char* buffer);
// Converte a string de tipos de cozinha para um array de strings
void string_to_array(char* s, char tipos[][MAX_TIPO_STR], int* n);
Restaurante* parse_restaurante(char* s);
// Transforma o restaurante formatado em um display de string para exibicao
void formatar_restaurante(Restaurante* r, char* buffer);
void ler_csv_colecao(Colecao_Restaurantes* c, char* path);
// Retorna uma colecao de restaurantes preenchida
Colecao_Restaurantes* ler_csv();
Restaurante* get_restaurante_by_id(Colecao_Restaurantes* c, int id);
// Libera a memoria alocada para um unico restaurante
void free_restaurante(Restaurante* r);
void free_colecao(Colecao_Restaurantes* c);
// Exporta as metricas de desempenho para um arquivo texto log
void gerar_log(char* matricula, char* algoritmo, int comparacoes, int movimentacoes, long tempo);

//---- Lista Flexivel ----
Celula* primeiro;
Celula* ultimo;

// Inicializa a estrutura de dados e seus ponteiros base
void iniciar() {
    primeiro = (Celula*) malloc(sizeof(Celula));
    primeiro->restaurante = NULL;
    primeiro->prox = NULL;
    ultimo = primeiro;
}

// Aloca e anexa o elemento no fim da estrutura
void inserirFim(Restaurante* x) {
    ultimo->prox = (Celula*) malloc(sizeof(Celula));
    ultimo = ultimo->prox;
    ultimo->restaurante = x;
    ultimo->prox = NULL;
}

// Varre a estrutura imprimindo seus elementos na saida padrao
void mostrar() {
    for (Celula* i = primeiro->prox; i != NULL; i = i->prox) {
        char buffer[MAX_BUFFER];
        formatar_restaurante(i->restaurante, buffer);
        printf("%s\n", buffer);
    }
}

// Libera da memoria de forma recursiva os nos alocados na estrutura
void liberar() {
    Celula* i = primeiro;
    while (i != NULL) {
        Celula* tmp = i;
        i = i->prox;
        free(tmp);
    }
}

void selecao(int* comp, int* mov) {
    for (Celula* i = primeiro->prox; i != NULL; i = i->prox) {
        Celula* menor = i;
        for (Celula* j = i->prox; j != NULL; j = j->prox) {
            (*comp)++;
            if (strcmp(j->restaurante->nome, menor->restaurante->nome) < 0) {
                menor = j;
            }
        }
        if (menor != i) {
            Restaurante* tmp = i->restaurante;
            i->restaurante = menor->restaurante;
            menor->restaurante = tmp;
            (*mov) += 3;
        }
    }
}

int main()
{
    Colecao_Restaurantes* c = ler_csv();

    iniciar();

    int id;
    while(scanf("%d", &id) == 1 && id != -1)
    {
        Restaurante* r = get_restaurante_by_id(c, id);
        if (r) inserirFim(r);
    }

    int comparacoes = 0, movimentacoes = 0;
    clock_t inicio = clock();

    selecao(&comparacoes, &movimentacoes);

    long tempo = (long)(((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);

    mostrar();

    gerar_log("892665", "selecao_flexivel", comparacoes, movimentacoes, tempo);

    liberar();
    free_colecao(c);

    return 0;
}

// Faz a varredura linear na colecao para resgatar o restaurante pelo ID
Restaurante* get_restaurante_by_id(Colecao_Restaurantes* c, int id) {
    for (int i = 0; i < c->tamanho; i++) {
        if (c->restaurantes[i]->id == id) {
            return c->restaurantes[i];
        }
    }
    return NULL;
}

//Funcao que gera o arquivo de log
void gerar_log(char* matricula, char* algoritmo, int comparacoes, int movimentacoes, long tempo)
{
    char filename[100];
    sprintf(filename, "%s_%s.txt", matricula, algoritmo);
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s\t%d\t%d\t%ld", matricula, comparacoes, movimentacoes, tempo);
    fclose(f);
}

//Classes Principais
/*-------------------------------------------------------------------------------------------------------*/

// Extrai hora e minuto de uma string
Hora parse_hora(char* s)
{
    Hora h;
    sscanf(s, "%d:%d", &h.hora, &h.minuto);
    return h;
}

void formatar_hora(Hora* hora, char* buffer)
{
    sprintf(buffer, "%02d:%02d", hora->hora, hora->minuto);
}

// Extrai ano, mes e dia de uma string
Data parse_data(char* s)
{
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

void formatar_data(Data* data, char* buffer)
{
    sprintf(buffer, "%02d/%02d/%04d", data->dia, data->mes, data->ano);
}

// Converte a string de tipos de cozinha para um array de strings
void string_to_array(char* s, char tipos[][MAX_TIPO_STR], int* n)
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

// Recebe uma linha CSV, faz a quebra dos atributos e monta a struct do Restaurante
Restaurante* parse_restaurante(char* s)
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

// Transforma o restaurante formatado em um display de string para exibicao
void formatar_restaurante(Restaurante* r, char* buffer)
{
    char tipos[500];
    tipos[0] = '\0';
    strcat(tipos, "[");
    for(int i = 0; i < r->n_tipos_cozinha; i++)
    {
        strcat(tipos, r->tipos_cozinha[i]);
        if(i < r->n_tipos_cozinha - 1)
            strcat(tipos, ",");
    }
    strcat(tipos, "]");

    char faixa[10];
    faixa[0] = '\0';
    for(int i = 0; i < r->faixa_preco; i++)
        strcat(faixa, "$");

    char h_abertura[10], h_fechamento[10], data[15];
    formatar_hora(&r->horario_abertura, h_abertura);
    formatar_hora(&r->horario_fechamento, h_fechamento);
    formatar_data(&r->data_abertura, data);

    sprintf(buffer, "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %s]",
        r->id, r->nome, r->cidade, r->capacidade, r->avaliacao,
        tipos, faixa, h_abertura, h_fechamento, data,
        r->aberto ? "true" : "false");
}

// Le os dados do CSV e instancia os restaurantes
void ler_csv_colecao(Colecao_Restaurantes* c, char* path)
{
    FILE* f = fopen(path, "r");
    if(f == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    char linha[4096];
    int cont = 0;

    fgets(linha, sizeof(linha), f); 
    while(fgets(linha, sizeof(linha), f) != NULL)
    {
        cont++;
    }

    c->tamanho = cont;
    c->restaurantes = (Restaurante**) malloc(cont * sizeof(Restaurante*));

    rewind(f);

    int i = 0;
    fgets(linha, sizeof(linha), f); 
    while(fgets(linha, sizeof(linha), f) != NULL)
    {
        int len = strlen(linha);
        while(len > 0 && (linha[len-1] == '\n' || linha[len-1] == '\r'))
            linha[--len] = '\0';

        c->restaurantes[i] = parse_restaurante(linha);
        i++;
    }

    fclose(f);
}

// Retorna uma colecao de restaurantes preenchida
Colecao_Restaurantes* ler_csv()
{
    Colecao_Restaurantes* c = (Colecao_Restaurantes*) malloc(sizeof(Colecao_Restaurantes));
    ler_csv_colecao(c, "/tmp/restaurantes.csv");
    return c;
}

// Libera a memoria alocada para um unico restaurante
void free_restaurante(Restaurante* r) {
    if (r) free(r);
}

// Libera toda a colecao e seus restaurantes para evitar memory leaks
void free_colecao(Colecao_Restaurantes* c) {
    if (c) {
        if (c->restaurantes) {
            for (int i = 0; i < c->tamanho; i++) {
                free_restaurante(c->restaurantes[i]);
            }
            free(c->restaurantes);
        }
        free(c);
    }
}
/*-------------------------------------------------------------------------------------------------------*/