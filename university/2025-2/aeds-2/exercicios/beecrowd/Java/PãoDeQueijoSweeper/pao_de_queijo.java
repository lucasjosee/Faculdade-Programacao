import java.util.Scanner;

public class pao_de_queijo
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        while(sc.hasNextInt())
        {
            int n, m;
            n = sc.nextInt();
            m = sc.nextInt();

            int matriz[][] = new int[n][m];

            lerMatriz(matriz, n, m, sc);    

            paodequeijo(matriz, n, m);

            imprimir(matriz, n, m);
        }
    }

    
    public static void paodequeijo(int matriz[][], int n, int m)
    {
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(matriz[i][j] == 0)
                {
                    int cont = 0;
                    for(int k = 0; k < 4; k++)
                        {
                            int vizinhoI = i + dx[k];
                            int vizinhoJ = j + dy[k];

                            if(vizinhoI >= 0 && vizinhoI < n && vizinhoJ >= 0 && vizinhoJ < m)
                            {
                                if(matriz[vizinhoI][vizinhoJ] == 9)
                                {
                                    cont++;
                                }
                            }
                        }
                        matriz[i][j] = cont;
                }
            }
        }
    }

    public static void imprimir(int matriz[][], int n, int m)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                System.out.print(matriz[i][j]);
            }
            System.out.println();
        }
    }

    public static void lerMatriz(int matriz[][], int n, int m, Scanner sc)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int aux = sc.nextInt();
                if(aux == 1)
                {
                    matriz[i][j] = 9;
                }
                else
                {
                    matriz[i][j] = 0;
                }
            }
        }
    }
}
