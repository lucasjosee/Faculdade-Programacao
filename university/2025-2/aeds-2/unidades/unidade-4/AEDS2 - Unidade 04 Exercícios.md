# AEDS2 — Unidade 04: Estruturas de Dados Básicas Flexíveis

> Exercícios extraídos dos slides da Unidade 04 de Algoritmos e Estruturas de Dados II (PUC Minas).

---

## 04a — Introdução (TAD Flexível)

- [ ] Crie a classe `Celula` com atributos **privados** `elemento` (int) e `prox` (Celula), com métodos get e set
- [ ] Mostre o que acontece ao executar `Celula tmp = new Celula(3)`
- [ ] Mostre o que acontece ao executar `Celula tmp = new Celula()`

---

## 04b — Pilha Flexível

- [ ] **(1)** Método **iterativo** que retorna a **soma** dos elementos da pilha
- [ ] **(2)** Método **recursivo** que retorna a **soma** dos elementos da pilha
- [ ] **(3)** Método **iterativo** que retorna o **maior elemento** da pilha
- [ ] **(4)** Método **recursivo** que retorna o **maior elemento** da pilha
- [ ] **(5)** Método **recursivo** para mostrar os elementos na **ordem de remoção** (topo → fundo)
- [ ] **(6)** Método **recursivo** para mostrar os elementos na **ordem de inserção** (fundo → topo)
- [ ] **(7)** Método **iterativo** para mostrar os elementos na **ordem de inserção**
- [ ] **(8)** Dadas as ilustrações do construtor e do `inserir`, escreva o código completo da classe `Pilha`

---

## 04c — Fila Flexível

- [ ] **(1)** Método para retornar o **terceiro elemento** (supondo que existe)
- [ ] **(2)** Método que **soma** o conteúdo dos elementos da fila
- [ ] **(3)** Método que **inverte** a ordem dos elementos da fila
- [ ] **(4)** Método **recursivo** para contar elementos **pares E múltiplos de 5**
- [ ] **(5)** Mostre **graficamente** a execução do `metodoDoidao()` com a fila contendo `[5, 10, 15, 20, 25]`
- [ ] **(6)** Implemente `Celula toFila(Celula topo)` — converte uma pilha em fila (na ordem de inserção, sem destruir a pilha)
- [ ] **(7)** Implemente a **fila flexível sem nó cabeça**
- [ ] **(8)** Implemente a **pilha flexível com nó cabeça**

---

## 04d — Lista Simples

- [ ] **(1)** Implemente um método que **remove a segunda posição válida** (siga os 6 passos ilustrados no slide 57)
- [ ] **(2)** Crie a classe **`ListaSimplesEncadeadaOrdenada`** garantindo que os elementos sempre fiquem ordenados após inserção

---

## 04e — Lista Dupla

- [ ] **(1)** Execute graficamente o **remover no início** com lista `[3, 5, 7]`
- [ ] **(2)** Execute graficamente o **remover no fim** com lista `[3, 5, 7]`
- [ ] **(3)** Execute graficamente o **inserir(6, 2)** com lista `[3, 5, 7]`
- [ ] **(4)** Execute graficamente o **remover(1)** com lista `[3, 5, 7]`
- [ ] **(5)** Implemente o **mostrar** e execute com lista `[3, 5, 7]`
- [ ] **(6)** Método que **inverta** os elementos da **lista dupla** (ex: `[5,4,3,2,1]` → `[1,2,3,4,5]`)
- [ ] **(7)** Método que **inverta** os elementos da **lista simples**
- [ ] **(8)** Implemente **Shellsort** na **lista dupla**
- [ ] **(9)** Implemente **Shellsort** na **lista simples**
- [ ] **(10)** Implemente **Quicksort** na **lista dupla**
- [ ] **(11)** Implemente **Quicksort** na **lista simples**

---

## 04f — Matriz Flexível

> Sem exercícios explícitos. Estrutura usa célula com 4 ponteiros: `esq`, `dir`, `inf`, `sup`.

---

## 04g — Coleta de Lixo

- [ ] **(1)** Compile e execute `ColetaLixo.java`; monitore com `top` — observe que a JVM mantém memória estável graças ao GC
- [ ] **(2)** Compile e execute `coletalixo.c` (`gcc coletalixo.c -o coletalixo`); compare com Java — memória estável pois C faz `malloc` + `free`
- [ ] **(3)** Comente o `free(tmp)` no `coletalixo.c`, recompile e observe o consumo de memória crescer rapidamente ⚠️ *Cuidado: pode travar a máquina — pressione CTRL+C imediatamente*

---

## 04h / 04i — TAD em C e TADs Nativos em Java

> Sem exercícios explícitos. Conteúdo teórico sobre `Stack`, `Queue`, `ArrayList`, `Vector`, `LinkedList`.

---

## Tags

#aeds2 #estruturas-de-dados #java #pilha #fila #lista #pucminas
