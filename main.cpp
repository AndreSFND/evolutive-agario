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

using namespace std;

#define windowWidth 600
#define windowHeight 600
#define windowPositionX 383
#define windowPositionY 84

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
 *              blob.r = math.sqrt(blob.mass / math.pi)
 *          - 
 * 
 *      Variaveis input rede neural:
 *          - Distancia do inimigo mais proximo
 *          - Angulo entre personagem e inimigo mais proximo
 *          - Massa do inimigo mais proximo
 * 
 *          - Massa do personagem
 *          - Distancia da comida mais proxima
 *          - Angulo entre personagem e comida mais proxima
 * 
*/

vector<Comida> comidas;
vector<Bolinha> players;
int ticks = 0;

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

void initialize() {

    new Bolinha(0.01, -0.8, 0, 0, 0, 0.8, 1, 0, players);
    new Bolinha(0.02, 0.8, 0, 0, 0.8, 0, 0, 1, players);

    for(int i=0; i<40; i++) {

        float x = ((rand() % 200) / 100.0) - 1;
        float y = ((rand() % 200) / 100.0) - 1;

        new Comida(x, y, 0.8, 0, 0.8, comidas);

    }

}

void destroy() {

    players.clear();
    comidas.clear();

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

    if(ticks > 500) {

        ticks = 0;

        destroy();

        initialize();
        glutTimerFunc(0, timer, 0);
        
        return;

    }

    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0); // 60Hz

}