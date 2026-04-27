#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct
{
    Restaurante** pilha;
    int n;
    int capacidade;
} Pilha;

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
Restaurante* buscar_por_id(Colecao_Restaurantes* c, int id);
void inicializar_pilha(Pilha* p, int capacidade);
void empilhar(Pilha* p, Restaurante* r);
Restaurante* desempilhar(Pilha* p);
void mostrar_pilha(Pilha* p);

int main()
{
    Colecao_Restaurantes* c = ler_csv();
    int total;
    Restaurante** selecionados = separar_restaurantes(c, &total);

    Pilha pilha;
    inicializar_pilha(&pilha, 1000);

    for(int i = 0; i < total; i++)
        empilhar(&pilha, selecionados[i]);

    int n_ops;
    scanf("%d", &n_ops);
    for(int i = 0; i < n_ops; i++)
    {
        char cmd[5];
        scanf("%s", cmd);
        if(strcmp(cmd, "I") == 0)
        {
            int id;
            scanf("%d", &id);
            empilhar(&pilha, buscar_por_id(c, id));
        }
        else if(strcmp(cmd, "R") == 0)
        {
            Restaurante* r = desempilhar(&pilha);
            printf("(R)%s\n", r->nome);
        }
    }

    mostrar_pilha(&pilha);

    return 0;
}

//Busca um restaurante pelo id na colecao
Restaurante* buscar_por_id(Colecao_Restaurantes* c, int id)
{
    for(int i = 0; i < c->tamanho; i++)
    {
        if(c->restaurantes[i]->id == id)
            return c->restaurantes[i];
    }
    return NULL;
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

//---------------------Pilha com Alocacao Sequencial----------------------//

void inicializar_pilha(Pilha* p, int capacidade)
{
    p->pilha = (Restaurante**) malloc(capacidade * sizeof(Restaurante*));
    p->n = 0;
    p->capacidade = capacidade;
}

//Insere no topo da pilha
void empilhar(Pilha* p, Restaurante* r)
{
    p->pilha[p->n++] = r;
}

//Remove e retorna o elemento do topo da pilha
Restaurante* desempilhar(Pilha* p)
{
    return p->pilha[--p->n];
}

//Imprime todos os elementos da pilha do topo ate a base
void mostrar_pilha(Pilha* p)
{
    for(int i = p->n - 1; i >= 0; i--)
    {
        char buffer[MAX_BUFFER];
        formatar_restaurante(p->pilha[i], buffer);
        printf("%s\n", buffer);
    }
}

//-------------------------------------------//

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
