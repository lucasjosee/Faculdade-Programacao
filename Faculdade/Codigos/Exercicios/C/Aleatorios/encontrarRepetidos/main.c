Celula* encontrarRepetidos(No* raiz, CelulaMatriz* inicio)
{
	CelulaMatriz* atual = inicio;
	Celula* primeiro, ultimo;
	primeiro = ultimo = (Celula*) malloc(sizeof(Celula));
	
	for(CelulaMatriz* i = inicio; i->inf != NULL; i = i->inf)
	{
		for(CelulaMatriz* j = i; j->dir != NULL; j = j->dir)
		{
			if(pesquisarArvore(raiz, i->elemento))
			{
				Celula temp = (Celula*) malloc(sizeof(Celula));
				temp->elemento = i->elemento;
				temp->prox = primeiro->prox;
				primeiro->prox = temp;
				if(primeiro == ultimo)
				{
					ultimo = temp;
				}
				temp == NULL;
			}
		}
	}
	ordenarDescrescente(primeiro, ultimo);
	return primeiro;
}

void ordenarDecrescente(Celula* primeiro, Celula* ultimo)
{
	for(Celula* i = primeiro->prox; i->prox != ultimo; i = i->prox)
	{
		for(Celula* j = primeiro->prox; j != NULL; j = j->prox)
		{
			if(i->elemento < j->elemento)
			{
				int temp = i->elemento;
				i->elemento = j->elemento;
				j->elemento = temp;
			}
		}
	}
}

bool pesquisarArvore(No* raiz, int n)
{
	if(raiz == NULL)
	{
		return false;
	}
	if(raiz->elemento == n)
	{
		return true;
	}
	if(n < raiz->elemento)
	{
		return pesquisarArvore(raiz->esq, n);
	}
	return pesquisarArvore(raiz->dir, n);
}
