#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

int sleep(int);                             // Conta segundos antes de avançar.
int loop_funcao = TRUE;
int qtd_primos_confirmados = 0;             // Variável para a função primen;

void receber_entrada();
void chave_publica();
    long long int func_euclides(long long int, long long int);
int criptografar();
void descriptografar();
    long long int valor_D(long long int a, long long int);
    long long int exponenciacao_modular(long long int, unsigned long long int, long long int);
    int primen(int*, int*, long long int);
    void registrador_primen(int*, int, int*);
    int conferir_primalidade(long long int);
    int verificar_paridade_de_p(int);
    int p_menor_igual_a_dois(int*, int*, long long int);

int main()
{
    printf("\nCriptografia RSA\n\n");
    receber_entrada();
    return 0;
}

void receber_entrada() {
    while(loop_funcao == TRUE)
    {
        loop_funcao = FALSE;

        printf("Escolha uma das opcoes abaixo\n");
        printf("1. Gerar chave publica;\n");
        printf("2. Criptografar uma mensagem;\n");
        printf("3. Descriptografar uma mensagem.\n");
        printf("Digite o numero da opcao: ");
        
        int escolha;
        scanf("%d", &escolha);

        switch(escolha)
        {
            case 1:
                printf("\nVocê escolheu: Gerar chave publica.\n\n");
                chave_publica();                                // Ir à função Gerar Chave Pública.
                break;
        
            case 2:
                printf("\nVocê escolheu: Criptografar.\n\n");
                int retorno_primalidade = criptografar();                   // Ir à função Criptografar.
        
                while(retorno_primalidade == 2){                // Se o número de retorno_primalidade for 2, então o usuário ainda... 
                    printf("\nVocê está gerando uma chave pública.\n"); // ... não possui uma chave pública.
                    chave_publica();                // Essa linha leva-o à função de gerar chave pública.
                    printf("\n");
                    retorno_primalidade = criptografar();       // Essa linha retorna à função criptografar e monitora...
                }                                   // ... o retorno_primalidade, para retornar à anterior caso necessário.
                break;
        
            case 3:
                printf("\nVocê escolheu: Descriptografar.\n\n");
                descriptografar();                              // Ir à função Descriptografar.
                break;

            default:
                printf("\nOpção inválida!\n\n");    // Caso o usuário escolha uma opção inválida.

                if((escolha > 10) || (escolha < 0)) {   // Opções inválidas são: dígtos > 10 | digitos < 0
                    exit(EXIT_FAILURE);                 // Finaliza o programa.
                }

                sleep(2);       // Espera 2 segundos para mostrar a mensagem de opção inválida.
                loop_funcao = TRUE; // Se a escolha estiver dentro do intervalo [0, 10], mas não for {1, 2, 3}...
                break;              // então o programa lista novamente as opções e pergunta novamente.
        }
    }
}

void chave_publica()
{
// Criar e abrir um arquivo de texto com o nome de 'chave_pública.txt' para armazenarmos a chave.
    FILE *chave_p_pasta;
    chave_p_pasta = fopen("chave_publica.txt", "w");

    if(chave_p_pasta == NULL)
    {
        /* Arquivo não foi criado, saindo */
        printf("Nao foi possivel criar o arquivo.\n"); //acent
        exit(EXIT_FAILURE);
    }

    long long int p, q, e;
    short int retorno_primalidade;
    
    printf("Digite dois numeros primos nao-iguais ('p' e 'q')\n");
    scanf("%lld%lld", &p, &q);
    getchar();
    
// Se os dois números inseridos forem iguais...
    if(p == q)
    {
        printf("Erro: Os dois numeros inseridos são iguais.\n");
        exit(EXIT_FAILURE);
    }

// Se os dois números inseridos forem menores do que três...
    if((p < 4)||(q < 4))
    {
        printf("Erro: Você deve inserir numeros primos maiores do que 3.\n");
        exit(EXIT_FAILURE);
    }

// Chamar a função para conferir se P e Q são primos;
    retorno_primalidade = conferir_primalidade(p);

// se P for um número primo, verificar a primalidade de Q.
    if(retorno_primalidade != 0)
    {
        retorno_primalidade = conferir_primalidade(q);
    
    // Se Q também for um número primo, ignorar o if abaixo.
        if(retorno_primalidade != 1)
        {
            printf("Numero invalido!\n");
            exit(EXIT_FAILURE); 
        }
    }
 
    printf("Digite o expoente (e), que esteja entre 1 e (p - 1)*(q - 1)\n");
    scanf("%lld", &e);
    
// Inicialização do Z ou (p - 1)*(q - 1);
    long long int z = ((p - 1)*(q - 1));

// Se E for maior que o Z, terminar o programa.
    if(e > z) {
        printf("Numero invalido! O numero digitado é maior que (p - 1)*(q - 1).\n");
        exit(EXIT_FAILURE);
    }

// Verificar se são coprimos
    if(func_euclides(z, e) != 1) {
        printf("Numero invalido! O numero digitado não é coprimo de %llu.\n", (p - 1) * (q - 1));
        exit(EXIT_FAILURE);
    }
    
// Salvar as chaves públicas no arquivo "chave_publica.txt"
    fprintf(chave_p_pasta, "n = %lld, e = %lld", p * q, e);
    fclose(chave_p_pasta);
    printf("\nChave criada com sucesso!\n");
}

int criptografar()
{
// Inicialização das variáveis.
    char texto_puro[500000];
    long long int texto_criptografado[500000];
    long long int n, e;

    printf("Digite uma mensagem para ser criptografada: ");
    getchar();
    fgets(texto_puro, 500000, stdin);
    
    printf("Insira a chave pública. (Dica: se não tiver uma chave pública, insira 0 para fazê-la agora.)\n");

// Receber o N ... e, caso necessário, retornar a função Gerar Chave Pública.
    printf("Digite 'n', o produto de 'p' e 'q': ");
    scanf("%lld", &n);
    
    if(n == 0)
    {
        return 2;
    }

// Receber o E.
    printf("Digite o expoente 'e': ");
    scanf("%lld", &e);

    if(e == 0)
    {
        return 2;
    }

// Após receber o N e o E, podemos continuar.

// Gera um arquivo chamado "mensagem_criptografada.txt"
    FILE *mensagem_criptografada;
    mensagem_criptografada = fopen("mensagem_criptografada.txt", "w");
    
    if(mensagem_criptografada == NULL)
    {
        /* Arquivo não foi criado, saindo */
        printf("Nao foi possivel criar o arquivo.\n"); //acent
        exit(EXIT_FAILURE);
    }

// Inicialização de variáveis: 
    int check_lower;
    int string_lenght = strlen(texto_puro);

// Loop para transformar as letras minúsculas em maiúsculas e filtrar caracteres não alfabéticos.
    printf("Mensagem recebida: ");
    for(int i = 0; i < string_lenght; i++)
    {
    /*  Essa área do código apenas deixa passar letras e espaços, e transforma as letras minúsculas em
        maiúsculas, para então transformar os valores ASCII das letras em novos valores alfabéticos indo
        de 2-28 (A-Z e Espaço), armazenando cada respectivo valor em uma casa da array texto_criptografado,
        além de printar a mensagem recebida na tela. */
        if(((isalpha(texto_puro[i])) != 0) || ((isspace(texto_puro[i])) != 0)) 
        {
            if(texto_puro[i] == 32) // Caso espaço.
            {
                texto_criptografado[i] = texto_puro[i] - 4;
                printf("%c", texto_puro[i]);
                continue;
            }

            check_lower = islower(texto_puro[i]);

            if(check_lower == 512)
            {
                texto_puro[i] = toupper(texto_puro[i]);
            }

            texto_criptografado[i] = texto_puro[i] - 63;
            printf("%c", texto_puro[i]);
        }
    }

    unsigned long long int potencia_criptografar;

    for(int k = 0; k < string_lenght - 1; k++) {
        potencia_criptografar = pow(texto_criptografado[k], e);   // Loop -> Texto criptografado = (Texto puro^e) mod(n)
        texto_criptografado[k] = potencia_criptografar % n;       // e depois escreve o valor criptografado no documento.
        fprintf(mensagem_criptografada, "%lld", texto_criptografado[k]);
        if(k != string_lenght - 2) {
            fprintf(mensagem_criptografada, " ");
        }
    }

    // Fim da função
    fclose(mensagem_criptografada);
    return 0;
}

void descriptografar() {
// Inicializar e receber os valores de P, Q, e E
    long long int p, q, e;

    printf("Digite os valores de 'p', 'q', e 'e'\n");
    scanf("%lld", &p);  scanf("%lld", &q);  scanf("%lld", &e);
    getchar();

    long long int texto_criptografado[500000];
    char texto_puro[500000];
    int string_lenght = 0;

    FILE *arquivo_texto_criptografado;
    arquivo_texto_criptografado = fopen("mensagem_criptografada.txt", "r");

    if(arquivo_texto_criptografado == NULL)
    {
        /* Arquivo não foi criado, saindo */
        printf("Nao foi possivel criar o arquivo.\n"); //acent
        exit(EXIT_FAILURE);
    }

/*      Coletar todos os números dentro do arquivo com a mensagem criptografada.
        Após coletar todos os números, fechar o arquivo.                            */

    while(!feof(arquivo_texto_criptografado)) {
        fscanf(arquivo_texto_criptografado, "%lld", &texto_criptografado[string_lenght]);
        string_lenght++;
    }

    fclose(arquivo_texto_criptografado);

// Criar um novo arquivo chamado "mensagem_descriptografada.txt"

    FILE *arquivo_texto_descriptografado;
    arquivo_texto_descriptografado = fopen("mensagem_descriptografada.txt", "w");
    
    if(arquivo_texto_descriptografado == NULL)
    {
        /* Arquivo não foi criado, saindo */
        printf("Nao foi possivel criar o arquivo.\n"); //acent
        exit(EXIT_FAILURE);
    }

//  Declarar e assignar um valor ao D.
    long long int d;
    d = valor_D(e, ((p - 1) * (q - 1)));

    long long int n = p * q;

/*  Fazer a exponenciação modular de todos os caracteres criptografados e assigná-los a seus valores originais
    da tabela ASCII na string 'texto_puro'.*/

    for(int i = 0; i < string_lenght; i++)
    {
        texto_puro[i] = exponenciacao_modular(texto_criptografado[i], d, n);

        if(texto_puro[i] == 28)
        {
            texto_puro[i] += 4;
        }

        else
        {
            texto_puro[i] += 63;
        }

        printf("%c", texto_puro[i]);
        fprintf(arquivo_texto_descriptografado, "%c", texto_puro[i]);
    }

    printf("\n");
    fclose(arquivo_texto_descriptografado);
}





/*                  Funções                 */





// Função do Algoritmo de Euclides (MDC)

long long int func_euclides(long long int x, long long int y) {
    long long int res, resto;
    resto = x % y;
    if(resto == 0) {
       res = y;
       return res;
    }
    else {
        return func_euclides(y, resto); 
    }
}


// Função que determina o valor da variável 'd'

long long int valor_D(long long int a, long long int mod) {
    long long int inverso;
    for(inverso = 1; inverso > 0; inverso++) {
        long long int solucao = (a * inverso) % mod;
        if(solucao == 1) {
            return inverso;
        }
    }  
    return inverso;
}


// Função que determina a potência (texto criptografado^d) mod n
long long int exponenciacao_modular(long long int x, unsigned long long int y, long long int p) { 
    int resultado_pow = 1;      // Inicializar o resultado
  
    x = x % p;  // Atualizar o x se for maior ou igual a p
  
    if (x == 0) {
        return 0;
    } // Nesse caso, x é divisível por p;
  
    while (y > 0) 
    { 
        // Se y é ímpar, multiplicar o x com o resultado
        if (y & 1) {
            resultado_pow = (resultado_pow*x) % p; 
        }
            
        // y deve ser par agora 
        y = y >> 1; // y = y/2 
        x = (x*x) % p;   
    } 
    return resultado_pow; 
} 


/*      Função que contabiliza e registra diversos números primos, e é utilizado também para verificar
        a primalidade de qualquer número abaixo de 10^7     */

int primen(int * primo10e7_primen, int * primos_confirmados_primen, long long int n)
{
    int i, raiz_p;
    for(int p = 3; p < 1000000; p++)    // Rodar os 10^7 do array.
    {                           
        i = qtd_primos_confirmados;        
        primo10e7_primen[p] = 1;        // Assinar 1 (verdadeiro) à posição p por default.
        for(int m = p; m >= 2; m = m)
        {
            raiz_p = (int)sqrt(p);
            m = primos_confirmados_primen[qtd_primos_confirmados - i];
            
            if((p % m) == 0) // se real, o número não é primo e p deverá ser desconsiderado
            {
                primo10e7_primen[p] = 0;
                return 1;
                break;
            }
            // Para chegar ao primeiro dos primos armazenados (primos_confirmados_primen[0])
            if(m < primos_confirmados_primen[qtd_primos_confirmados]) 
            {
                i--;
                continue;
            }
            if((m > 2)&&(m > raiz_p)) {
                primo10e7_primen[p] = 1;
                // Registrar o número primo.
                registrador_primen(primo10e7_primen, p, primos_confirmados_primen);
                if(p == n) {
                    return 0;                    
                }
                break;
            }
            else if(m == primos_confirmados_primen[qtd_primos_confirmados])
            {
                if((p % m) != 0)
                {
                    registrador_primen(primo10e7_primen, p, primos_confirmados_primen); 
                    if(p == n) {
                        return 0;
                    }
                    break;
                }
            }
        }
    }
    return 1;
}


// Função auxiliar da primen, que confere a primalidade de tal número

int conferir_primalidade(long long int n)
{
    int primo10e7[1000000];     // Iniciar o array 10^7 para receber todos os valores entre 0 e 10^7
    int conjunto_primos[1000000];   // Receber os valores primos confirmados

    int resultado_p_menor = p_menor_igual_a_dois(primo10e7, conjunto_primos, n);
    
    if(resultado_p_menor == 0)
    {
        return 0;
    }
 
    int resultado = primen(primo10e7, conjunto_primos, n);
 
    if(resultado == 0)
    {
        return 0;
    }
 
    return 1;
}


// Função auxiliar do primen, que verifica a paridade de p

int verificar_paridade_de_p(int p)
{
    if(p % 2 == 0)
    {
        return p - 1;
    }
    else
    {
        return p - 2;
    }
}


// Função auxiliar do primen para verificar se p é menor ou igual a 2

int p_menor_igual_a_dois(int * primo10e7_pmenor, int * primo_conf_menor, long long int n)
{
    for(int i = 0; i < 3; i++)
    {
        if(i == 2)
        {
            if(n == 2) {
                return 0;
            }
            primo10e7_pmenor[i] = 1;
            primo_conf_menor[0] = 2;
            registrador_primen(primo10e7_pmenor, i, primo_conf_menor);
            break;
        }
        primo10e7_pmenor[i] = 0;
        registrador_primen(primo10e7_pmenor, i, primo_conf_menor);
    }
    return 1;
}


// Função auxiliar do primen, que registra os números primos confirmados.

void registrador_primen(int * primo10e7_d, int p_d, int * primos_conf_d)
{
        if(primo10e7_d[p_d] == 1)
        {
            qtd_primos_confirmados++;
            primos_conf_d[qtd_primos_confirmados] = p_d;
        }
}