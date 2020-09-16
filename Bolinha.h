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
#ifndef BOLINHA_H
#define BOLINHA_H

    #ifdef __APPLE__
        #include <GLUT/glut.h>
    #else
        #include <GL/glut.h>
    #endif

    #include <iostream>
    #include <vector>
    #include <math.h>

    using namespace std;

    class Bolinha {

        private:
            float r,g,b;
            float horizontal;
            float vertical;

        public:
            float x;
            float y;
            float mass;

            Bolinha(float _mass, float _x, float _y, float _r, float _g, float _b, float _horizontal, float _vertical);

            float Radius();
            float Speed();

            void Draw();
            void Move();
            void Collide(vector<Bolinha>& players);

    };

#endif