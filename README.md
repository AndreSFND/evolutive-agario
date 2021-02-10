# Projeto de Sistemas Evolutivos e Aplicados à Robótica (SSC0713) - Agar.io

Andre Santana Fernandes - 11208537

Diogo Castanho Emídio - 11297274

Leonardo Antonetti da Motta - 11275338

Marcus Vinicius Santos Rodrigues - 11218862

Olavo Morais Borges Pereira - 11297792

# 1. Introdução

## 1.1 Como instalar

1. Instalar o [OpenGL](https://github.com/Brenocq/OpenGL-Tutorial);
2. Fazer o download do projeto (através do botão _Code_);
3. Digitar os comandos `make all` e `make run` no terminal para, respectivamente, compilar e iniciar o jogo;
4. Observar a execução;
5. Depois de fechar, digitar, novamente no terminal, `make clean` para limpar toda a memória alocada.

## 1.2 Sobre o projeto

Inspirado no famoso jogo homônimo, esta versão não possui jogadores nem a possibilidade de a célula se dividir. São geradas aleatoriamente, em posição e comportamento, dez unidades pelo mapa, com o único objetivo de crescer. Essa meta pode ser alcançada tanto coletando pontos, que são 5 vezes mais numerosos que os indivíduos, quanto devorando concorrentes de massa menor. Ao fim, se restar somente um, esse é considerado o vencedor, senão, o de maior tamanho. O jogo reinicia em ambos os casos.

# 2. Descrição do Software

## 2.1 Funcionamento do jogo

O jogo possui dois conceitos de computação bioinspirada: rede neural artificial e algoritmo evolutivo. O primeiro será explorado mais profundamente na próxima seção, porém é importante pontuar que é ele que comanda o movimento de cada célula.

Quanto ao segundo, que é o foco do trabalho, ele foi implementado de forma relativamente simples. Todas as gerações, com exceção da primeira, são compostas pelo vencedor da rodada anterior e seus nove descendentes, que são gerados após cruzar com cada um dos perdedores, sendo esses substituídos pelos seus filhos. Tal mecanismo é denominado elitismo.

## 2.2 Rede Neural Artificial (RNA)

Uma Rede Neural Artificial (RNA), com quatro neurônios em uma única camada, está presente em cada uma das células. Ela foi feita de forma que suas entradas sejam geradas inicialmente de forma aleatória e suas saídas ditem para onde o indivíduo irá.

Os seis _inputs_ são:
- Distância até o inimigo mais próximo;
- Ângulo em relação ao inimigo mais próximo;
- Massa do inimigo mais próximo;
- Sua própria massa;
- Distância até a comida mais próxima;
- Ângulo em relação à comida mais próxima.

A partir da segunda geração, esses valores são calculados através do produto entre a média aritmética dos de seus pais (o vencedor e um perdedor ainda sem filho) e um valor aleatório pertencente ao intervalo [-2, 2]. É válido ainda ressaltar que o peso de cada entrada é aleatório, independentemente da geração, e que a massa da célula é diretamente proporcional ao seu raio e inversamente à sua velocidade.

Os _outputs_, por sua vez, são somente dois:
- Movimento na horizontal;
- Movimento na vertical.

A função sigmoide foi a escolhida para ser a função de ativação da RNA, uma vez que é a mais utilizada para essa função e por não haver necessidades de uma mais complexa. Portanto, os valores das saídas pertencem ao intervalo [0,1], fazendo com que o indivíduo ande para a direita, para cima ou para qualquer outro sentido compreendido entre esses dois. Por fim, é necessário destacar que a RNA implementada não possui limiar de ativação, devido à simplicidade da natureza de sua aplicação.

# 3. Conclusões

**Aguardem...**

# 4. Execução e Apresentação

https://drive.google.com/file/d/1oJ_MnOE8KIa1fFsZBLMB04bxLwNnA8oe/view?usp=sharing
