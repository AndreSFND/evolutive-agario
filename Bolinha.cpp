/**
 * USP Sao Carlos, ICMC
 * Agario Evolutivo
 * 
 * Classe dos personagens, que sao capazes de se mover e absorver outros personagens e comidas
 * 
 * @author Andre Santana Fernandes <11208537>
 * @author Diogo Castanho Emídio <11297274>
 * @author Leonardo Antonetti da Motta <11275338>
 * @author Marcus Vinicius Santos Rodrigues <11218862>
 * @author Olavo Morais Borges Pereira <11297792>
 * 
*/

#include "Bolinha.h"
#define circleSegments 8

using namespace std;

void DrawCircle(float cx, float cy, float r, int num_segments) {

    glBegin(GL_LINE_LOOP);

    for (int ii = 0; ii < num_segments; ii++) {

        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle 
        float x = r * cosf(theta); //calculate the x component 
        float y = r * sinf(theta); //calculate the y component 
        glVertex2f(x + cx, y + cy); //output vertex 

    }

    glEnd();

}

Bolinha::Bolinha(float _radius, float _x, float _y, float _r, float _g, float _b, float _horizontal, float _vertical) {
    
    radius = _radius;
    x = _x;
    y = _y;
    r = _r; g = _g; b = _b;
    horizontal = _horizontal;
    vertical = _vertical;

}

void Bolinha::Draw() {

    glColor3f(r, g, b);
    DrawCircle(x, y, radius, circleSegments);
    glEnd();

}

void Bolinha::Move() {

    // Move o personagem
    x += horizontal / 100;
    y += vertical / 100;

    // Impede que o personagem saia da tela
    x = x > 1 || x < -1 ? x*-1 : x;
    y = y > 1 || y < -1 ? y*-1 : y;

}

void Bolinha::Collide(vector<Bolinha>& players) {

    for(int i=0; i<players.size(); i++) {

        if( &(players[i]) != this ) {

            float distance = sqrt(pow(players[i].x - x, 2) + pow(players[i].y - y, 2) * 1.0);

            // Se estao colidindo
            if( distance < radius + players[i].radius ) {

                if( radius > players[i].radius ) {

                    radius += players[i].radius;
                    players.erase(players.begin() + i);

                }

            }

        }
        
    }

}