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
 *      Variaveis a serem adicionadas (distribuir pontos entre elas):
 *          - Velocidade
 *          - Taxa de conversao de comida em massa
 *              blob.r = math.sqrt(blob.mass / math.pi)
 *          - 
 * 
*/

vector<Bolinha> players;

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

    Bolinha b1(0.1, -0.8, 0, 0, 0, 0.8, 1, 0);
    Bolinha b2(0.15, 0.8, 0, 0, 0.8, 0, -1, 0);

    players.push_back(b1);
    players.push_back(b2);

}

void draw() {
    
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i=0; i<players.size(); i++) {
        players[i].Draw();
    }

    glutSwapBuffers();

}

void timer(int) {

    for(int i=0; i<players.size(); i++) {
        players[i].Move();
        players[i].Collide(players);
    }

    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0); // 60Hz

}