#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Erro: digite o comando corretamente.\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // variavel buffer para armazenar a imagem
    uint8_t buffer[512];

    char nameImg[8];
    int cont = 0;
    FILE *output = NULL;

    // Lendo cada block do raw
    while (fread(buffer, 1, 512, raw) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // True quando o primeiro block é o header/inicio de uma imagem
        {
            if (output != NULL)
            {
                fclose(output);
            }

            sprintf(nameImg, "%03i.jpg", cont); //Atribuindo um nome a proxima imagem que será gravada
            output = fopen(nameImg, "w");
            cont++;
        }
        if (output != NULL)
        {
            fwrite(buffer, 1, 512, output);
        }
    }
    fclose(raw);

    if (output != NULL)
    {
        fclose(output);
    }
}
