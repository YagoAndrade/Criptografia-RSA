#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int maior_primo = 0, qtd_primo_conf = 0;
int p0 = 0, p1 = 0, p2 = 0, p3 = 0;

void chave_publica();
    long long int func_euclides(long long int, long long int);
int criptografar();
void descriptografar();
    long long int func_variavel_d(long long int a, long long int mod);
    int conferir_se_eh_primo(long long int n_func);
    int verificar_paridade_de_p(int);
    int primen(int*, int*, long long int);
    int p_menorigual2(int*, int*, long long int);
    void debug_print(int*, int, int*);
    long long int func_primo_em_relacao_a_e(long long int);
    int mdc_func(int, long long int);
    long long int power(long long int, unsigned long long int, long long int);

int main() {
    int func_true = 1;
    while(func_true == 1) {
        func_true = 0;
        printf("Criptografia RSA\n");
        printf("Escolha uma das opcoes abaixo\n");
        printf("1. Gerar chave publica;\n");
        printf("2. Criptografar uma mensagem;\n");
        printf("3. Descriptografar uma mensagem.\n");
        printf("Digite o numero da opcao: ");
        int escolha;
        scanf("%d", &escolha);
        switch(escolha) {
            case 1:
                printf("Você escolheu: gerar chave publica.\n");
                chave_publica();
                break;
            case 2:
                printf("Você escolheu: Criptografar.\n");
                int retorno = criptografar();
                while(retorno == 2){
                    printf("\nVocê está gerando uma chave pública.\n");
                    chave_publica();
                    retorno = criptografar();
                }
                break;
            case 3:
                printf("Você escolheu: Descriptografar.\n");
                descriptografar();
                break;
            default:
                printf("Escolha inválida!\n");
                func_true = 1;
        }
    }
    return 0;
}

void chave_publica() {
    FILE *chave_p_pasta;
    chave_p_pasta = fopen("chave_publica.txt", "w");
    if(chave_p_pasta == NULL)
    {
        /* Arquivo não foi criado, saindo */
        printf("Nao foi possivel criar o arquivo.\n"); //acent
        exit(EXIT_FAILURE);
    }
    long long int p, q, e;
    short int retorno;
    printf("Digite dois numeros primos (p e q): ");
    scanf("%lld%lld", &p, &q);
    if(p != 2) {
        retorno = conferir_se_eh_primo(p); // Função para verificar se P e Q são primos;
        if(retorno != 0) {
            if(q != 2) {
                retorno = conferir_se_eh_primo(q);
                if(retorno != 1) {
                    printf("Numero invalido!\n");
                    exit(5); // Código do número inválido        
                }
            }
        }
    }

    else if(!(p == 2)){
        printf("Numero invalido!\n");
        exit(5);
    }
    long long int z = ((p - 1)*(q - 1));
    printf("Digite o expoente (e), que esteja entre 1 e (p - 1)*(q - 1): ");
    scanf("%lld", &e);
    if(func_euclides(z, e) != 1) {
        printf("Numero invalido!\n");
        exit(6);
    }
    fprintf(chave_p_pasta, "n = %lld, e = %lld", p * q, e);
    printf("Chave criada com sucesso!\n");
    fclose(chave_p_pasta);
}

int criptografar() {
    printf("Digite uma mensagem a ser criptografada: ");
    char mensagem[500000];
    long long int array[500000];
    long long int chave_publica_n, chave_publica_e;
    getchar();
    fgets(mensagem, 500000, stdin);
    printf("Digite a chave pública. (Dica: se não tiver uma chave pública, submeta 0 para fazê-la)\n");
    printf("Digite o 'n' ou o produto de 'p' e 'q': ");
    scanf("%lld", &chave_publica_n);
    if(chave_publica_n == 0) {
        return 2;
    }
    printf("Digite o expoente 'e': ");
    scanf("%lld", &chave_publica_e);
    if(chave_publica_e == 0) {
        return 2;
    }
    FILE *mensagem_criptografada;
    mensagem_criptografada = fopen("mensagem_criptografada.txt", "w");
    if(mensagem_criptografada == NULL)
    {
        /* Arquivo não foi criado, saindo */
        printf("Nao foi possivel criar o arquivo.\n"); //acent
        getchar();
        exit(EXIT_FAILURE);
    }
    int check_lower;
    int string_lenght = strlen(mensagem);
    for(int i = 0; i < string_lenght; i++) {
        if(mensagem[i] == 32) {
            array[i] = mensagem[i] - 4;
            continue;
        }
        check_lower = islower(mensagem[i]);
        if(check_lower == 512) {
            mensagem[i] = toupper(mensagem[i]);
        }
        array[i] = mensagem[i] - 63;
    }
    printf("Mensagem recebida: %s", mensagem);
    unsigned long long int pow_result;
    for(int k = 0; k < string_lenght - 1; k++) {
        pow_result = pow(array[k], chave_publica_e);
        array[k] = pow_result % chave_publica_n;
        fprintf(mensagem_criptografada, "%lld\n", array[k]);
    }
    fclose(mensagem_criptografada);
    return 0;
}

void descriptografar() {
    long long int p, q, e;

    printf("Digite os valores de 'p', 'q', e 'e'\n");
    printf("p: ");
    scanf("%lld", &p);
    printf("q: ");
    scanf("%lld", &q);
    printf("e: ");
    scanf("%lld", &e);

    long long int msg_criptografada_int[500000];
    int contador = 0;
    char msg_descriptografada_char[500000];

    FILE *mensagem_criptografada_arquivo;
    mensagem_criptografada_arquivo = fopen("mensagem_criptografada.txt", "r");
    while(!feof(mensagem_criptografada_arquivo)) {
        fscanf(mensagem_criptografada_arquivo, "%lld", &msg_criptografada_int[contador]);
        contador++;
    }
    fclose(mensagem_criptografada_arquivo);

    FILE *mensagem_descriptografada_arquivo;
    mensagem_descriptografada_arquivo = fopen("mensagem_descriptografada.txt", "w");

    long long int d_inverso_descripto;
    d_inverso_descripto = func_variavel_d(e, ((p - 1) * (q - 1)));

    long long int pow_result_descripto;
    long long int n = p * q;
    for(int i = 0; i < (contador - 1); i++) {
        pow_result_descripto = power(msg_criptografada_int[i], d_inverso_descripto, n);
        msg_descriptografada_char[i] = pow_result_descripto;
        msg_descriptografada_char[i] = (long long int) pow_result_descripto % n;
        if(msg_descriptografada_char[i] == 28) {
            msg_descriptografada_char[i] += 4;
        }
        else {
            msg_descriptografada_char[i] += 63;
        }
        fprintf(mensagem_descriptografada_arquivo, "%c", msg_descriptografada_char[i]);
    }

    fclose(mensagem_descriptografada_arquivo);
}

long long int func_euclides(long long int x, long long int y) {
    long long int res, rest;
    rest = x % y;
    if(rest == 0) {
       res = y;
       return res;
    }
    else {
        return func_euclides(y, rest); 
    }
}

long long int func_variavel_d(long long int a, long long int mod) {
    long long int d_inverso_func;
    for(d_inverso_func = 1; d_inverso_func > 0; d_inverso_func++) {
        long long int sol = (a * d_inverso_func) % mod;
        if(sol == 1) {
            return d_inverso_func;
        }
    }  
    return d_inverso_func;
}

int conferir_se_eh_primo(long long int n_func) {
    int primo10e7[1000000];     // Iniciar o array 10^7 para receber todos os valores entre 0 e 10^7
    int primo_conf[1000000];   // Receber os valores primos confirmados
    int result_p_menor = p_menorigual2(primo10e7, primo_conf, n_func);
    if(result_p_menor == 0) {
        return 0;
    }
    int result = primen(primo10e7, primo_conf, n_func);
    if(result == 0) {
        return 0;
    }
    return 1;
}

int verificar_paridade_de_p(int p_even)
{
    if(p_even % 2 == 0)
    {
        return p_even - 1;
    }
    else
    {
        return p_even - 2;
    }
}

int primen(int * primo10e7_primen, int * primo_conf_primen, long long int n_func) {
    int i, sqrtp;
    for(int p = 3; p < 1000000; p++)    // Rodar os 10^7 do array.
    {                           
        i = qtd_primo_conf;        
        primo10e7_primen[p] = 1;             // Assinar 1 (verdadeiro) à posição p por default.
        for(int m = p; m >= 2; m = m)
        {
            sqrtp = (int)sqrt(p);
            m = primo_conf_primen[qtd_primo_conf - i];
            if((p % m) == 0)// se real, o número não é primo e p deverá ser desconsiderado
            {
                primo10e7_primen[p] = 0;
                return 1;
                break;
            }
            if(m < primo_conf_primen[qtd_primo_conf]) // Para chegar ao primeiro dos primos armazenados (primo_conf_primen[0])
            {
                i--;
                continue;
            }
            if((m > 2)&&(m > sqrtp)) {
                primo10e7_primen[p] = 1;
                debug_print(primo10e7_primen, p, primo_conf_primen); // Printar na tela o número primo
                if(p == n_func) {
                    return 0;                    
                }
                break;
            }
            else if(m == primo_conf_primen[qtd_primo_conf])
            {
                if((p % m) != 0)
                {
                    debug_print(primo10e7_primen, p, primo_conf_primen); // Printar na tela o número primo
                    if(p == n_func) {
                        return 0;
                    }
                    break;
                }
            }
        }
    }
    return 1;
}

int p_menorigual2(int * primo10e7_pmenor, int * primo_conf_menor, long long int n_func)
{
    for(int i = 0; i < 3; i++)
    {
        if(i == 2)
        {
            if(n_func == 2) {
                return 0;
            }
            primo10e7_pmenor[i] = 1;
            primo_conf_menor[0] = 2;
            debug_print(primo10e7_pmenor, i, primo_conf_menor);
            break;
        }
        primo10e7_pmenor[i] = 0;
        debug_print(primo10e7_pmenor, i, primo_conf_menor);
    }
    return 1;
}

void debug_print(int * primo10e7_d, int p_d, int * primos_conf_d)
{
        if(primo10e7_d[p_d] == 1)
        {
            maior_primo = p_d;
            qtd_primo_conf++;
            primos_conf_d[qtd_primo_conf] = p_d;
        }
}

long long int func_primo_em_relacao_a_e(long long int func_e) {
    printf("Func_primo_em_relacao\n");
    int resultado_slide_59;
    for(int i = 2; i > 1; i++) {
        printf("rodada func_primo = %d", i);
        resultado_slide_59 = func_euclides(i, func_e);
        if(resultado_slide_59 == 1) {
            return i;
        }
    }
    return 1;
}

long long int power(long long int x, unsigned long long int y, long long int p) { 
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

/*int mdc_func(int num1_mdc, long long int num2_mdc) {
    int resto = 1;
    int i;
    while(resto != 0) {
        printf("mdc func = %d\n", i);
        resto = num1_mdc % num2_mdc;
        num1_mdc = num2_mdc;
        num2_mdc = resto;
        printf("num1_mdc = %d | resto = %d\n\n", num1_mdc, resto);
        i++;
    }
    return num1_mdc;
}*/

/*short int func_eh_primo(long long int n_func) {
    if((n_func == 1) || (n_func == 0)) {
        return 0;
    }
    if(n_func <= 10) {
        for(int i = 2; i < n_func; i++) {
            if((n_func % i) == 0) {
                return 0;
            }
        }
        return 1;
    }
    else {
        for(int i = 2; i <= 10; i++){
            if((n_func % i) == 0){
                return 0;
            }
        }
        return 1;
    }
}*/

/*  Função do Teorema de Fermat para lidar com números muito grandes (slide 61/66)
    Substituir função "eh_primo" para descobrir que dado número é primo ou não de uma forma mais rápida*/