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
Restaurante** separar_restaurantes(Colecao_Restaurantes* c, int* total);
// Exporta as metricas de desempenho para um arquivo texto log
void gerar_log(char* matricula, char* algoritmo, int comparacoes, int movimentacoes, double tempo);
void free_restaurante(Restaurante* r);
// Libera toda a colecao e seus restaurantes para evitar memory leaks
void free_colecao(Colecao_Restaurantes* c);
void insercao_parcial(Restaurante** lista, int n, int* comparacoes, int* movimentacoes);

// Funcao principal que orquestra a leitura, ordenacao e impressao
int main()
{
    Colecao_Restaurantes* c = ler_csv();
    int total;
    Restaurante** selecionados = separar_restaurantes(c, &total);

    int comparacoes = 0, movimentacoes = 0;

    clock_t inicio = clock();
    
    // Executar metodo de ordenacao parcial
    insercao_parcial(selecionados, total, &comparacoes, &movimentacoes);
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    for(int i = 0; i < total; i++)
    {
        char buffer[MAX_BUFFER];
        formatar_restaurante(selecionados[i], buffer);
        printf("%s\n", buffer);
    }

    // Gerar log no formato exigido
    gerar_log("892665", "insercao_parcial", comparacoes, movimentacoes, tempo);

    // Liberar memoria para evitar memory leaks
    free(selecionados);
    free_colecao(c);

    return 0;
}

// Le os ids do terminal e retorna um array de restaurantes correspondentes
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
                break;
            }
        }
    }

    free(ids);
    return selecionados;
}

// Implementa o algoritmo de ordenacao parcial por insercao mantendo apenas os k menores
void insercao_parcial(Restaurante** lista, int n, int* comparacoes, int* movimentacoes)
{
    int k = 10;
    if (k > n) k = n;

    for (int i = 1; i < n; i++) {
        Restaurante* tmp = lista[i];
        (*movimentacoes)++;
        
        int j = (i < k) ? i - 1 : k - 1;

        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(lista[j]->cidade, tmp->cidade) > 0) {
                lista[j + 1] = lista[j];
                (*movimentacoes)++;
                j--;
            } else {
                break;
            }
        }

        lista[j + 1] = tmp;
        (*movimentacoes)++;
    }
}

// Cria o arquivo de log com os dados de desempenho
void gerar_log(char* matricula, char* algoritmo, int comparacoes, int movimentacoes, double tempo)
{
    char filename[100];
    sprintf(filename, "%s_%s.txt", matricula, algoritmo);
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s\t%d\t%d\t%f", matricula, comparacoes, movimentacoes, tempo);
    fclose(f);
}

/*-------------------------------------------------------------------------------------------------------*/

// Converte string HH:mm para struct Hora
Hora parse_hora(char* s)
{
    Hora h;
    sscanf(s, "%d:%d", &h.hora, &h.minuto);
    return h;
}

// Formata struct Hora para string HH:mm
void formatar_hora(Hora* hora, char* buffer)
{
    sprintf(buffer, "%02d:%02d", hora->hora, hora->minuto);
}

// Converte string YYYY-MM-DD para struct Data
Data parse_data(char* s)
{
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}

// Formata struct Data para string DD/MM/YYYY
void formatar_data(Data* data, char* buffer)
{
    sprintf(buffer, "%02d/%02d/%04d", data->dia, data->mes, data->ano);
}

// Quebra a string separada por ';' e armazena no array bidimensional
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

// Instancia um Restaurante e popula os campos extraindo da linha do CSV
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

// Formata os dados de um restaurante em uma unica string para impressao
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

// Conta linhas do arquivo, faz as alocacoes e popula o struct da Colecao
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

// Popula a colecao baseando-se no arquivo de dados padrao
Colecao_Restaurantes* ler_csv()
{
    Colecao_Restaurantes* c = (Colecao_Restaurantes*) malloc(sizeof(Colecao_Restaurantes));
    ler_csv_colecao(c, "/tmp/restaurantes.csv");
    return c;
}

// Libera memoria individual de um restaurante
void free_restaurante(Restaurante* r) {
    if (r) free(r);
}

// Percorre a colecao dando free nos ponteiros dos restaurantes e no ponteiro master
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