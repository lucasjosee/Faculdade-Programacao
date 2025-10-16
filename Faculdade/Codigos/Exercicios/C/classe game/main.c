#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_SIZE 4096
#define MAX_FIELD_SIZE 2048
#define MAX_ARRAY_SIZE 150

typedef struct {
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

char* proximoCampo(char* linha, int* pos);
char* formatarData(const char* dataStr);
char** stringParaArray(const char* s, int* count);
char* trim(char *str);
int stringParaInt(const char* s);
float stringParaFloat(const char* s);
void mostrar(Game* jogo);
void freeGame(Game* jogo);

int main() {
    char idDeEntrada[20];

    while (fgets(idDeEntrada, sizeof(idDeEntrada), stdin) != NULL) {
        idDeEntrada[strcspn(idDeEntrada, "\n")] = 0;
        if (strcmp(idDeEntrada, "FIM") == 0) {
            break;
        }

        int idParaBuscar = stringParaInt(idDeEntrada);

        FILE* file = fopen("/tmp/games.csv", "r");
        if (file == NULL) {
            perror("Erro ao abrir o arquivo GAMES.CSV");
            return 1;
        }

        char linha[MAX_LINE_SIZE];
        fgets(linha, MAX_LINE_SIZE, file);

        while (fgets(linha, MAX_LINE_SIZE, file)) {
            linha[strcspn(linha, "\n")] = 0;
            int pos = 0;
            char* idStr = proximoCampo(linha, &pos);
            int idAtual = stringParaInt(idStr);
            free(idStr);

            if (idAtual == idParaBuscar) {
                Game jogo;
                jogo.id = idAtual;
                jogo.name = proximoCampo(linha, &pos);
                
                char* dataStr = proximoCampo(linha, &pos);
                jogo.releaseDate = formatarData(dataStr);
                free(dataStr);

                char* donosStr = proximoCampo(linha, &pos);
                jogo.estimatedOwners = stringParaInt(donosStr);
                free(donosStr);
                
                char* precoStr = proximoCampo(linha, &pos);
                jogo.price = strcmp(precoStr, "Free to Play") == 0 ? 0.0f : stringParaFloat(precoStr);
                free(precoStr);

                char* linguasStr = proximoCampo(linha, &pos);
                jogo.supportedLanguages = stringParaArray(linguasStr, &jogo.languageCount);
                free(linguasStr);

                char* metaScoreStr = proximoCampo(linha, &pos);
                jogo.metacriticScore = stringParaInt(metaScoreStr);
                free(metaScoreStr);

                char* userScoreStr = proximoCampo(linha, &pos);
                jogo.userScore = strcmp(userScoreStr, "tbd") == 0 ? -1.0f : stringParaFloat(userScoreStr);
                free(userScoreStr);

                char* conquistasStr = proximoCampo(linha, &pos);
                jogo.achievements = stringParaInt(conquistasStr);
                free(conquistasStr);
                
                char* publishersStr = proximoCampo(linha, &pos);
                jogo.publishers = stringParaArray(publishersStr, &jogo.publisherCount);
                free(publishersStr);

                char* developersStr = proximoCampo(linha, &pos);
                jogo.developers = stringParaArray(developersStr, &jogo.developerCount);
                free(developersStr);

                char* categoriesStr = proximoCampo(linha, &pos);
                jogo.categories = stringParaArray(categoriesStr, &jogo.categoryCount);
                free(categoriesStr);

                char* genresStr = proximoCampo(linha, &pos);
                jogo.genres = stringParaArray(genresStr, &jogo.genreCount);
                free(genresStr);

                char* tagsStr = proximoCampo(linha, &pos);
                jogo.tags = stringParaArray(tagsStr, &jogo.tagCount);
                free(tagsStr);

                mostrar(&jogo);
                freeGame(&jogo);
                break;
            }
        }
        fclose(file);
    }
    return 0;
}


char* proximoCampo(char* linha, int* pos) {
    char* campo = (char*)malloc(MAX_FIELD_SIZE * sizeof(char));
    int i = *pos;
    int j = 0;

    if (i >= strlen(linha)) {
        strcpy(campo, "");
        return campo;
    }

    if (linha[i] == '"') {
        i++;
        while (i < strlen(linha) && linha[i] != '"') {
            campo[j++] = linha[i++];
        }
        i++;
    } else {
        while (i < strlen(linha) && linha[i] != ',') {
            campo[j++] = linha[i++];
        }
    }
    
    if (i < strlen(linha) && linha[i] == ',') {
        i++;
    }

    campo[j] = '\0';
    *pos = i;
    return campo;
}

char* formatarData(const char* dataStr) {
    char* dataFormatada = (char*)malloc(11 * sizeof(char));
    char mesStr[4] = "Jan";
    int dia = 1, ano = 2000;

    if (strlen(dataStr) > 4) {
        sscanf(dataStr, "%s %d, %d", mesStr, &dia, &ano);
    } else if (strlen(dataStr) > 0) {
        sscanf(dataStr, "%d", &ano);
    }
    
    int mesNum = 0;
    const char* meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; i++) {
        if (strcmp(mesStr, meses[i]) == 0) {
            mesNum = i + 1;
            break;
        }
    }
    if (mesNum == 0) mesNum = 1;
    sprintf(dataFormatada, "%02d/%02d/%d", dia, mesNum, ano);
    return dataFormatada;
}

char* trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

char** stringParaArray(const char* s, int* count) {
    *count = 0;
    if (s == NULL || strlen(s) == 0) return NULL;

    char** array = (char**)malloc(MAX_ARRAY_SIZE * sizeof(char*));
    char temp[MAX_FIELD_SIZE];
    strcpy(temp, s);
    
    if (temp[0] == '[' && strchr(temp, '\'')) {
        char palavra[MAX_FIELD_SIZE];
        int palavraPos = 0;
        int dentroDeAspas = 0;
        for (int i = 0; i < strlen(temp); i++) {
            if (temp[i] == '\'') {
                dentroDeAspas = !dentroDeAspas;
                if (!dentroDeAspas && palavraPos > 0) {
                    palavra[palavraPos] = '\0';
                    array[*count] = strdup(palavra);
                    (*count)++;
                    palavraPos = 0;
                }
            } else if (dentroDeAspas) {
                palavra[palavraPos++] = temp[i];
            }
        }
    } else {
        char* token = strtok(temp, ",");
        while (token != NULL) {
            char* trimmed_token = trim(token);
            if(strlen(trimmed_token) > 0) {
                array[*count] = strdup(trimmed_token);
                (*count)++;
            }
            token = strtok(NULL, ",");
        }
    }
    return array;
}

int stringParaInt(const char* s) {
    if (s == NULL || strlen(s) == 0) return 0;
    return atoi(s);
}

float stringParaFloat(const char* s) {
    if (s == NULL || strlen(s) == 0) return 0.0f;
    return atof(s);
}

void mostrar(Game* jogo) {
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

void freeGame(Game* jogo) {
    free(jogo->name);
    free(jogo->releaseDate);
    if(jogo->languageCount > 0) {
        for (int i = 0; i < jogo->languageCount; i++) free(jogo->supportedLanguages[i]);
        free(jogo->supportedLanguages);
    }
    if(jogo->publisherCount > 0) {
        for (int i = 0; i < jogo->publisherCount; i++) free(jogo->publishers[i]);
        free(jogo->publishers);
    }
    if(jogo->developerCount > 0) {
        for (int i = 0; i < jogo->developerCount; i++) free(jogo->developers[i]);
        free(jogo->developers);
    }
    if(jogo->categoryCount > 0) {
        for (int i = 0; i < jogo->categoryCount; i++) free(jogo->categories[i]);
        free(jogo->categories);
    }
    if(jogo->genreCount > 0) {
        for (int i = 0; i < jogo->genreCount; i++) free(jogo->genres[i]);
        free(jogo->genres);
    }
    if(jogo->tagCount > 0) {
        for (int i = 0; i < jogo->tagCount; i++) free(jogo->tags[i]);
        free(jogo->tags);
    }
}