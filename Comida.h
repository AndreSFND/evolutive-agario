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
            double r,g,b;

        public:
            double x;
            double y;
            double mass;

            Comida(double _x, double _y, double _r, double _g, double _b, vector<Comida>& comidas);

            double Radius();

            void Draw();

    };

#endif