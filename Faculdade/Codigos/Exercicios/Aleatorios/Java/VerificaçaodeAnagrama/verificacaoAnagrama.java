//Aluno: Lucas José Souza Rodrigues
//Ex: VErificação de Anagrama - TP 2

import java.util.Scanner;

class anagrama
{
  public boolean teste(String primeira, String segunda) 
    {
        if (primeira.length() != segunda.length()) //Se as Strings tiverem tamanho diferente, não é anagrama
        {
            return false;
        }

        int[] freq = new int[256]; //Vetor que vai armazenar cada caractere da string para verificar se as letras das strings possuem a mesma quantidade 

        for (int i = 0; i < primeira.length(); i++) 
        {
            char c1 = primeira.charAt(i);
            char c2 = segunda.charAt(i);

            if (c1 >= 'A' && c1 <= 'Z') c1 = (char)(c1 + 32); //Transformando todas as letras em minusculas
            if (c2 >= 'A' && c2 <= 'Z') c2 = (char)(c2 + 32);

            freq[c1]++;
            freq[c2]--;
        }

        for (int f : freq) //Percorre todo o vetor freq e se não ouver diferença é um anagrama
        {
            if (f != 0) return false;
        }
        return true;
    }


}


public class verificacaoAnagrama
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String fim = "FIM"; //String para comparar com a entrada e parar o codigo
        boolean a = false; //Se a for true o codigo para

        anagrama an = new anagrama();

        while(true)
        {
            String primeira = "";
            String segunda = "";
            String linhaInteira = sc.nextLine();
            

            int posicao = -1;

            for(int i = 0; i < fim.length(); i++) //Verificando se a palavra FIM (comando de parada) foi digitada
            {
                if(linhaInteira.charAt(i) == fim.charAt(i))
                {
                    a = true;
                }
                else
                {
                    a = false;
                }
            }

            if(a == true)
            {
                System.exit(0);
            }

            for(int i = 0; i < linhaInteira.length(); i++) //Pegando a posição do caractere -
            {
                if(linhaInteira.charAt(i) == '-')
                {
                    posicao = i;
                    break;
                }
            }

            for(int i = 0; i < posicao; i++) //Separando a string linhaInteira e colocando a primeira parte em outra string
            {
                if(linhaInteira.charAt(i) != ' ' && linhaInteira.charAt(i) != '-')
                {
                    primeira += linhaInteira.charAt(i);

                }
            }

            for(int i = posicao + 1; i < linhaInteira.length(); i++) //colocando a segunda parte em outra string
            {
                if(linhaInteira.charAt(i) != ' ' && linhaInteira.charAt(i) != '-') 
                {
                    segunda += linhaInteira.charAt(i);
                }
            }

            if(an.teste(primeira, segunda)) //testando se é anaframa
            {
                System.out.println("SIM");
            }
            else
            {
                System.out.println("N\u00C3O");
            }
        }
        
    }
}