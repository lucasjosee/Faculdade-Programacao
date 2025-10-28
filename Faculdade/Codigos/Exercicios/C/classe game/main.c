#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_SIZE 4096
#define MAX_FIELD_SIZE 2048
#define MAX_ARRAY_SIZE 150
#define MAX_ENTRADAS 1850

long long comparacoes = 0;
long long movimentacoes = 0;

typedef struct 
{
    int id;
    char* name;
    char* releaseDate;
    int estimatedOwners;
    float price;
    char** supportedLanguages;
    int languageCount;
    int metacriticScore;
    float userScore;
    int achievements;
    char** publishers;
    int publisherCount;
    char** developers;
    int developerCount;
    char** categories;
    int categoryCount;
    char** genres;
    int genreCount;
    char** tags;
    int tagCount;
} Game;

//PROTÓTIPOS
char* proximoCampo(char* linha, int* pos);
char* formatarData(const char* dataStr);
char** stringParaArray(const char* s, int* count);
char* trim(char *str);
int stringParaInt(const char* s);
float stringParaFloat(const char* s);
void mostrar(Game* jogo);
void freeGame(Game* jogo);
void selectionSort(Game** array, int n);
int compararNome(Game* a, Game* b);
void swap(Game** array, int i, int j);

int main() 
{
    char idDeEntrada[20];
    int idsParaBuscar[MAX_ENTRADAS];
    int numEntradas = 0;

    //Leitura dos IDs até "FIM"
    while (fgets(idDeEntrada, sizeof(idDeEntrada), stdin) != NULL) 
    {
        idDeEntrada[strcspn(idDeEntrada, "\n")] = 0;
        if (strcmp(idDeEntrada, "FIM") == 0) 
            break;
        idsParaBuscar[numEntradas++] = stringParaInt(idDeEntrada);
    }

    Game** jogos = (Game**) malloc(numEntradas * sizeof(Game*));
    int count = 0;

    //Lê os jogos do CSV correspondentes aos IDs
    for (int i = 0; i < numEntradas; i++) 
    {
        FILE* file = fopen("/tmp/games.csv", "r");
        if (file == NULL) 
        {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        char linha[MAX_LINE_SIZE];
        fgets(linha, MAX_LINE_SIZE, file); // pula cabeçalho

        while (fgets(linha, MAX_LINE_SIZE, file)) 
        {
            linha[strcspn(linha, "\n")] = 0;
            int pos = 0;
            char* idStr = proximoCampo(linha, &pos);
            int idAtual = stringParaInt(idStr);
            free(idStr);

            if (idAtual == idsParaBuscar[i]) 
            {
                Game* g = (Game*) malloc(sizeof(Game));
                g->id = idAtual;

                g->name = proximoCampo(linha, &pos);

                char* dataStr = proximoCampo(linha, &pos);
                g->releaseDate = formatarData(dataStr);
                free(dataStr);

                char* donosStr = proximoCampo(linha, &pos);
                g->estimatedOwners = stringParaInt(donosStr);
                free(donosStr);

                char* precoStr = proximoCampo(linha, &pos);
                g->price = strcmp(precoStr, "Free to Play") == 0 ? 0.0f : stringParaFloat(precoStr);
                free(precoStr);

                char* linguasStr = proximoCampo(linha, &pos);
                g->supportedLanguages = stringParaArray(linguasStr, &g->languageCount);
                free(linguasStr);

                char* metaScoreStr = proximoCampo(linha, &pos);
                g->metacriticScore = stringParaInt(metaScoreStr);
                free(metaScoreStr);

                char* userScoreStr = proximoCampo(linha, &pos);
                g->userScore = strcmp(userScoreStr, "tbd") == 0 ? -1.0f : stringParaFloat(userScoreStr);
                free(userScoreStr);

                char* conquistasStr = proximoCampo(linha, &pos);
                g->achievements = stringParaInt(conquistasStr);
                free(conquistasStr);

                char* publishersStr = proximoCampo(linha, &pos);
                g->publishers = stringParaArray(publishersStr, &g->publisherCount);
                free(publishersStr);

                char* developersStr = proximoCampo(linha, &pos);
                g->developers = stringParaArray(developersStr, &g->developerCount);
                free(developersStr);

                char* categoriesStr = proximoCampo(linha, &pos);
                g->categories = stringParaArray(categoriesStr, &g->categoryCount);
                free(categoriesStr);

                char* genresStr = proximoCampo(linha, &pos);
                g->genres = stringParaArray(genresStr, &g->genreCount);
                free(genresStr);

                char* tagsStr = proximoCampo(linha, &pos);
                g->tags = stringParaArray(tagsStr, &g->tagCount);
                free(tagsStr);

                jogos[count++] = g;
                break;
            }
        }
        fclose(file);
    }

    //Ordenação por seleção
    clock_t inicio = clock();
    selectionSort(jogos, count);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    //Exibe os jogos ordenados
    for (int i = 0; i < count; i++) 
    {
        mostrar(jogos[i]);
        freeGame(jogos[i]);
    }
    free(jogos);

    //Cria arquivo de log
    const char* MATRICULA = "892665";
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s_selecao.txt", MATRICULA);

    FILE* log = fopen(nomeArquivo, "w");
    if (log != NULL)
    {
        fprintf(log, "%s\t%lld\t%lld\t%.6f\n", MATRICULA, comparacoes, movimentacoes, tempo);
        fclose(log);
    }

    return 0;
}

//SELECTION SORT
void selectionSort(Game** array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;
        for (int j = i + 1; j < n; j++)
        {
            comparacoes++;
            if (compararNome(array[j], array[menor]) < 0)
                menor = j;
        }
        if (menor != i)
        {
            swap(array, i, menor);
        }
    }
}

//COMPARA NOME
int compararNome(Game* a, Game* b)
{
    return strcmp(a->name, b->name);
}

//TROCA POSIÇÕES
void swap(Game** array, int i, int j)
{
    Game* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    movimentacoes += 3;
}

//LEITURA DE CAMPOS
char* proximoCampo(char* linha, int* pos)
{
    char* campo = (char*)malloc(MAX_FIELD_SIZE);
    int i = *pos, j = 0;
    int aspas = 0;

    if (linha[i] == '"')
    {
        aspas = 1;
        i++;
    }

    while (linha[i] != '\0')
    {
        if (aspas && linha[i] == '"')
        {
            i++;
            break;
        }
        if (!aspas && linha[i] == ',')
            break;
        campo[j++] = linha[i++];
    }

    campo[j] = '\0';
    if (linha[i] == ',') i++;
    *pos = i;
    return campo;
}

//FORMATA DATA
char* formatarData(const char* dataStr)
{
    char* dataFormatada = (char*)malloc(11);
    char mesStr[4] = "Jan";
    int dia = 1, ano = 2000;

    if (strlen(dataStr) > 4)
        sscanf(dataStr, "%s %d, %d", mesStr, &dia, &ano);
    else if (strlen(dataStr) > 0)
        sscanf(dataStr, "%d", &ano);

    int mesNum = 0;
    const char* meses[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i = 0; i < 12; i++)
        if (strcmp(mesStr, meses[i]) == 0) mesNum = i + 1;

    if (mesNum == 0) mesNum = 1;
    sprintf(dataFormatada, "%02d/%02d/%d", dia, mesNum, ano);
    return dataFormatada;
}

//REMOVE ESPAÇOS
char* trim(char *str)
{
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

//TRANSFORMA STR EM ARRAY
char** stringParaArray(const char* s, int* count)
{
    *count = 0;
    if (s == NULL || strlen(s) == 0) return NULL;

    char** array = (char**)malloc(MAX_ARRAY_SIZE * sizeof(char*));
    char temp[MAX_FIELD_SIZE];
    strcpy(temp, s);

    if (temp[0] == '[' && strchr(temp, '\'')) 
    {
        char palavra[MAX_FIELD_SIZE];
        int palavraPos = 0;
        int dentroDeAspas = 0;
        for (int i = 0; i < strlen(temp); i++) 
        {
            if (temp[i] == '\'') 
            {
                dentroDeAspas = !dentroDeAspas;
                if (!dentroDeAspas && palavraPos > 0) 
                {
                    palavra[palavraPos] = '\0';
                    array[*count] = strdup(palavra);
                    (*count)++;
                    palavraPos = 0;
                }
            } 
            else if (dentroDeAspas) 
            {
                palavra[palavraPos++] = temp[i];
            }
        }
    } 
    else 
    {
        char* token = strtok(temp, ",");
        while (token != NULL) 
        {
            char* trimmed = trim(token);
            if(strlen(trimmed) > 0) 
                array[*count] = strdup(trimmed);
            (*count)++;
            token = strtok(NULL, ",");
        }
    }
    return array;
}

//STRING PARA INT E FLOAT
int stringParaInt(const char* s) { return atoi(s); }
float stringParaFloat(const char* s) { return atof(s); }

//MOSTRA JOGO
void mostrar(Game* jogo)
{
    printf("=> %d ## %s ## %s ## %d ## %.2f ## [", jogo->id, jogo->name, jogo->releaseDate, jogo->estimatedOwners, jogo->price);
    
    for (int i = 0; i < jogo->languageCount; i++) printf("%s%s", jogo->supportedLanguages[i], i == jogo->languageCount - 1 ? "" : ", ");
    printf("] ## %d ## %.1f ## %d ## [", jogo->metacriticScore, jogo->userScore, jogo->achievements);
    
    for (int i = 0; i < jogo->publisherCount; i++) printf("%s%s", jogo->publishers[i], i == jogo->publisherCount - 1 ? "" : ", ");
    printf("] ## [");
    
    for (int i = 0; i < jogo->developerCount; i++) printf("%s%s", jogo->developers[i], i == jogo->developerCount - 1 ? "" : ", ");
    printf("] ## [");
    
    for (int i = 0; i < jogo->categoryCount; i++) printf("%s%s", jogo->categories[i], i == jogo->categoryCount - 1 ? "" : ", ");
    printf("] ## [");
    
    for (int i = 0; i < jogo->genreCount; i++) printf("%s%s", jogo->genres[i], i == jogo->genreCount - 1 ? "" : ", ");
    printf("] ## [");
    
    for (int i = 0; i < jogo->tagCount; i++) printf("%s%s", jogo->tags[i], i == jogo->tagCount - 1 ? "" : ", ");
    printf("] ##\n");
}

//LIBERA MEMÓRIA
void freeGame(Game* jogo)
{
    free(jogo->name);
    free(jogo->releaseDate);

    if (jogo->supportedLanguages) 
    {
        for (int i = 0; i < jogo->languageCount; i++) 
            free(jogo->supportedLanguages[i]);
        free(jogo->supportedLanguages);
    }

    if (jogo->publishers)
    {
        for (int i = 0; i < jogo->publisherCount; i++) 
            free(jogo->publishers[i]);
        free(jogo->publishers);
    }

    if (jogo->developers)
    {
        for (int i = 0; i < jogo->developerCount; i++) 
            free(jogo->developers[i]);
        free(jogo->developers);
    }

    if (jogo->categories)
    {
        for (int i = 0; i < jogo->categoryCount; i++) 
            free(jogo->categories[i]);
        free(jogo->categories);
    }

    if (jogo->genres)
    {
        for (int i = 0; i < jogo->genreCount; i++) 
            free(jogo->genres[i]);
        free(jogo->genres);
    }

    if (jogo->tags)
    {
        for (int i = 0; i < jogo->tagCount; i++) 
            free(jogo->tags[i]);
        free(jogo->tags);
    }

    free(jogo);
}

