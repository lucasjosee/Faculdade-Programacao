class hash
{
    int[] tabela;
    int tamTabela;

    public hash(int tamanho)
    {
        tabela = new int[tamanho]; //Considerando que foi inicializado com -1
        tamTabela = tamanho;
    }

    public void inserir(int num)
    {
        int chave = hash(num);

        if(tabela[chave] == -1)
            tabela[chave] = num;
        else
        {
            int chaveRehash = rehash(chave);
            if(tabela[chaveRehash] == -1)
                tabela[chaveRehash] = num;
            else
                System.out.println("Erro ao inserir, posição cheia");
        }
    }

    boolean pesquisar(int num)
    {
        int chave = hash(num);
        if(tabela[chave] == num)
            return true;
        else
        {
            int chaveRehash = rehash(chave);
            if(tabela[chaveRehash] == num)
                return true;
            else
                return false;
        }
    }

    //Remover -- preguiça de implementar

    int hash(int x)
    {
        return x % tamTabela; 
    }

    int rehash(int x)
    {
        return ++x % tamTabela;
    }   
}
