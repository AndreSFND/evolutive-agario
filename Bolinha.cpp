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
#define CIRCLE_SEGMENTS 8

using namespace std;

void DrawCircle(float cx, float cy, float r, int num_segments) {

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < num_segments; i++) {

        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); //get the current angle 
        float x = r * cosf(theta); //calculate the x component 
        float y = r * sinf(theta); //calculate the y component 
        glVertex2f(x + cx, y + cy); //output vertex 

    }

    glEnd();

}

Bolinha::Bolinha(float _mass, float _x, float _y, float _r, float _g, float _b, float _horizontal, float _vertical, vector<Bolinha>& players) {
    
    mass = _mass;
    x = _x;
    y = _y;
    r = _r; g = _g; b = _b;
    horizontal = _horizontal;
    vertical = _vertical;

    players.push_back(*this);

}

float Bolinha::Radius() {

    float pi = 2 * acos(0.0);
    float radius = sqrt( mass / pi );

    return radius;

}

float Bolinha::Speed() {

    float speed = pow(Radius(), -0.439) * 2.2;

    return speed;

}

void Bolinha::Draw() {

    glColor3f(r, g, b);
    DrawCircle(x, y, Radius(), CIRCLE_SEGMENTS);
    glEnd();

}

void Bolinha::Move() {

    // Move o personagem
    x += horizontal * Speed() / 500;
    y += vertical * Speed() / 500;

    // Impede que o personagem saia da tela
    x = x > 1 || x < -1 ? x*-1 : x;
    y = y > 1 || y < -1 ? y*-1 : y;

}

void Bolinha::Collide(vector<Bolinha>& players) {

    for(int i=0; i<players.size(); i++) {

        if( &(players[i]) != this ) {

            float distance = sqrt(pow(players[i].x - x, 2) + pow(players[i].y - y, 2) * 1.0);

            // Se estao colidindo
            if( (distance*2) < Radius() + players[i].Radius() ) {

                if( mass > players[i].mass ) {

                    mass += players[i].mass;
                    players.erase(players.begin() + i);

                }

            }

        }
        
    }

}

void Bolinha::Collide(vector<Comida>& comidas) {

    for(int i=0; i<comidas.size(); i++) {

        float distance = sqrt(pow(comidas[i].x - x, 2) + pow(comidas[i].y - y, 2) * 1.0);

        // Se estao colidindo
        if( distance < Radius() + comidas[i].Radius() ) {

            mass += comidas[i].mass;
            comidas.erase(comidas.begin() + i);

        }
        
    }

}