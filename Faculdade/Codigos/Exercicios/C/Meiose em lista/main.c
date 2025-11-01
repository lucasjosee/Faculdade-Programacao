void meiose()
{
	Celula* temp;
	for(Celula* i = inicio; i != NULL && i->prox != NULL; i = i->prox->prox)
	{
		temp = (Celula*) malloc(sizeof(Celula));
		
		temp->elemento = i->elemento / 2;
		i->elemento = i->elemento / 2;
		
		temp->prox = i->prox;
		i->prox =  temp;
		
		fim = temp;
		
		temp = NULL;	
	}
}
