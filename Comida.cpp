/**
 * USP Sao Carlos, ICMC
 * Agario Evolutivo
 * 
 * Classe da comida
 * 
 * @author Andre Santana Fernandes <11208537>
 * @author Diogo Castanho Emídio <11297274>
 * @author Leonardo Antonetti da Motta <11275338>
 * @author Marcus Vinicius Santos Rodrigues <11218862>
 * @author Olavo Morais Borges Pereira <11297792>
 * 
*/

#include "Comida.h"
#define CIRCLE_SEGMENTS 8
#define MASS 0.0005

using namespace std;

void DrawCircle_(double cx, double cy, double r, int num_segments) {

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < num_segments; i++) {

        double theta = 2.0f * 3.1415926f * double(i) / double(num_segments); //get the current angle 
        double x = r * cosf(theta); //calculate the x component 
        double y = r * sinf(theta); //calculate the y component 
        glVertex2f(x + cx, y + cy); //output vertex 

    }

    glEnd();

}

Comida::Comida(double _x, double _y, double _r, double _g, double _b, vector<Comida>& comidas) {
    
    mass = MASS;
    x = _x;
    y = _y;
    r = _r; g = _g; b = _b;
    active = true;

    comidas.push_back(*this);

}

double Comida::Radius() {

    double pi = 2 * acos(0.0);
    double radius = sqrt( mass / pi );

    return radius;

}

void Comida::Draw() {

    glColor3f(r, g, b);
    DrawCircle_(x, y, Radius(), CIRCLE_SEGMENTS);
    glEnd();

}

bool Comida::isActive() {

    return this->active;

}

void Comida::setActive(bool active) {

    this->active = active;

}