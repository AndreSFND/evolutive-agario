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

void DrawCircle_(float cx, float cy, float r, int num_segments) {

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < num_segments; i++) {

        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); //get the current angle 
        float x = r * cosf(theta); //calculate the x component 
        float y = r * sinf(theta); //calculate the y component 
        glVertex2f(x + cx, y + cy); //output vertex 

    }

    glEnd();

}

Comida::Comida(float _x, float _y, float _r, float _g, float _b, vector<Comida>& comidas) {
    
    mass = MASS;
    x = _x;
    y = _y;
    r = _r; g = _g; b = _b;

    comidas.push_back(*this);

}

float Comida::Radius() {

    float pi = 2 * acos(0.0);
    float radius = sqrt( mass / pi );

    return radius;

}

void Comida::Draw() {

    glColor3f(r, g, b);
    DrawCircle_(x, y, Radius(), CIRCLE_SEGMENTS);
    glEnd();

}