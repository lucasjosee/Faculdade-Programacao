import os
import glob
import re

verde_replacements = [
    (r"// Mostrar TODOS os elementos para o Verde validar os swaps parciais", r"// Exibe a listagem completa dos elementos finais"),
    (r"// Mostrar TODOS os elementos para o Verde validar", r"// Exibe a listagem completa dos elementos finais"),
    (r"// Funcao de atalho para instanciar a colecao apontando direto para a pasta tmp do Verde", r"// Popula a colecao baseando-se no arquivo de dados padrao"),
    (r"// Imprimir TODOS os elementos do array. O Verde exige a impressao do array\s+// inteiro para validar como o resto do array foi afetado pela insercao parcial.", r"// Imprime toda a extensao do array para visualizacao do resultado final"),
    (r"// Imprimir TODOS os elementos do array. O Verde exige a impressao do array\s+// inteiro para validar como o resto do array foi afetado pela ordenacao parcial.", r"// Imprime toda a extensao do array para visualizacao do resultado final"),
    (r"// Se vier com carriage return, remove", r"// Remove o carriage return (\\r) se existir no final da string para evitar problemas de leitura")
]

c_comments = [
    (r"^(void swap\()", r"// Realiza a troca de posicao entre dois elementos do arranjo\n\1"),
    (r"^(void construir\()", r"// Constroi e ajusta o heap a partir de um no raiz\n\1"),
    (r"^(void gerar_log\()", r"// Exporta as metricas de desempenho para um arquivo texto log\n\1"),
    (r"^(void ler_csv_colecao\()", r"// Le os dados do CSV e instancia os restaurantes\n\1"),
    (r"^(Colecao_Restaurantes\* ler_csv\(\))", r"// Retorna uma colecao de restaurantes preenchida\n\1"),
    (r"^(Restaurante\* parse_restaurante\()", r"// Recebe uma linha CSV, faz a quebra dos atributos e monta a struct do Restaurante\n\1"),
    (r"^(void formatar_restaurante\()", r"// Transforma o restaurante formatado em um display de string para exibicao\n\1"),
    (r"^(Hora parse_hora\()", r"// Extrai hora e minuto de uma string\n\1"),
    (r"^(Data parse_data\()", r"// Extrai ano, mes e dia de uma string\n\1"),
    (r"^(void string_to_array\()", r"// Converte a string de tipos de cozinha para um array de strings\n\1"),
    (r"^(void free_restaurante\()", r"// Libera a memoria alocada para um unico restaurante\n\1"),
    (r"^(void free_colecao\()", r"// Libera toda a colecao e seus restaurantes para evitar memory leaks\n\1"),
    (r"^(Restaurante\* get_restaurante_by_id\()", r"// Faz a varredura linear na colecao para resgatar o restaurante pelo ID\n\1"),
    (r"^(void iniciar\(\))", r"// Inicializa a estrutura de dados e seus ponteiros base\n\1"),
    (r"^(void inserirInicio\()", r"// Aloca e anexa o elemento no inicio da estrutura\n\1"),
    (r"^(void inserirFim\()", r"// Aloca e anexa o elemento no fim da estrutura\n\1"),
    (r"^(void inserir\()", r"// Aloca e anexa o elemento na respectiva posicao da estrutura\n\1"),
    (r"^(Restaurante\* removerInicio\()", r"// Desvincula e retorna o primeiro elemento da estrutura, atualizando os nos\n\1"),
    (r"^(Restaurante\* removerFim\()", r"// Desvincula e retorna o ultimo elemento da estrutura, atualizando os nos\n\1"),
    (r"^(Restaurante\* remover\()", r"// Desvincula e retorna um elemento especifico da estrutura\n\1"),
    (r"^(void mostrar\(\))", r"// Varre a estrutura imprimindo seus elementos na saida padrao\n\1"),
    (r"^(void liberar\(\))", r"// Libera da memoria de forma recursiva os nos alocados na estrutura\n\1"),
    (r"^(int comparar_datas\()", r"// Compara duas structs de Data retornando a diferenca cronologica\n\1"),
    (r"^(No\* novoNo\()", r"// Cria um novo no e aloca sua memoria\n\1"),
    (r"^(No\* inserirRec\()", r"// Chama a insercao de forma recursiva buscando a folha ideal\n\1"),
    (r"^(void pesquisar\()", r"// Inicia o processo de busca imprimindo o caminho percorrido\n\1"),
    (r"^(int pesquisarRec\()", r"// Busca de forma recursiva nos ramos da arvore\n\1"),
    (r"^(void caminharCentral\()", r"// Varre a arvore imprimindo seus elementos na saida padrao\n\1"),
    (r"^(void liberarArvore\()", r"// Libera da memoria de forma recursiva os nos alocados na arvore\n\1")
]

java_comments = [
    (r"^(    public static void swap\()", r"    // Realiza a troca de posicao entre dois elementos do arranjo\n\1"),
    (r"^(    public static void quicksort\()", r"    // Rotinas auxiliares para fracionar e ordenar os vetores usando Quicksort\n\1"),
    (r"^(    public static void iniciar\(\))", r"    // Inicializa a estrutura de dados e seus ponteiros base\n\1"),
    (r"^(    public static void inserir\()", r"    // Aloca e anexa o elemento na respectiva posicao da estrutura\n\1"),
    (r"^(    public static void inserirInicio\()", r"    // Aloca e anexa o elemento no inicio da estrutura\n\1"),
    (r"^(    public static void inserirFim\()", r"    // Aloca e anexa o elemento no fim da estrutura\n\1"),
    (r"^(    public static Restaurante remover\()", r"    // Desvincula e retorna o elemento da estrutura, atualizando os nos\n\1"),
    (r"^(    public static Restaurante removerInicio\()", r"    // Desvincula e retorna o primeiro elemento da estrutura\n\1"),
    (r"^(    public static Restaurante removerFim\()", r"    // Desvincula e retorna o ultimo elemento da estrutura\n\1"),
    (r"^(    public static void mostrar\(\))", r"    // Varre a estrutura imprimindo seus elementos na saida padrao\n\1"),
    (r"^(    public static void pesquisar\()", r"    // Inicia o processo de busca imprimindo o caminho percorrido\n\1"),
    (r"^(    private static boolean pesquisar\()", r"    // Busca de forma recursiva nos ramos da arvore\n\1"),
    (r"^(    public static void caminharCentral\()", r"    // Varre a arvore imprimindo seus elementos na saida padrao\n\1"),
    (r"^(    public static String\[\] stringToArray\()", r"    // Converte a string de tipos de cozinha para um array de strings\n\1"),
    (r"^(    public static Hora parseHora\()", r"    // Extrai hora e minuto de uma string\n\1"),
    (r"^(    public static Data parseData\()", r"    // Extrai ano, mes e dia de uma string\n\1"),
    (r"^(    public static Restaurante parseRestaurante\()", r"    // Recebe uma linha CSV, faz a quebra dos atributos e monta a struct do Restaurante\n\1"),
    (r"^(    public String formatar\(\))", r"    // Transforma o restaurante formatado em um display de string para exibicao\n\1"),
    (r"^(    public void lerCsv\(String path\))", r"    // Le os dados do CSV e instancia os restaurantes\n\1"),
    (r"^(    public static ColecaoRestaurantes lerCsv\(\))", r"    // Popula a colecao baseando-se no arquivo de dados padrao\n\1"),
    (r"^(    public Restaurante getRestauranteById\()", r"    // Faz a varredura linear na colecao para resgatar o restaurante pelo ID\n\1")
]

matriz_comments = [
    (r"^(    public Matriz somar\()", r"    // Realiza a soma de matrizes validando suas dimensoes previamente\n\1"),
    (r"^(    public Matriz multiplicar\()", r"    // Multiplica duas matrizes alocando dinamicamente a matriz resultante\n\1"),
    (r"^(    public void mostrarDiagonalPrincipal\(\))", r"    // Percorre e imprime os elementos da diagonal principal da matriz\n\1"),
    (r"^(    public void mostrarDiagonalSecundaria\(\))", r"    // Percorre e imprime os elementos da diagonal secundaria da matriz\n\1")
]

files_c = glob.glob("tp3_*.c")
files_java = glob.glob("tp3_*.java") + ["Matriz.java"]

for fpath in files_c + files_java:
    with open(fpath, "r") as f:
        content = f.read()
    
    # Run verde string replacements
    for src, dst in verde_replacements:
        content = re.sub(src, dst, content)
        
    # Inject function comments
    lines = content.split('\n')
    new_lines = []
    
    rules = c_comments if fpath.endswith(".c") else java_comments
    if fpath == "Matriz.java":
        rules.extend(matriz_comments)
        
    i = 0
    while i < len(lines):
        line = lines[i]
        matched = False
        
        # Don't add comment if previous line is already a comment
        is_already_commented = False
        if i > 0 and new_lines[-1].strip().startswith("//"):
            is_already_commented = True
            
        for pat, repl in rules:
            if re.match(pat, line):
                if not is_already_commented:
                    # Apply regex replacement for the single line
                    line = re.sub(pat, repl, line)
                break
                
        new_lines.append(line)
        i += 1
        
    with open(fpath, "w") as f:
        f.write('\n'.join(new_lines))
        
print("Comentarios padronizados com sucesso.")
