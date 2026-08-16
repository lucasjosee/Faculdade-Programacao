int contarPalavras(char primeiro, char ultimo)
{   
    No alvo = buscarPrimeiro(primeiro);
    if(alvo == null) return 0;

    int cont = contarUltimo(alvo.raiz, ultimo);

    return cont;
}

public int contarUltimo(No2 root, char ultimo)
{
    int cont = 0;
    if(root == null) return 0;
    
    if(root.palavra.charAt(root.palavra.length() - 1) == ultimo)
        cont++;

    cont += contarUltimo(root.esq, ultimo);
    cont += contarUltimo(root.dir, ultimo);

    return cont;
}

public No buscarPrimeiro(char primeiro)
{
    return buscarPrimeiro(this.raiz, primeiro);
}

No buscarPrimeiro(No root, char alvo)
{
    if(root == null) return null;

    if(root.letra == alvo)
        return root;
    else if(alvo < root.letra)
        return buscarPrimeiro(root.esq, alvo);
    else
        return buscarPrimeiro(root.dir, alvo);

}
