### Heap:
O HeapSort como o nome já diz trabalha com uma heap, mais precisamente, com uma max-heap completa. O array que o HeapSort irá ordenar começa do index 1, então precisamos de algo para remover ou isolar o index 0 do nosso array.

Na imagem abaixo podemos ver 3 max-heap, porém, só a primeira e a segunda está completa. Só podemos implementar o HeapSort em heap completa.
![[Pasted image 20251019152116.png]]

A max-heap é organizada de forma decrescente, com o maior número estando no topo da heap.  O nó mais acima é chamado de pai, e as que estão abaixo são chamadas de filhas.

Colocando a heap em um array, a organização ficara "quebrada", e por exemplo, para acharmos a filha-esquerda do pai A, temos que aplicar uma formula no índice do array.

Se um Nó está em i:
1. A filha-esquerda = 2 * i
2. A filha-direita = 2 * i + 1
3. O pai = i / 2

##### Em Java, o índice do array começa em 0, então precisamos fazer um deslocamento nas formulas:
1. filho-esquerdo = 2 * i + 1
2. filho-direito = 2 * i + 2
3. pai = (i-1)/2

Usando essas regras podemos achar as filhas e o pai de cada nó no array.
### Inserção:
Na inserção em uma max-heap, primeiro inserimos na primeira posição livre no array, em seguida comparamos se o pai desse nó é menor ou maior que o nó que queremos inserir. Fazemos isso usando a terceira formula falada anteriormente. Caso o pai for menor que a filha, trocamos os dois e fazemos isso até o pai for maior, ou chegar no index 1.
![[Pasted image 20251019154147.png]]


### Remoção:
A remoção é feita a partir do primeiro nó, o nó cabeça. Depois da remoção, pegamos o ultimo elemento do array e colocamos no nó cabeça, comparamos seus filhos e trocamos o nó cabeça com o maior. A próxima etapa, é comparar os pais de cada nó filho, começando da base.
![[Pasted image 20251019155239.png]]

### Sort:
Agora é aqui que a ordenação realmente começa, e a base dele está no método de remoção. Após remover o nó cabeça, foi liberado um espaço no array. Nesse espaço, que é o ultimo, iremos colocar o número que acabou de ser removido. E ao fazermos isso varias vezes, teremos um array completamente ordenado.

Com base nisso, o HeapSort tem duas etapas: Criar a heap, e remover da heap.

#### Como Criar uma Heap?
Pegamos o array de números a ser ordenados e colocamos o primeiro elemento como o cabeça. Em seguida, comparamos o primeiro filho do nó cabeça que é o filha-esquerda usando a formula dele, se o filho for maior, trocamos. Depois, fazemos esse mesmo processo com a filha-direita. Feitas as comparações, pegamos o próximo elemento do array como alvo de comparação e comparamos seus nós filhos com seus parentes. Depois de fazer isso com todos os elementos do array, teremos nossa max-heap. (Os nós filhos que são comparados com seus parentes, para isso usamos a formula 3: i/2.)


