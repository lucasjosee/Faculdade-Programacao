### Pesquisa Sequencial
A pesquisa é feita a partir da analise sequencial da estrutura, verificando todos os elementos. Um exemplo dessa pesquisa é a manipulação de vetores usando o laço de repetição FOR, com uma variável de parada que vai se ativar ao encontrar o elemento desejado.

### Pesquisa Binaria
Na Pesquisa Binaria, o vetor é dividido ao meio e somente uma das partes são analisadas. Isso é feito até achar o elemento.

Exemplo a seguir:
boolean resp = false;
int dir = n - 1, esq = 0, meio, diferença;
while (esq <= dir)
   {
	meio = (esq + dir) / 2; 
	diferença = (x - array[meio]);
	 if (diferença == 0)
	   { 
		 resp = true; esq = n;
		  } 
		 else if (diferença > 0)
		 { 
		 esq = meio + 1;
		  } 
		  else { dir = meio - 1;
	   }
   }