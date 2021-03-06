/**
 * USP Sao Carlos, ICMC
 * Agario Evolutivo
 * 
 * O jogo, que utiliza OpenGL, simula varias partidas do jogo Agar.io, cruzando os individuos que sobrevivem por mais tempo e 
 * gerando um que sempre consiga vencer. 
 * 
 * @author Andre Santana Fernandes <11208537>
 * @author Diogo Castanho Emídio <11297274>
 * @author Leonardo Antonetti da Motta <11275338>
 * @author Marcus Vinicius Santos Rodrigues <11218862>
 * @author Olavo Morais Borges Pereira <11297792>
 * 
*/

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
#include "Comida.h"
#include "Bolinha.h"

using namespace std;

#define windowWidth 600
#define windowHeight 600
#define windowPositionX 383
#define windowPositionY 84
#define fps 60

#define nPlayers 10
#define timeLimit 2000

void initialize();
void draw();
void timer(int);

/**
 *  TODO:
 *      Cruzamento in game
 *          - Duas bolinhas cruzam na hora
 *  
 *      Variaveis a serem adicionadas (distribuir pontos entre elas):
 *          - Velocidade
 *          - Taxa de conversao de comida em massa
 * 
 *      Variaveis input rede neural:
 *          - Distancia do inimigo mais proximo
 *          - Angulo entre personagem e inimigo mais proximo
 *          - Massa do inimigo mais proximo
 *          - Massa do personagem
 *          - Distancia da comida mais proxima
 *          - Angulo entre personagem e comida mais proxima
 * 
 *      Elitismo:
 *          - Quem ganha cruza com todo mundo; os filhos substituem todos, menos ele
 * 
 *      Torneio de 2:
 *          - Selecionados 2 aleatoriamente para lutarem; vencedor eh o pai; o mesmo ocorre para a mae
 * 
 *      Opcoes de cruzamento decorrentes do elitismo (ambas descartadas), para os casos de 1, 2 ou 3 bolinhas restantes (aplicando-se para qualquer quantidade que seja):
 *          - Opcao 1:
 *              Bolinhas restantes (quando acaba o tempo) = 1 -> numeros de pais = 2;
 *              Numero de vencedores = 1 -> vencedor = a;
 *              n = total - 1;
 *              Filhos = ((a + b) / 2),  ((a + c) / 2), ..., ((a + n) / 2)
 *
 *              Bolinhas restantes (quando acaba o tempo) = 2 -> numeros de pais = 3;
 *              Numero de vencedores = 2 -> vencedores = a, b;
 *              n = total - 2;
 *              Filhos = ((a + b + c) / 3), ((a + b + d) / 3), ..., ((a + b + n) / 3)
 *
 *              Bolinhas restantes (quando acaba o tempo) = 3 -> numeros de pais = 4;
 *              Numero de vencedores = 3 -> vencedores = a, b, c;
 *              n = total - 3;
 *              Filhos = ((a + b + c + d) / 4), ((a + b + c + e) / 4), ..., ((a + b + c + n) / 4)
 *          - Opcao 2:
 *              Bolinhas restantes (quando acaba o tempo) = 1 -> numeros de pais = 2;
 *              Numero de vencedores = 1 -> vencedor = a;
 *              n = total - 1;
 *              Filhos = ((a + b) / 2),  ((a + c) / 2), ..., ((a + n) / 2)
 *
 *              Bolinhas restantes (quando acaba o tempo) = 2 -> numeros de pais = 3;
 *              Numero de vencedores = 1 -> vencedor = a;
 *              n = total - 1;
 *              Filhos = (0,5 * a + 0,25 * b + 0,25 * aleatorio),  (0,5 * a + 0,25 * c + 0,25 * aleatorio), ..., (0,5 * a + 0,25 * n + 0,25 * aleatorio)
 *
 *              Bolinhas restantes (quando acaba o tempo) = 3 -> numeros de pais = 4;
 *              Numero de vencedores = 1 -> vencedor = a;
 *              n = total - 1;
 *              Filhos = (0,5 * a + 0,25 * b + 0,125 * aleatorio + 0,125 * aleatorio),  (0,5 * a + 0,25 * c + 0,125 * aleatorio + 0,125 * aleatorio), ..., (0,5 * a + 0,25 * n + 0,125 * aleatorio + 0,125 * aleatorio)
 *              XOU
 *              Filhos = (0,5 * a + 0,5 * (b + aleatorio + aleatorio) / 3),  (0,5 * a + 0,5 * (c + aleatorio + aleatorio) / 3), ..., (0,5 * a + 0,5 * (n + aleatorio + aleatorio) / 3)
 *      
 * 
*/

// Vetores que salval as comidas, players e vencedores da partida
vector<Comida> comidas;
vector<Bolinha> players;
vector<Bolinha> winners;

// Tick e geracao atual
int ticks = 0;
int geracao = 1;

// Conta a quantidade de jogadores vivos
int countActivePlayers() {

    int activePlayers = 0;

    for(int i=0; i<nPlayers; i++) {

        if(players[i].isActive())
            activePlayers++;

    }

    return activePlayers;

}

// Gera um numero aleatorio
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Roda ao iniciar a partida
void initialize() {

    // Imprime a geracao atual
    printf("GERACAO %d\n", geracao++);

    // Inicializa os axons da rede neural
    double axonsIn[N_INPUTS][N_NEURONS];
    double axonsOut[N_NEURONS][N_OUTPUTS];

    // Se nao houverem vencedores, inicializa a partida com axons aleatorios
    if( winners.size() <= 0 ) {

        int counter = 0;

        for(int i=0; i<nPlayers; i++) {

            for( int j=0; j<N_INPUTS; j++ ) {

                for( int k=0; k<N_NEURONS; k++ ) {

                    axonsIn[j][k] = fRand(MIN_AXON, MAX_AXON);

                }

            }

            for( int j=0; j<N_NEURONS; j++ ) {

                for( int k=0; k<N_OUTPUTS; k++ ) {

                    axonsOut[j][k] = fRand(MIN_AXON, MAX_AXON);

                }

            }
            
            new Bolinha(axonsIn, axonsOut, 0.001, (0.1 * i)-0.5, (0.1 * i)-0.5, 1, 0, 1, 1, 0, players);

        }
        
    } else { // Se houverem vencedores da ultima partida, faz o cruzamento (elitismo)

        // Move os jogadores atuais para outro vetor 
        vector<Bolinha> oldGen(players);

        // Limpa o vetor de jogadores atuais
        players.clear();

        // Pega os axons do vencedor
        RedeNeural::structAxons winnerAxons = winners[0].redeNeural->getAxons();

        for(int i=0; i<nPlayers; i++) {

            // Pega os axons do jogador da ultima geracao
            RedeNeural::structAxons playerAxons = oldGen[i].redeNeural->getAxons();

            for( int j=0; j<N_INPUTS; j++ ) {

                for( int k=0; k<N_NEURONS; k++ ) {

                    // Cruza o vencedor com o jogador da ultima geracao
                    double axon = ( ( playerAxons.axonsIn[j][k] + winnerAxons.axonsIn[j][k] ) / 2 ) + fRand(-1, 1);
                    if( playerAxons.axonsIn[j][k] == winnerAxons.axonsIn[j][k] ) axon = winnerAxons.axonsIn[j][k];

                    axonsIn[j][k] = axon;

                }

            }

            for( int j=0; j<N_NEURONS; j++ ) {

                for( int k=0; k<N_OUTPUTS; k++ ) {

                    // Cruza o vencedor com o jogador da ultima geracao
                    double axon = ( ( playerAxons.axonsOut[j][k] + winnerAxons.axonsOut[j][k] ) / 2 ) + fRand(-1, 1);
                    if( playerAxons.axonsOut[j][k] == winnerAxons.axonsOut[j][k] ) axon = winnerAxons.axonsOut[j][k];

                    axonsOut[j][k] = axon;

                }

            }
            
            new Bolinha(axonsIn, axonsOut, 0.001, (0.1 * i)-0.5, (0.1 * i)-0.5, 1, 0, 1, 1, 0, players);

        }

        oldGen.clear();
        winners.clear();
        winners.reserve(0);

    }

    // Cria as comidas em locais aleatorios
    for(int i=0; i<nPlayers*5; i++) {

        double x = ((rand() % 200) / 100.0) - 1;
        double y = ((rand() % 200) / 100.0) - 1;

        new Comida(x, y, 0.8, 0, 0.8, comidas);

    }

}

// Roda ao acabar a partida
void destroy() {

    int playersLength = players.size();
    double maxMass = 0;
    Bolinha *winner;

    // Busca pelo vencedor
    for(int i=0; i<playersLength; i++) {

        if( players[i].isActive() && players[i].Mass() > maxMass ) {

            winner = &players[i];
            maxMass = players[i].Mass();

        }

    }

    // Imprime os dados do vencedor
    printf("Winner stats: \n \tmass = %f\n", winner->mass);

    winners.push_back(*winner);
    comidas.clear();

}

int main(int argc, char** argv) {

    srand( time(NULL) );

    players.reserve( nPlayers );
    initialize();

    // Initialize window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPositionX, windowPositionY);
    glutCreateWindow("Evolutive Agario");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(draw);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;

}

void draw() {
    
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha as comidas ativas
    for(int i=0; i<comidas.size(); i++) {
    
        if( comidas[i].isActive() ) comidas[i].Draw();
    
    }

    // Desenha os jogadores ativos/vivos
    for(int i=0; i<players.size(); i++) {
    
        if( players[i].isActive() ) players[i].Draw();
    
    }

    glutSwapBuffers();

}

void timer(int) {

    for(int i=0; i<players.size(); i++) {
    
        if( players[i].isActive() ) {
            
            // Calcula a colisao do jogador com as comidas e outros jogadores
            players[i].Collide(players);
            players[i].Collide(comidas);

            // Move o jogador
            players[i].Move();

        }
    
    }

    ticks++;

    // Se o tempo tiver acabado ou houver apenas 1 jogador, finaliza a partida
    if( ticks > timeLimit || countActivePlayers() == 1 ) {

        ticks = 0;

        destroy();

        initialize();
        glutTimerFunc(0, timer, 0);
        
        return;

    }

    glutPostRedisplay();
    glutTimerFunc(1000/fps, timer, 0); // 60Hz

}
