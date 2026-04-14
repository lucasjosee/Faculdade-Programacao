/* 
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q8
*/  

import java.util.Scanner;

public class validacao_senha
{
     public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        
        String linha = sc.nextLine();

        while(!isFIM(linha))
        {
            if(hasTam(linha) && hasMaiusc(linha) && hasMinusc(linha) && hasEspecial(linha) && hasNum(linha)) //Caso todos as funções de verificacao retornarem true, mostrara sim na tela
            {                                                                            
                System.out.println("SIM");
            }
            else //Caso alguma for falso mostrara nao na tela
            {
                System.out.println("NAO");
            }
            linha = sc.nextLine();
        }

        sc.close();
    }

    /*
     * Funções de verificação da senha, se houver ao menos dos caracteres obrigatorios
     * elas retornam true
    */
    static boolean hasEspecial(String s)
    {
        for(int i = 0; i < s.length(); i++)
        {
            if((s.charAt(i) >= '!' && s.charAt(i) <= '/') || (s.charAt(i) >= ':' && s.charAt(i) <= '@')
                    || (s.charAt(i) >= '{' && s.charAt(i) <= '~') || (s.charAt(i) >= '[' && s.charAt(i) <= '`')) return true;
        }
        return false;
    }

    static boolean hasNum(String s)
    {
        for(int i = 0; i < s.length(); i++)
        {
            if(s.charAt(i) >= '0' && s.charAt(i) <= '9') return true;
        }
        return false;
    }

    static boolean hasMinusc(String s)
    {
        for(int i = 0; i < s.length(); i++)
        {
            if(s.charAt(i) >= 'a' && s.charAt(i) <= 'z') return true;
        }
        return false;
    }

    static boolean hasMaiusc(String s)
    {
        for(int i = 0; i < s.length(); i++)
        {
            if(s.charAt(i) >= 'A' && s.charAt(i) <= 'Z') return true;
        }
        return false;
    }

    static boolean hasTam(String s)
    {
        if(s.length() >= 8) return true;

        return false;
    }

    public static boolean isFIM(String s) //Função que ira parar o programa caso a palavra lida seja FIM
    {
        if(s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M')
        {
            return true;
        }
        return false;
    }
}
