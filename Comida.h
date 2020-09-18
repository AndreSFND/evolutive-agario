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
#ifndef COMIDA_H
#define COMIDA_H

    #ifdef __APPLE__
        #include <GLUT/glut.h>
    #else
        #include <GL/glut.h>
    #endif

    #include <iostream>
    #include <vector>
    #include <math.h>

    using namespace std;

    class Comida {

        private:
            float r,g,b;

        public:
            float x;
            float y;
            float mass;

            Comida(float _x, float _y, float _r, float _g, float _b, vector<Comida>& comidas);

            float Radius();

            void Draw();

    };

#endif