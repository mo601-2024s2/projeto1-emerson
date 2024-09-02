# Projeto 1 de MO601 - Simulador RISC-V
## Identificação do Grupo


- RA: 233865
- Nome: Emerson José Bezerra da Silva

## Descrição do Projeto

Simulador de processador RISC-V (instruções I e M) escrito em C++ para a disciplina M0601. Simulação funcional de processador de único núcleo com execução em ordem.

## Ambiente de desenvolvimento
Foi utilizada a IDE CLion para os arquivos do projeto, juntamente com o compilador CLang. Já para os arquivos escritos para serem executados no simulador foram utilizados um editor de texto e o compilador gcc na versão oferecida pela toolchain RISC-V, montada no conjunto de instruções IMA (como a versão Linux foi montada juntamente, as instruções atômicas foram usadas na geração de código, mesmo que não sejam usadas nem suportadas pelo simulador).

## Algoritmo de simulação
O compilador recebe um arquivo binário do tipo simples. O PC é inicializado com um valor dado por linha de comando (extraído do ELF, no caso dos exemplos executados), assim como o GP, que é necessário para alguns truques de endereçamento usados pelo GCC. Uma instrução é tirada do endereço apontado pelo PC na memória simulada (representada como um vetor de bytes), os campos dela são extraídos e salvos numa classe e a instrução passa por uma cascata de funções de interpretação, até chegar numa função de execução, que realiza as mudanças necessárias no PC, escreve um log de execução da instrução e produz o próximo PC. A execução segue até uma instrução inválida ou a chamada de sistema de saída ser executada.

## Testes
Os testes iniciais foram feitos utilizando arquivos escritos a mão com uma única instrução de codificação binária conhecida. Depois, testes mais complexos usando arquivos ASM foram feitos, até o estado em que o simulador já era capaz de executar programas completos escritos em C diretamente. Os primeiros aspectos se comunicavam com o sistema através do resultado do retorno da função main, antes da entrada e saída ser implementada no simulador, enquanto que os últimos eram programas mais completos com entrada e saída reais e maior cobertura de testes.

## Aprendizado
Aprendi bastante sobre a codificação binária das instruções RISC-V, principalmente sobre a regularidade dos formatos e sobre o tratamento dos imediatos, assim como sobre a forma como um compilador faz uso dos recursos da arquitetura, principalmente no modo comum de endereçamento de globais usado pelo compilador GCC na plataforma RISC-V. O projeto também foi útil para entender sobre simulação funcional de processadores, no sentido de que esse projeto buscou o modelo mais simples possível do processador para a simulação.


## Desempenho
No teste dhrystone, foram obtidos resultados de 1000~1500 microsegundos por teste, com 665~1000 dhrystones por segundo.

Crie seções para cada uma das informações abaixo:

- Desempenho do seu simulador conforme DryStone e CoreMark
