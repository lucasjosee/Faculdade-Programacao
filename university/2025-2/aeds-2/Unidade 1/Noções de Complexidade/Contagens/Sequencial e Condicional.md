
### Contagem Condicional
Corresponde ao custo da condição mais o custo de uma das listas (verdadeira/falsa).
if(condição()) 
{
	listaVerdadeira();
}
else
{
	listaFalsa();
}
##### Melhor caso: Condição() + mínimo(listaVerdadeiro(), listaFalsa())
##### Pior caso: Condição + máximo(listaVerdadeiro(), listaFalsa())
