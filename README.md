# Memory-Simulator
Trabalho Prático da matéria de SIstemas Operacionais do DCC-UFMG

Sistemas Operacionais 
TP2: Simulação de um sistema de memória virtual 

Henrique Rotsen Santos Ferreira - 2020100945 
Gabriel Castelo Branco -  

## Resumo 

O projeto consiste em um simulador de algoritmos de reposição de página em uma memória virtual. Para isso utilizamos diferentes técnicas de reposição, como LRU (Least Recently Used), FIFO (First-In-First-Out), Segunda Chance e Aleatório. 

A estrutura geral do código inclui a definição de duas estruturas importantes: struct Page e struct Recorder. A struct Page representa uma página na tabela de páginas, contendo informações como o ID da página, se ela está suja, o contador de segunda chance, um temporizador e o bit de referência. A struct Recorder é responsável por armazenar estatísticas da execução do simulador, como o número de page faults e páginas sujas escritas. 

Existem várias funções importantes no código. A função print_results é responsável por imprimir os resultados finais do simulador, exibindo as configurações utilizadas e as estatísticas coletadas. 

As funções simulate_lru, simulate_fifo, simulate_2a e simulate_random são responsáveis por simular o comportamento dos algoritmos de reposição LRU, FIFO, Segunda Chance e Aleatório, respectivamente. Essas funções percorrem um arquivo de entrada contendo endereços de memória e operações de leitura/escrita. Com base nessas operações, as páginas são carregadas na tabela de páginas e as técnicas de reposição são aplicadas quando ocorrem page faults. 

A função main é o ponto de entrada do programa. Ela recebe os parâmetros da linha de comando, como o algoritmo de reposição, o arquivo de entrada, o tamanho das páginas e o tamanho da memória. Com base nos parâmetros, a função aloca a memória para a tabela de páginas, chama a função apropriada para simular o algoritmo escolhido e, em seguida, imprime os resultados finais. 

O código utiliza outras funções auxiliares, como size_calculator para calcular o tamanho necessário para representar as páginas, id_calculator para calcular o ID da página com base no endereço de memória e add para adicionar uma nova página na tabela. 

## Decisões de Projeto 

O código lida com linhas que não contêm comandos, apenas manipulação de arquivos, de forma simples e direta. Quando o código lê uma linha do arquivo de entrada que não contém um comando válido (endereço de memória seguido de R ou W), ele simplesmente ignora essa linha e passa para a próxima. Essas linhas não causam nenhum efeito no simulador, uma vez que não representam uma operação de leitura ou escrita de memória. 

Isso é tratado pela função simulate_lru, simulate_fifo, simulate_2a e simulate_random, onde há um loop que percorre o arquivo de entrada com a função fscanf. A função fscanf é usada para ler o endereço de memória e o tipo de operação (R ou W) em cada linha. Se a linha não puder ser lida corretamente ou não contiver um comando válido, a função fscanf retornará um valor diferente de 2, indicando que a leitura falhou. 

Quando isso acontece, o código simplesmente ignora a linha e continua para a próxima iteração do loop, lendo a próxima linha do arquivo. Dessa forma, as linhas inválidas ou sem comandos não interferem no funcionamento do simulador e não afetam as estatísticas ou o comportamento dos algoritmos de reposição de página. 

## Análise de Desempenho 

A análise de desempenho dos algoritmos de substituição de página depende dos programas utilizados e de suas características de acesso à memória. Vou fornecer uma análise geral, considerando os quatro algoritmos implementados: LRU, FIFO, Segunda Chance e Aleatório. 

1. LRU (Least Recently Used): 

O algoritmo LRU tende a ter um bom desempenho em programas com padrões de acesso à memória em que as páginas recentemente acessadas têm maior probabilidade de serem acessadas novamente no futuro próximo. Ele mantém um registro do tempo de acesso de cada página e substitui a página que não foi acessada há mais tempo. Portanto, em programas com bom aproveitamento de localidade temporal, o LRU tende a minimizar o número de faltas de página. 

2. FIFO (First-In-First-Out): 

O algoritmo FIFO é simples e fácil de implementar. Ele substitui a página que está há mais tempo na memória, seguindo uma abordagem de fila. No entanto, o FIFO não leva em consideração o padrão de acesso às páginas, o que pode levar a um desempenho inferior em programas com alto grau de localidade temporal. Ele pode ser adequado para programas em que o padrão de acesso é uniforme ou aleatório. 

3. Segunda Chance: 

O algoritmo de Segunda Chance é uma melhoria do FIFO, onde é adicionado um bit de referência a cada página. Esse bit é definido como 1 sempre que a página é acessada. Quando ocorre uma falta de página, o algoritmo examina o bit de referência da página mais antiga. Se for 0, a página é substituída. Caso contrário, o bit de referência é zerado, e a página recebe uma "segunda chance". Essa abordagem tende a melhorar o desempenho em programas com acesso aleatório ou em programas com altas taxas de referência a páginas recentemente acessadas. 

 4. Aleatório: 

O algoritmo Aleatório simplesmente seleciona uma página aleatória para substituir. É uma abordagem básica que não leva em consideração o histórico de acesso às páginas. Em média, o desempenho do algoritmo aleatório é razoável, mas pode variar dependendo da sorte dos acessos. Em alguns casos, pode apresentar resultados comparáveis aos demais algoritmos, enquanto em outros casos pode ter um desempenho inferior. 

 Em resumo, a escolha do melhor algoritmo de substituição de página depende das características do programa e do padrão de acesso à memória. Não há um algoritmo universalmente superior em todas as situações. É importante realizar testes e análises específicas para cada programa a fim de determinar qual algoritmo proporcionará o melhor desempenho. 
