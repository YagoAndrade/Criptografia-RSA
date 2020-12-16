# Criptografia-RSA
PT-BR: Projeto final da disciplina Matemática Discreta, um projeto que consiste em um algoritmo básico que criptografe e descriptografe textos baseado na tecnologia de Criptografia RSA.

------------ EXPLICAÇÃO DO CÓDIGO ------------

1-5: 5 bibliotecas incluídas.

6-7: definição de dois “nomes” que já terão significado constante durante o código.

8-25: Definição de variáveis e Declaração de funções usadas durante todo o código. 

26-34: Função principal, aonde se inicia nosso programa.
       •Nela nós fazemos um loop para que o programa rode até o usuário digitar a opção 4, de querer sair e encerrar o programa.

35-92: Criamos uma nova função onde nela:
       •Informamos ao usuário as opções que ele poderá escolher e armazenamos tal opção, de modo a redireciona-lo para o local de qual opção ele escolheu.
       •De modo que a cada escolha que ele fizer a gente vai para uma função específica que irá fazer o que a opção escolhida pelo usuário informa.

93-166: Nessa linhas temos uma nova função, a qual irá gerar a chave pública para o usuário, após ele digitar certos comandos.
        •Linha 109: solicitamos que o usuário digite um par de números primos p e q
(Verificamos se os números digitados são primos, se não for informamos, e se for continuamos o programa).
        •Linha 143: solicitamos ao usuário que digite um expoente ‘e’, que esteja entre 1 e (p-1)*(q-1)
(Verificamos se o ‘e’ corresponde as especificidades dadas, se não informarmos, e se sim informamos “Chave criada com sucesso!”).
        •E, com isso, salvamos, no diretório de execução do programa, um arquivo txt(“chave_publica.txt”) com os dois números que formam a chave pública.

167-259: Nessas linhas, teremos uma função responsável por criptografar uma mensagem.
        •174: Solicitamos ao usuário a digitação da mensagem.
        •178: Solicitamos que o usuário digite a chave pública recebida previamente.
        •Durante toda a função iremos transformar cada caractere recebido da mensagem, em um número corresponde entre 2-28.
         •Iremos criptografar cada representação numérica de 2-28 dos carácteres recebidos, em novos números os quais serão a mensagem encriptografada.
          •Salvamos, no diretório de execução do programa, um arquivo txt com a mensagem encriptada, chamado de “mensagem_criptografada.txt”.

260-333: Uma nova função, com o objetivo de descriptografar uma mensagem.
           •264: Solicitamos que o usuário digite o ‘p’, ‘q’ e ‘e’.
           •Transformamos a mensagem criptografada em uma nova sequência numérica entre 2-28, e após isso descriptografamos tais números para representação de caractere, formando a mensagem original e encerrando a descriptografia.
             •Salvamos, no diretório de execução do programa, um arquivo txt com a mensagem desencriptada, chamado de “mensagem_descriptografada.txt”.

334-524: Diversas funções extras necessárias para o decorrer do programa e os cálculos nele feitos.
      •347: Função do Algoritmo de Euclides(MDC).
      •360: Função que determina o valor da variável ‘d’.
      •375: Função que determina a potência (texto criptografado^d) mod n.
      •402: Função que verifica a primalidade.
      •454: Função auxiliar da anterior, que confere a primalidade de tal número.
      •479: Função auxiliar da localizada na linha 402, que verifica a paridade de p.
      •494: Função auxiliar da localizada na linha 402, para verificar se ‘p’ é menor ou igual a 2.
       •517: Função auxiliar da localizada na linha 402, que registra os números primos confirmados.
