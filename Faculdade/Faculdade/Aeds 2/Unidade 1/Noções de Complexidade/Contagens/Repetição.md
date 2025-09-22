1. Temos N iterações quando o contador da estrutura de repetição começa com 0, repete enquanto menor que N e é incrementado em uma unidade.
for(int i = 0; i < n; i++)
{
	lista();
}


2. Temos(n - a) quando o contador da estrutura de repetição começa com a, repete enquanto menor que n é incrementado em uma unidade.
for(int i = a; i < n; i++)
{
	lista();
}


3. Corresponde ao custo da condição mais o número de iterações multiplicado pela soma custo da condição e da lista a ser repetida.
while(condição())
{
	lista();
}
##### Custo do While: condição() + n x (lista() + condição()), onde n é o número de vezes que o laço vai ser repetido


4. Corresponde ao número de iterações multiplicado pela soma dos custos da lista a ser repetida e da condição.
do
{
	i++;
	i--;
} while(i < 3);
##### Custo do Do-While: n x (lista() + condição()), onde n é o número de vezes que o laço é repetido.