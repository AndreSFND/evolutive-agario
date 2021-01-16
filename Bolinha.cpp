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
#define PI 3.1415

using namespace std;

void DrawCircle(float cx, float cy, float r, int num_segments) {

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < num_segments; i++) {

        float theta = 2.0f * PI * float(i) / float(num_segments); //get the current angle 
        float x = r * cosf(theta); //calculate the x component 
        float y = r * sinf(theta); //calculate the y component 
        glVertex2f(x + cx, y + cy); //output vertex 

    }

    glEnd();

}

Bolinha::Bolinha(double _axonsIn[][N_NEURONS], double _axonsOut[][N_OUTPUTS], float _mass, float _x, float _y, float _r, float _g, float _b, float _horizontal, float _vertical, vector<Bolinha>& players) {
    
    mass = _mass;
    x = _x;
    y = _y;
    r = _r; g = _g; b = _b;
    horizontal = _horizontal;
    vertical = _vertical;

    closestFood = NULL;
    closestEnemy = NULL;

    double _inputs[] = {0, 0, 0, 0, 0, 0};
	double _biasNeuron = 0;
	double _biasOutput = 0;

    redeNeural = new RedeNeural(_inputs, _biasNeuron, _biasOutput);
    redeNeural->setAxonsIn(_axonsIn);
    redeNeural->setAxonsOut(_axonsOut);

    players.push_back(*this);

}

float Bolinha::Mass() {

    return mass;

}

float Bolinha::Radius() {

    float radius = sqrt( mass / PI );

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

    double _inputs[] = { DistanceToClosestEnemy(), AngleToClosestEnemy(), ClosestEnemyMass(), Mass(), DistanceToClosestFood(), AngleToClosestFood() };  
    redeNeural->setInput(_inputs);
    redeNeural->feedForward();

    double *_outputs = redeNeural->getOutput();

    horizontal = (_outputs[0] * 2) - 1;
    vertical = (_outputs[1] * 2) - 1;

    // if( angle == 0 ) {

    //     horizontal = 1;
    //     vertical = 0;

    // } else if( angle > 0 && angle < 90 ) {

    //     horizontal = 1;
    //     vertical = 1;

    // } else if( angle == 90 ) {

    //     horizontal = 0;
    //     vertical = 1;

    // } else if( angle > 90 && angle < 180 ) {

    //     horizontal = -1;
    //     vertical = 1;

    // } else if( angle == 180 ) {

    //     horizontal = -1;
    //     vertical = 0;

    // } else if( angle > 180 && angle < 270 ) {

    //     horizontal = -1;
    //     vertical = -1;

    // } else if( angle == 270 ) {

    //     horizontal = 0;
    //     vertical = -1;

    // }  else if( angle > 270 && angle < 360 ) {

    //     horizontal = 1;
    //     vertical = -1;

    // } else {

    //     horizontal = 0;
    //     vertical = 0;

    // }

    // Move o personagem
    x += horizontal * Speed() / 500;
    y += vertical * Speed() / 500;

    // Impede que o personagem saia da tela
    x = x > 1 || x < -1 ? x*-1 : x;
    y = y > 1 || y < -1 ? y*-1 : y;

}

void Bolinha::Collide(vector<Bolinha>& players) {

    int playersLength = players.size();
    float currentDistance = 0;

    if( playersLength > 0 ) {

        for(int i=0; i<playersLength; i++) {

            if( &(players[i]) != this ) {

                float distance = sqrt(pow(players[i].x - x, 2) + pow(players[i].y - y, 2) * 1.0);

                if( currentDistance == 0 ) {

                    closestEnemy = &players[i];
                    currentDistance = distance;

                } else if( distance < currentDistance ) {

                    closestEnemy = &players[i];
                    currentDistance = distance;

                }

                // Se estao colidindo
                if( (distance*2) < Radius() + players[i].Radius() ) {

                    if( mass > players[i].mass ) {

                        mass += players[i].mass;
                        players.erase(players.begin() + i);

                    }

                }

            }
            
        }

    } else {

        closestEnemy = NULL;

    }

}

void Bolinha::Collide(vector<Comida>& comidas) {

    closestFood = &comidas[0];
    float currentDistance = sqrt(pow((*closestFood).x - x, 2) + pow((*closestFood).y - y, 2) * 1.0);

    int comidasLength = comidas.size();

    if( comidasLength > 0 ) {

        for(int i=0; i<comidasLength; i++) {

            float distance = sqrt(pow(comidas[i].x - x, 2) + pow(comidas[i].y - y, 2) * 1.0);

            if( distance < currentDistance ) {

                closestFood = &comidas[i];
                currentDistance = distance;

            }

            // Se estao colidindo
            if( distance < Radius() + comidas[i].Radius() ) {

                mass += comidas[i].mass;
                comidas.erase(comidas.begin() + i);

            }
            
        }

    } else {

        closestFood = NULL;

    }

}

float Bolinha::DistanceToClosestFood() {

    float currentDistance = sqrt(pow((*closestFood).x - x, 2) + pow((*closestFood).y - y, 2) * 1.0);

    return currentDistance;

}

float Bolinha::AngleToClosestFood() {

    if( closestFood != NULL ) {

        float dx = (*closestFood).x - x;
        float dy = (*closestFood).y - y;

        float inRads = atan2(dy, dx);
        float angle = inRads * 180.0 / PI;

        if(angle < 0) angle += 360;

        return angle;

    } else {

        return -1;

    }

}

float Bolinha::DistanceToClosestEnemy() {

    float currentDistance = sqrt(pow((*closestEnemy).x - x, 2) + pow((*closestEnemy).y - y, 2) * 1.0);

    return currentDistance;

}

float Bolinha::AngleToClosestEnemy() {

    if( closestEnemy != NULL ) {

        float dx = (*closestEnemy).x - x;
        float dy = (*closestEnemy).y - y;

        float inRads = atan2(dy, dx);
        float angle = inRads * 180.0 / PI;

        if(angle < 0) angle += 360;

        return angle;

    } else {

        return -1;

    }

}

float Bolinha::ClosestEnemyMass() {

    float mass = (*closestEnemy).mass;

    return mass;

}
