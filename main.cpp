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

#include <iostream>
#include <vector>
#include "Comida.h"
#include "Bolinha.h"
#include "RedeNeural.h"

using namespace std;

#define windowWidth 600
#define windowHeight 600
#define windowPositionX 383
#define windowPositionY 84
#define fps 60

#define nPlayers 10
#define timeLimit 500

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
 *          - 
 * 
 *      Se acaba o tempo:
 *          -Faz suruba com até 3 vencedores
 * 
 *          Bolinhas restantes (quando acaba o tempo) = números de pais = 3;
 *          Vencedor = 1 (sempre) = a;
 *          Filhos = (0,25 * a + 0,25 * b + 0,5 * aleatório) / 3,  (0,25 * a + 0,25 * c + 0,5 * aleatório) / 3, ..., (0,25 * a + 0,25 * n + 0,5 * aleatório) / 3
 *      
 *      Senao:
 *          -Roda o elitismo
 *          
 * 
*/

vector<Comida> comidas;
vector<Bolinha> players;
vector<Bolinha> winners;
int ticks = 0;


// Roda ao iniciar a partida
void initialize() {

    for(int i=0; i<nPlayers; i++) {

        if( winners.size() <= 0 ) {

            new Bolinha(0.01, -0.2 * i, -0.2 * i, 0, 0, 0.8, 1, 0, players);

        } else { // Se existem vencedores da ultima partida, faz o cruzamento
            
            new Bolinha(0.01, -0.2 * i, -0.2 * i, 0.8, 0, 0, 1, 0, players);

        }

    }

    for(int i=0; i<nPlayers*10; i++) {

        float x = ((rand() % 200) / 100.0) - 1;
        float y = ((rand() % 200) / 100.0) - 1;

        new Comida(x, y, 0.8, 0, 0.8, comidas);

    }

    winners.clear();

}

// Roda ao acabar a partida
void destroy() {

    int playersLength = players.size();
    float maxMass = 0;
    Bolinha *winner;

    for(int i=0; i<playersLength; i++) {

        if( players[i].Mass() > maxMass ) {

            winner = &players[i];
            maxMass = players[i].Mass();

        }

    }

    winners.push_back(*winner);

    players.clear();
    comidas.clear();

}

int main(int argc, char** argv) {
	
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

    for(int i=0; i<comidas.size(); i++) {
    
        comidas[i].Draw();
    
    }

    for(int i=0; i<players.size(); i++) {
    
        players[i].Draw();
    
    }

    glutSwapBuffers();

}

void timer(int) {

    for(int i=0; i<players.size(); i++) {
    
        players[i].Collide(players);
        players[i].Collide(comidas);
        players[i].Move();
    
    }

    ticks++;

    if( ticks > timeLimit || players.size() < 2 ) {

        ticks = 0;

        destroy();

        initialize();
        glutTimerFunc(0, timer, 0);
        
        return;

    }

    glutPostRedisplay();
    glutTimerFunc(1000/fps, timer, 0); // 60Hz

}