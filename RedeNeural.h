/**
 * USP Sao Carlos, ICMC
 * Agario Evolutivo
 * 
 * Classe da rede neural
 * 
 * @author Andre Santana Fernandes <11208537>
 * @author Diogo Castanho Emídio <11297274>
 * @author Leonardo Antonetti da Motta <11275338>
 * @author Marcus Vinicius Santos Rodrigues <11218862>
 * @author Olavo Morais Borges Pereira <11297792>
 * 
*/
#ifndef REDENEURAL_H
#define REDENEURAL_H

    #ifdef __APPLE__
        #include <GLUT/glut.h>
    #else
        #include <GL/glut.h>
    #endif

    #include <iostream>
    #include <vector>

    using namespace std;

    class RedeNeural {

        private:
            float r,g,b;
            float horizontal;
            float vertical;

        public:
            float x;
            float y;
            float mass;

            RedeNeural(float _mass, float _x, float _y, float _r, float _g, float _b, float _horizontal, float _vertical, vector<Bolinha>& players);

            float Radius();
            float Speed();

    };

#endif