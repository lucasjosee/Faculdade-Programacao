// Pinos dos LEDs que mostram o resultado W da ULA
#define LED_F3 13  // bit mais significativo
#define LED_F2 12
#define LED_F1 11
#define LED_F0 10  // bit menos significativo

#define TAM_MEMORIA     100      // maximo de instrucoes que o programa aceita
#define TIMEOUT_CARGA   1000  // ms sem dados para considerar carga concluida
#define DELAY_EXECUCAO  4000  // ms entre instrucoes (4 segundos conforme especificacao)

// Estados da maquina
#define S_AGUARDANDO     0  // esperando o primeiro byte chegar pelo serial
#define S_CARREGANDO     1  // recebendo e guardando as instrucoes na memoria
#define S_PRONTO         2  // carga concluida, vai mostrar dump e perguntar S/N
#define S_ESPERANDO_RESP 3  // aguardando o usuario digitar S ou N
#define S_EXECUTANDO     4  // executando instrucoes uma a uma
#define S_CONCLUIDO      5  // programa terminou, nao faz mais nada

// Vetor memoria
char memoria[TAM_MEMORIA][4];
int num_instrucoes; 

int regs[4];

int estado;            
char linha_buf[10];    
int linha_idx;         
unsigned long t_ultimo_dado;   
unsigned long t_ultimo_passo; 

// Prototipos
void mostrarDump();
void imprimirMarcador(int pc);
void atualizarLeds(int w);
int executarULA(int x, int y, int s);
int hexParaInt(char c);
void salvarLinha();

void setup()
{
    Serial.begin(9600);

    // Configura os 4 pinos dos LEDs como saida
    pinMode(LED_F3, OUTPUT);
    pinMode(LED_F2, OUTPUT);
    pinMode(LED_F1, OUTPUT);
    pinMode(LED_F0, OUTPUT);

    // Inicializa tudo zerado antes de comecar
    regs[0] = 0;
    regs[1] = 0;
    regs[2] = 0;
    regs[3] = 0;
    num_instrucoes = 0;
    linha_idx = 0;
    estado = S_AGUARDANDO;

    Serial.println("Aguardando programa (.hex)...");
}

void loop()
{
    switch (estado)
    {
        case S_AGUARDANDO:
            // Fica parado ate o primeiro byte chegar pelo serial
            if (Serial.available())
            {
                t_ultimo_dado = millis();  // marca o inicio da carga
                estado = S_CARREGANDO;
            }
            break;

        case S_CARREGANDO:
            // Le todos os bytes disponiveis no serial agora
            while (Serial.available())
            {
                char c = Serial.read();
                t_ultimo_dado = millis();  // atualiza o tempo do ultimo dado recebido

                // Ignora qualquer separador
                if (c == '\n' || c == '\r' || c == ' ') continue;

                if (linha_idx < 3)
                {
                    linha_buf[linha_idx++] = c;

                    // Assim que completar 3 digitos, salva como uma instrucao
                    if (linha_idx == 3) salvarLinha();
                }
            }

            // Se passou 1 segundo sem receber nada, consideramos que a carga terminou
            if (millis() - t_ultimo_dado > TIMEOUT_CARGA)
            {
                estado = S_PRONTO;
            }
            break;

        case S_PRONTO:
            // Exibe o estado inicial da memoria e dos registradores
            Serial.println("Programa carregado na memoria");
            imprimirMarcador(0);  // marca o PC apontando para a primeira instrucao
            mostrarDump();
            Serial.println();
            Serial.println("Deseja executar o programa (S/N)?");
            estado = S_ESPERANDO_RESP;
            break;

        case S_ESPERANDO_RESP:
            // Aguarda o usuario responder se quer executar ou nao
            if (Serial.available())
            {
                char r = Serial.read();
                if (r == 'S' || r == 's')
                {
                    // Subtrai o delay para a primeira instrucao executar imediatamente
                    t_ultimo_passo = millis() - DELAY_EXECUCAO;
                    estado = S_EXECUTANDO;
                }
                else if (r == 'N' || r == 'n')
                {
                    estado = S_CONCLUIDO;
                }
            }
            break;

        case S_EXECUTANDO:
            // Verifica se ja executamos todas as instrucoes
            if (regs[0] >= num_instrucoes)
            {
                Serial.println("Programa concluido !");
                estado = S_CONCLUIDO;
                break;
            }

            // delay de 4s
            if (millis() - t_ultimo_passo >= DELAY_EXECUCAO)
            {
                // Busca a instrucao que o PC esta apontando
                char* inst = memoria[regs[0]];

                // Decodifica os 3 digitos hex em X, Y e S
                int x = hexParaInt(inst[0]);
                int y = hexParaInt(inst[1]);
                int s = hexParaInt(inst[2]);

                // Executa a operacao da ULA e obtem o resultado W
                int w = executarULA(x, y, s);

                // Atualiza os registradores com os valores desta instrucao
                regs[2] = x;
                regs[3] = y;
                regs[1] = w;
                regs[0]++;  // avanca o PC para a proxima instrucao

                // Mostra o resultado nos LEDs fisicos
                atualizarLeds(w);

                // Exibe o dump com o marcador ja na nova posicao do PC
                imprimirMarcador(regs[0]);
                mostrarDump();

                t_ultimo_passo = millis();  // reinicia o contador do delay
            }
            break;

        case S_CONCLUIDO:
            break;
    }
}

// Salva os 3 digitos do buffer como uma instrucao na memoria
void salvarLinha()
{
    if (linha_idx == 3 && num_instrucoes < TAM_MEMORIA)
    {
        memoria[num_instrucoes][0] = linha_buf[0];
        memoria[num_instrucoes][1] = linha_buf[1];
        memoria[num_instrucoes][2] = linha_buf[2];
        memoria[num_instrucoes][3] = '\0'; 
        num_instrucoes++;
    }
    linha_idx = 0;  // reseta o buffer para a proxima instrucao
}

// Imprime no serial o estado atual da memoria e dos 4 registradores
void mostrarDump()
{
    // Mostra apenas as posicoes da memoria que tem instrucoes, nao o vetor inteiro
    Serial.print("Memoria:      ");
    for (int i = 0; i < num_instrucoes; i++)
    {
        Serial.print("| ");
        Serial.print(memoria[i]);
        Serial.print(" ");
    }
    Serial.println("|");

    // Mostra PC, W, X e Y em hexadecimal
    Serial.print("Registradores: ");
    for (int i = 0; i < 4; i++)
    {
        Serial.print("| ");
        Serial.print(regs[i], HEX);
        Serial.print(" ");
    }
    Serial.println("|");
}

// Imprime "--"
void imprimirMarcador(int pc)
{
    int espacos = 14 + pc * 6 + 2;
    for (int i = 0; i < espacos; i++) Serial.print(" ");
    Serial.println("--");
}

// Aciona os 4 LEDs conforme os bits do resultado W
void atualizarLeds(int w)
{
    // Usa deslocamento de bits para extrair cada bit individualmente
    digitalWrite(LED_F3, (w >> 3) & 1);
    digitalWrite(LED_F2, (w >> 2) & 1);
    digitalWrite(LED_F1, (w >> 1) & 1);
    digitalWrite(LED_F0, (w >> 0) & 1);
}

// Converte um caractere hex ('0'-'9', 'A'-'F') para o inteiro equivalente
int hexParaInt(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

// Executa a operacao da ULA definida por S e retorna W com 4 bits
int executarULA(int x, int y, int s)
{
    int w = 0;
    switch (s)
    {
        case 0x0: w = x;           break; // CopiaA:  W = X
        case 0x1: w = y;           break; // CopiaB:  W = Y
        case 0x2: w = x ^ y;       break; // AxB:     W = X XOR Y
        case 0x3: w = ~(x ^ y);    break; // nAxnB:   W = XNOR(X, Y)
        case 0x4: w = ~(x & y);    break; // AeBn:    W = NAND(X, Y)
        case 0x5: w = ~y;          break; // nB:      W = NOT Y
        case 0x6: w = (~x) | (~y); break; // nAonB:   W = (NOT X) OR (NOT Y)
        case 0x7: w = ~x;          break; // nA:      W = NOT X
        case 0x8: w = x | (~y);    break; // AonB:    W = X OR (NOT Y)
        case 0x9: w = 0xF;         break; // UmL:     W = 1111
        case 0xA: w = 0x0;         break; // ZeroL:   W = 0000
        case 0xB: w = x & y;       break; // AeB:     W = X AND Y
        case 0xC: w = (~x) & y;    break; // nAeB:    W = (NOT X) AND Y
        case 0xD: w = x & (~y);    break; // AenB:    W = X AND (NOT Y)
        case 0xE: w = x | y;       break; // AoB:     W = X OR Y
        case 0xF: w = (~x) & (~y); break; // nAenB:   W = NOR(X, Y)
    }
    return w & 0xF;
}
