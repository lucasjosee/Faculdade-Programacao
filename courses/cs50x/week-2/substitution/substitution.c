#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool hasLetters(string key);
bool hasEquals(string key);
string criptography(string key, string plainText);

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Erro! Digite ao menos um parametro\n");
        return 1;
    }

    if (argc > 2)
    {
        printf("Erro! Muitos argumentos.\n");
        return 1;
    }

    string key = argv[1];
    int tamanhoKey = strlen(key);
    if (tamanhoKey < 26 || tamanhoKey > 26)
    {
        printf("Erro! Key deve conter 26 letras.\n");
        return 1;
    }

    if (hasLetters(key) == false)
    {
        printf("Erro! A key deve conter apenas letras.\n");
        return 1;
    }

    if (hasEquals(key))
    {
        printf("Erro! A key não pode conter letras iguais.\n");
        return 1;
    }

    string plainText = get_string("plaintext: ");

    string result = criptography(key, plainText);

    printf("ciphertext: %s\n", result);
}

string criptography(string key, string plainText)
{
    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(plainText); i++)
    {
        for (int j = 0; j < strlen(alfabeto); j++)
        {
            if (plainText[i] == alfabeto[j] || plainText[i] == alfabeto[j] + 32)
            {
                if (plainText[i] == alfabeto[j] + 32)
                {
                    if (key[j] >= 'a' && key[j] <= 'z')
                    {
                        plainText[i] = key[j];
                        break;
                    }
                    else
                    {
                        plainText[i] = key[j] + 32;
                        break;
                    }
                }

                if (plainText[i] >= 'A' && plainText[i] <= 'Z')
                {
                    if (key[j] >= 'a' && key[j] <= 'z')
                    {
                        plainText[i] = key[j] - 32;
                        break;
                    }
                }

                plainText[i] = key[j];
                break;
            }
        }
    }

    return plainText;
}

bool hasEquals(string key)
{
    for (int i = 0; i < strlen(key) - 1; i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j] || key[i] + 32 == key[j])
            {
                return true;
            }
        }
    }
    return false;
}

bool hasLetters(string key)
{
    bool a = true;
    for (int i = 0; key[i] != '\0'; i++)
    {
        if ((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z'))
        {
            a = true;
        }
        else
        {
            a = false;
            break;
        }
    }
    return a;
}
