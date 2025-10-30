# Diagrama de casos de uso:
### Oq é:
Descreve oq um sistema faz, mas não especifica como ele faz. Possui duas partes, o diagrama 
figura ilustrativa das funcionalidades e usuários do sistema e documentação descrição narrativa das interações que ocorrem entre os elementos externos de um sistema.

Casos de uso == Requisito funcional
![[Pasted image 20251029112207.png]]

Ator == Representa qualquer "coisa" que interaja com o sistema.
![[Pasted image 20251029112223.png]]

### Ator:
O ator é um elemento externo ao sistema que interage com este, são classificados com primário e secundário. Representam um conjunto coerente de "papéis" que interagem com o caso de uso ou casos de uso. Podem representar dispositivos de hardware ou sistemas.

Obs: Atores não fazem parte do sistema.

Deve ser conectado a um ou mais casos de Uso.

Representam os papéis assumidos pelos usuários e não a pessoa do usuário, com nomes próprios.

##### Perguntas usadas para encontrar atores:
1. Quem está interessado em certo requisito?
2. Quem vai inserir, editar ou excluir informações do/ para o sistema?
3. Que recursos externos o sistema utiliza?
4. Que atores são requeridos por casos de uso?

### Caso de Uso:
Constitui todas as funcionalidades do sistema. É iniciado por um ator para ativar certa funcionalidade no sistema(evento/estímulo).

São os requisitos funcionais do sistema.

Os atores são os próprios stakeholders.

##### Como encontrar casos de uso:
1. Quais são as tarefas/ações de um determinado ator?
2. Quais tarefas de um ator: criar, armazenar, alterar ou remover informações do sistema?
3. Que mudanças externas o ator deve informar ao sistema?
4. Que ocorrências no sistema devem ser informadas ao ator?
5. Todos os requisitos podem ser atendidos pelos casos de uso?

###### Relacionamento entre casos de uso:
1. Generalização(Herança);
2. 
3. Extensão(extend);
4. Inclusão(include);

