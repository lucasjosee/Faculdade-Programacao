//Aluno: Lucas José Souza Rodrigues
//Ex: Inversão de string - TP 2

import java.util.Scanner;
public class inversaodeString 
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String palavra;
        String fim = "FIM"; //String para comparar com a entrada e parar o codigo
        boolean a = false; //Se a for true o codigo para

        while(true)
        {
            palavra = sc.nextLine();

            for(int i = 0; i < fim.length(); i++) //Verificando se a palavra FIM (comando de parada) foi digitada
            {
                if(palavra.charAt(i) == fim.charAt(i))
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
            
            char[] invertidaArray = new char[palavra.length()]; //Criando o array de char para colocar a string invertida

            for(int i = 0; i < palavra.length(); i++)
            {
                invertidaArray[i] = palavra.charAt(palavra.length() - 1 - i); //invertendo a string e manipulando ela com com o charAt
            }

            String invertida = new String(invertidaArray); //Tranformando o array de char em string

            System.out.println(invertida);
        }
        
        
    }   
}
