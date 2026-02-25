### Representação Fracionária:
Para converter números reais, usamos o sistema de ponto flutuante. A ideia é parecida com notação científica.

- **Bit de Sinal (1 bit)**:
    
    - `0` para números positivos.
        
    - `1` para números negativos.
    
- **Expoente (Ex: 8 bits)**:
    
    - Representa a potência de 2. É ele que "move" o ponto binário para a esquerda ou para a direita, permitindo representar números muito grandes ou muito pequenos.
    
- **Mantissa ou Fração (Ex: 23 bits)**:
    
    - Representa os dígitos significativos do número em binário. Quanto mais bits na mantissa, maior a **precisão** do número.

Um número em ponto flutuante de 32 bits é representado da seguinte forma:

S EEEEEEEE MMMMMMMMMMMMMMMMMMMMMMM

S é o sinal (1 bit), E é o expoente (8 bits), e o M é a mantissa (23 bits)

Ao guardar a mantissa o numero 1, antes do ponto é armazenado "fora" então para fazer a transformação inversa, lembre-se de colocar o número 1