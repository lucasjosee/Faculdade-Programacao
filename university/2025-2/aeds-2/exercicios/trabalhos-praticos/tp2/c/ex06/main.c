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

//---- Prototipos ----

Hora parse_hora(char* s);
void formatar_hora(Hora* hora, char* buffer);
Data parse_data(char* s);
void formatar_data(Data* data, char* buffer);
void string_to_array(char* s, char tipos[][MAX_TIPO_STR], int* n);
Restaurante* parse_restaurante(char* s);
void formatar_restaurante(Restaurante* r, char* buffer);
void ler_csv_colecao(Colecao_Restaurantes* c, char* path);
Colecao_Restaurantes* ler_csv();
Restaurante** separar_restaurantes(Colecao_Restaurantes* c, int* total);
void gerar_log(char* matricula, char* algoritmo, int comparacoes, int movimentacoes, long tempo);
void swap(Restaurante** array, int i, int j);
void selection_sort(Restaurante** selecionados, int tamanho, int* comparacoes, int* movimentacoes);
int pesquisa_binaria(Restaurante** selecionados, int tamanho, char* nome, int* comparacoes);

int main()
{
    Colecao_Restaurantes* c = ler_csv();
    int total;
    Restaurante** selecionados = separar_restaurantes(c, &total);

    //Ordena para poder fazer a pesquisa binaria
    int comp_ord = 0, mov_ord = 0;
    selection_sort(selecionados, total, &comp_ord, &mov_ord);

    int comparacoes = 0;

    //Consome o restante da linha do -1
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);

    clock_t inicio = clock();

    char linha[MAX_STR];
    while(fgets(linha, sizeof(linha), stdin) != NULL)
    {
        //Remove o newline do final
        int len = strlen(linha);
        while(len > 0 && (linha[len-1] == '\n' || linha[len-1] == '\r'))
            linha[--len] = '\0';

        if(strcmp(linha, "FIM") == 0)
            break;

        if(pesquisa_binaria(selecionados, total, linha, &comparacoes))
            printf("SIM\n");
        else
            printf("NAO\n");
    }

    long tempo = (long)(((double)(clock() - inicio)) / CLOCKS_PER_SEC * 1000);
    gerar_log("892665", "binaria", comparacoes, 0, tempo);

    return 0;
}

//Le os ids que vao ser processados e devolve o array pronto para a main
Restaurante** separar_restaurantes(Colecao_Restaurantes* c, int* total)
{
    int* ids = (int*) malloc(c->tamanho * sizeof(int));
    int total_ids = 0;
    int n;

    while(scanf("%d", &n) == 1 && n != -1)
    {
        ids[total_ids++] = n;
    }

    Restaurante** selecionados = (Restaurante**) malloc(total_ids * sizeof(Restaurante*));
    *total = total_ids;

    for(int i = 0; i < total_ids; i++)
    {
        for(int j = 0; j < c->tamanho; j++)
        {
            if(c->restaurantes[j]->id == ids[i])
            {
                selecionados[i] = c->restaurantes[j];
                j = c->tamanho;
            }
        }
    }

    free(ids);
    return selecionados;
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

void swap(Restaurante** array, int i, int j)
{
    Restaurante* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

//---------------------SelectionSort (usada para ordenar antes da busca)----------------------//
void selection_sort(Restaurante** selecionados, int tamanho, int* comparacoes, int* movimentacoes)
{
    for(int i = 0; i < tamanho - 1; i++)
    {
        int menor = i;
        for(int j = i + 1; j < tamanho; j++)
        {
            (*comparacoes)++;
            if(strcmp(selecionados[j]->nome, selecionados[menor]->nome) < 0)
            {
                menor = j;
            }
        }
        if(menor != i)
        {
            swap(selecionados, i, menor);
            (*movimentacoes) += 3;
        }
    }
}

//---------------------Pesquisa Binaria----------------------//
int pesquisa_binaria(Restaurante** selecionados, int tamanho, char* nome, int* comparacoes)
{
    int esq = 0, dir = tamanho - 1;
    int resp = 0;

    while(esq <= dir)
    {
        int meio = (esq + dir) / 2;
        (*comparacoes)++;
        int cmp = strcmp(selecionados[meio]->nome, nome);
        if(cmp == 0)
        {
            resp = 1;
            esq = dir + 1;
        }
        else if(cmp < 0)
        {
            esq = meio + 1;
        }
        else
        {
            dir = meio - 1;
        }
    }
    return resp;
}

//Classes Principais
/*-------------------------------------------------------------------------------------------------------*/

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

void string_to_array(char* s, char tipos[][MAX_TIPO_STR], int* n)
{
    //Scanner varre string s parando nos ;
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

Restaurante* parse_restaurante(char* s)
{
    Restaurante* r = (Restaurante*) malloc(sizeof(Restaurante));

    char linha[4096];
    strcpy(linha, s);

    //Coleta todos os tokens separados por virgula antes de processar
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

    //tipos_cozinha
    string_to_array(tokens[5], r->tipos_cozinha, &r->n_tipos_cozinha);

    //Le $$$ e retorna o tamanho
    r->faixa_preco = strlen(tokens[6]);

    //Parse da hora
    char h_abertura[10], h_fechamento[10];
    sscanf(tokens[7], "%[^-]-%s", h_abertura, h_fechamento);
    r->horario_abertura = parse_hora(h_abertura);
    r->horario_fechamento = parse_hora(h_fechamento);

    //Parse da data
    r->data_abertura = parse_data(tokens[8]);

    //aberto
    r->aberto = (strcmp(tokens[9], "true") == 0) ? 1 : 0;

    return r;
}

void formatar_restaurante(Restaurante* r, char* buffer)
{
    //Preenche a string tipos, para que o array de tipos_cozinha possa ser imprimido
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

    //Como a faixa de preco esta salva como int, transformamos o int em string de $
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

    fgets(linha, sizeof(linha), f); //Pula a primeira linha
    while(fgets(linha, sizeof(linha), f) != NULL)
    {
        cont++;
    }

    c->tamanho = cont;
    c->restaurantes = (Restaurante**) malloc(cont * sizeof(Restaurante*));

    rewind(f);

    int i = 0;
    fgets(linha, sizeof(linha), f); //Pula a primeira linha
    while(fgets(linha, sizeof(linha), f) != NULL)
    {
        //Remove o newline do final
        int len = strlen(linha);
        while(len > 0 && (linha[len-1] == '\n' || linha[len-1] == '\r'))
            linha[--len] = '\0';

        c->restaurantes[i] = parse_restaurante(linha);
        i++;
    }

    fclose(f);
}

Colecao_Restaurantes* ler_csv()
{
    Colecao_Restaurantes* c = (Colecao_Restaurantes*) malloc(sizeof(Colecao_Restaurantes));
    ler_csv_colecao(c, "/tmp/restaurantes.csv");
    return c;
}

/*-------------------------------------------------------------------------------------------------------*/
