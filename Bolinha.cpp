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

// Desenha um poligono de n pontos
void DrawCircle(double cx, double cy, double r, int num_segments) {

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < num_segments; i++) {

        double theta = 2.0f * PI * double(i) / double(num_segments); //get the current angle 
        double x = r * cosf(theta); //calculate the x component 
        double y = r * sinf(theta); //calculate the y component 
        glVertex2f(x + cx, y + cy); //output vertex 

    }

    glEnd();

}

// Construtor
Bolinha::Bolinha(double _axonsIn[][N_NEURONS], double _axonsOut[][N_OUTPUTS], double _mass, double _x, double _y, double _r, double _g, double _b, double _horizontal, double _vertical, vector<Bolinha>& players) {
    
    mass = _mass;
    x = _x;
    y = _y;
    r = _r; g = _g; b = _b;
    horizontal = _horizontal;
    vertical = _vertical;
    active = true;

    closestFood = NULL;
    closestEnemy = NULL;

    // Cria a rede neural
    double _inputs[] = {0, 0, 0, 0, 0, 0};
	double _biasNeuron = 0;
	double _biasOutput = -0;

    redeNeural = new RedeNeural(_inputs, _biasNeuron, _biasOutput);
    redeNeural->setAxonsIn(_axonsIn);
    redeNeural->setAxonsOut(_axonsOut);

    players.push_back(*this);

}

double Bolinha::Mass() {

    return isnan(mass) ? 0 : mass;

}

// Calcula o raio com base na massa
double Bolinha::Radius() {

    double radius = sqrt( mass / PI );

    return isnan(radius) ? 0 : radius;

}

// Calcula a velocidade com base na massa
double Bolinha::Speed() {

    double speed = pow(Radius(), -0.439) * 2.2;

    return isnan(speed) ? 0 : speed;

}

// Desenha o poligono
void Bolinha::Draw() {

    glColor3f(r, g, b);
    DrawCircle(x, y, Radius(), CIRCLE_SEGMENTS);
    glEnd();

}

// Joga os inputs na rede neural e move o personagem segundo o output
void Bolinha::Move() {

    double _inputs[] = { DistanceToClosestEnemy(), AngleToClosestEnemy() / 180, ClosestEnemyMass(), Mass(), DistanceToClosestFood(), AngleToClosestFood() / 180 };  
    redeNeural->setInput(_inputs);
    redeNeural->feedForward();

    double *_outputs = redeNeural->getOutput();

    horizontal = ( _outputs[0] * 2 ) - 1;
    vertical = ( _outputs[1] * 2 ) - 1;

    RedeNeural::structAxons playerAxons = redeNeural->getAxons();

    // Move o personagem
    x += horizontal * Speed() / 500;
    y += vertical * Speed() / 500;

    // Impede que o personagem saia da tela
    x = x > 1 || x < -1 ? x*-1 : x;
    y = y > 1 || y < -1 ? y*-1 : y;

    // x = x + Radius() > 1 ? 1 - Radius() : x;
    // x = x - Radius() < -1 ? -1 + Radius() : x;

    // y = y + Radius() > 1 ? 1 - Radius() : y;
    // y = y - Radius() < -1 ? -1 + Radius() : y;

}

// Calcula a colisao do personagem com outros personagens
// Define o inimigo mais proximo
void Bolinha::Collide(vector<Bolinha>& players) {

    int playersLength = players.size();
    double currentDistance = -1;

    if( playersLength > 0 ) {

        for(int i=0; i<playersLength; i++) {

            if( &(players[i]) != this && players[i].isActive() ) {

                double distance = sqrt(pow(players[i].x - x, 2) + pow(players[i].y - y, 2) * 1.0);

                if( currentDistance == -1 ) {

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
                        players[i].setActive(false);
                        // players.erase(players.begin() + i);

                    }

                }

            }
            
        }

    } else {

        closestEnemy = NULL;

    }

}

// Calcula a colisao do personagem com comidas
// Define a comida mais proxima
void Bolinha::Collide(vector<Comida>& comidas) {

    int comidasLength = comidas.size();
    double currentDistance = -1;

    if( comidasLength > 0 ) {

        for(int i=0; i<comidasLength; i++) {

            if( comidas[i].isActive() ) {

                double distance = sqrt(pow(comidas[i].x - x, 2) + pow(comidas[i].y - y, 2) * 1.0);

                if( currentDistance == -1 ) {

                    closestFood = &comidas[i];
                    currentDistance = distance;

                } else if( distance < currentDistance ) {

                    closestFood = &comidas[i];
                    currentDistance = distance;

                }

                // Se estao colidindo
                if( distance < Radius() + comidas[i].Radius() ) {

                    mass += comidas[i].mass;
                    comidas[i].setActive(false);
                    // comidas.erase(comidas.begin() + i);

                }

            }
            
        }

    } else {

        closestFood = NULL;

    }

}

// Calcula a distancia ate a comida mais proxima
double Bolinha::DistanceToClosestFood() {

    if( closestFood != NULL ) {

        double currentDistance = sqrt(pow((*closestFood).x - x, 2) + pow((*closestFood).y - y, 2) * 1.0);

        return isnan(currentDistance) ? 0 : currentDistance;

    }

    return -1;

}

// Calcula o angulo ate a comida mais proxima
double Bolinha::AngleToClosestFood() {

    if( closestFood != NULL ) {

        double dx = (*closestFood).x - x;
        double dy = (*closestFood).y - y;

        double inRads = atan2(dy, dx);
        double angle = inRads * 180.0 / PI;

        if(angle < 0) angle += 360;

        return isnan(angle) ? 0 : angle;

    } else {

        return -1;

    }

}

// Calcula a distancia ate o inimigo mais proximo
double Bolinha::DistanceToClosestEnemy() {

    if( closestEnemy != NULL ) {

        double currentDistance = sqrt(pow((*closestEnemy).x - x, 2) + pow((*closestEnemy).y - y, 2) * 1.0);

        return isnan(currentDistance) ? 0 : currentDistance;

    }

    return -1;

}

// Calcula o angulo ate o inimigo mais proximo
double Bolinha::AngleToClosestEnemy() {

    if( closestEnemy != NULL ) {

        double dx = (*closestEnemy).x - x;
        double dy = (*closestEnemy).y - y;

        double inRads = atan2(dy, dx);
        double angle = inRads * 180.0 / PI;

        if(angle < 0) angle += 360;

        return isnan(angle) ? 0 : angle;

    } else {

        return -1;

    }

}

// Retorna a massa do inimigo mais proximo
double Bolinha::ClosestEnemyMass() {

    if( closestEnemy != NULL ) {

        double mass = (*closestEnemy).mass;

        return isnan(mass) ? 0 : mass;

    }

    return -1;

}

bool Bolinha::isActive() {

    return this->active;

}

void Bolinha::setActive(bool active) {

    this->active = active;

}