public int contarPalavras(String padrao)
{
    char letra = padrao.charAt(0);
    No letraAlvo = acharLetra(this.root, letra);
    if(letraAlvo == null) return 0;
    int tam = padrao.length();
    int cont = contarPalavras(letraAlvo.raiz, tam);
}

public int contarPalavras(No2 root, int tam)
{
    if(root == null)
        return 0;

    int cont = 0;
    if(root.palavra.length() == tam) 
        cont++;
    cont += contarPalavras(root.esq, tam);
    cont += contarPalavras(root.dir, tam);

    return cont;
    
}

public No acharLetra(No root, char letra)
{
    if(root == null) 
        return null;

    No resp = null;
    if(root.letra == letra)
        resp = root;
    else if(letra < root.letra)
        resp = acharLetra(root.esq, letra);
    else if(letra > root.letra)
        resp = acharLetra(root.dir, letra);

    return resp;
}
