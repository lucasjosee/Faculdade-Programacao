# Faculdade-Programacao

Repositório com todo o material produzido durante minha jornada de aprendizado em programação — exercícios, trabalhos práticos, anotações teóricas e projetos de cursos online.

## Estrutura

```
.
├── courses/          # Cursos online
│   ├── cs50x/        # Harvard CS50x (C)
│   └── frontend/     # Desenvolvimento Web (HTML, CSS, JS)
│
├── university/       # Disciplinas da faculdade
│   └── 2025-2/
│       ├── aeds-2/                    # Algoritmos e Estruturas de Dados II
│       ├── arquitetura-computadores/  # Arquitetura de Computadores I
│       ├── arquitetura-computadores-2/# Arquitetura de Computadores II
│       ├── engenharia-software/       # Engenharia de Software
│       └── processo-seletivo-webtech/ # Processo Seletivo WebTech
│
└── projects/         # Projetos pessoais
```

## Cursos Online

### CS50x — Harvard (C)
Semanas 0 a 4 do curso introdutório de Ciência da Computação da Harvard.

| Semana | Tópico | Exercícios |
|--------|--------|-----------|
| 0 | Scratch | `week-0/` |
| 1 | C — fundamentos | `credit`, `hello`, `mario-more` |
| 2 | Arrays e strings | `readability`, `scrabble`, `substitution` |
| 3 | Algoritmos | `plurality`, `tideman` |
| 4 | Memória e arquivos | `filter-less`, `recover`, `volume` |

### Frontend
Exercícios progressivos de HTML/CSS (`ex-01` a `ex-06`) e sandbox de JavaScript.

---

## Faculdade — Semestre 2025/2

### AEDS-2 — Algoritmos e Estruturas de Dados II
Principal disciplina do semestre. Implementações em **C** e **Java**.

**Estruturas de dados implementadas:**
- Lista simples e dupla
- Pilha (estática e flexível)
- Matriz (estática e flexível)
- Árvore binária
- Pesquisa binária

**Algoritmos de ordenação:**
- InsertionSort, QuickSort, HeapSort, ShellSort

**Organização interna:**
```
aeds-2/
├── estruturas-dados/   # Implementações das estruturas
├── exercicios/
│   ├── aleatorios/     # Exercícios variados (C e Java)
│   ├── beecrowd/       # Problemas do Beecrowd (C e Java)
│   ├── exercicios-de-prova/
│   └── trabalhos-praticos/  # TP1 e TP2
├── laboratorios/       # Labs 01, 02 e 03
├── sorts/              # Implementações de ordenação
├── unidade-1/          # Complexidade e análise de algoritmos
├── unidade-3/          # Algoritmos de ordenação avançados
├── unidade-4/          # Árvores
├── unidade-5/
├── oficina-pc/         # Matemática Discreta
└── funcoes-uteis/      # Referências e funções auxiliares
```

### Arquitetura de Computadores I
Anotações teóricas em Markdown sobre:
- Sistemas de numeração e representação de dados
- Álgebra Booleana e simplificação de expressões
- Operações aritméticas em binário
- Representação fracionária e complementos

### Arquitetura de Computadores II
Atividade prática com implementação de uma ULA em C e emulação em Arduino.

### Engenharia de Software
Anotações sobre UML, diagramas de classe, casos de uso, MER, modelos ágeis e tradicionais.

---

## Linguagens utilizadas

| Linguagem | Uso |
|-----------|-----|
| C | CS50x, AEDS-2 (estruturas e exercícios) |
| Java | AEDS-2 (estruturas e exercícios) |
| HTML/CSS | Curso Frontend |
| JavaScript | Sandbox Frontend |
| Arduino (C++) | Arquitetura de Computadores II |

---

## Convenções do repositório

- Nomes de pastas em `kebab-case`
- Arquivos compilados (`.exe`, `.class`, `.o`) não são versionados
- Anotações teóricas em Markdown junto ao código da unidade correspondente
