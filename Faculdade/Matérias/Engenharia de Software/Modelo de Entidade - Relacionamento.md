## **Vantagens**:  
1. Simplicidade.
2. Independe do SGBD a ser utilizado.
3. Mundo real a ser mapeado (minimundo) pode ser visto como um conjunto de entidades e de relacionamentos entre as mesmas.  
4. Desenvolvido para facilitar o projeto de banco de dados.  
5. Especifica “quais” os dados serão representados (O QUE) e não “como” os dados serão armazenados.  
## **Elementos do modelo**:  
### 1. Entidade:
Qualquer objeto, pessoa, lugar, conceito ou “coisa” no mundo real com uma existência própria/independente e sobre a qual seja necessário armazenar informações ou características.

Pode ter existência física:
um rio, uma estrada, um aluno.

Ou conceitual:
um cargo, um curso, um evento.

##### Entidade Fraca:
Depende de outra entidade para existir. É utilizado um retângulo dentro de outro retângulo para representa-lo.

### 2. Relacionamento:
Descreve a associação entre uma ou mais entidades. (ação)

Podem conter atributos que os caracterizam.

##### Relacionamento Dependente:
Utilizamos um losango dentro de outro losango, para representar um relacionamento ligada a uma entidade fraca.

### 3. Atributos:
Características, propriedades ou qualidade especifica que descreve um entidade ou um relacionamento.

Atributos-chaves devem estar sublinhados.

##### Atributo Simples:
Não podem ser separados/quebrados.

##### Atributo Composto:
Pode ser quebrado, exemplo:
Endereço -> Rua, número, bairro, país.

##### Atributo Multivalorado:
Possuem um ou mais valores do mesmo tipo. Exemplo: Telefone pode ser residencial, pessoal, trabalho.

São representados por círculos dentro de círculos.

##### Atributo Derivado:
Não é preciso armazenar no banco de dados, e pode ser calculado através da aplicação. Exemplo: A idade de uma pessoa pode ser calculada com a data de nascimento da pessoa.

Sua representação é ovalada com as linhas pontilhadas.




