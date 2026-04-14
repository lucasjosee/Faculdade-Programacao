
### Funcionamento

O `sscanf` extrai dados de uma string já existente baseando-se em um formato. **Retorno:** Quantidade de itens lidos com sucesso. Sempre verifique `if (sscanf(...) == total_esperado)`.

### Tabela de Formatos (Tokens)

- `%d`: Inteiro (ID, idade).
    
- `%f`: Float (Preço, peso).
    
- `%[^,]`: Lê tudo até a vírgula (Scanset). Essencial para strings com espaços.
    
- `%*[^,]`: Lê e ignora o conteúdo até a vírgula (Pula coluna).
    
- `%99[^,]`: Lê até 99 caracteres (Segurança contra Buffer Overflow).
    

### Exemplo de Aplicação

Para a linha: `10,Teclado Mecanico,250.00`

C

```
int id;
char produto[100];
float preco;

// %d      -> ID
// ,       -> Pula vírgula literal
// %99[^,] -> Nome (até 99 chars ou até a vírgula)
// ,       -> Pula vírgula literal
// %f      -> Preço
sscanf(linha, "%d,%99[^,],%f", &id, produto, &preco);
```

### Casos Especiais

- **Pular Coluna:** `sscanf(linha, "%d, %*[^,], %f", &id, &preco);` (Ignora o nome do produto).
    
- **Separador Ponto-e-Vírgula:** Basta trocar o caractere no scanset: `%[^;];`.
    
- **Ignorar Espaços:** Um espaço antes do `%` na máscara ignora espaços em branco/tabs na string original: `"%d , %f"`.