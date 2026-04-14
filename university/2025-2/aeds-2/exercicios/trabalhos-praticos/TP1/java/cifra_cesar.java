/* 
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q1
*/  

public class cifra_cesar
{
    public static void main(String[] args)
    {
       
        String entrada = MyIO.readLine(); 

        while(!isFIM(entrada)) 
        {
            int tamanho = entrada.length();

            char[] resultado = criptografia(entrada, tamanho);
            
            MyIO.println(new String(resultado)); //Tranforma o char[] em string e imprime

            entrada = MyIO.readLine();
        }
    }

    static char[] criptografia(String palavra, int n)
    {
        char[] result = new char[n]; 

        for(int i = 0; i < n; i++)
        {
            result[i] = (char) (palavra.charAt(i) + 3); //Soma 3 no codigo ascii do caractere 
        }
        return result;
    }

    static boolean isFIM(String e)
    {
        boolean resp = false;
        if(e.length() == 3 && e.charAt(0) == 'F' && e.charAt(1) == 'I' && e.charAt(2) == 'M')
        {
            resp = true;
        }
        return resp;
    }
}
