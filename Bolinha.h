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
    #include "Comida.h"
    #include "RedeNeural.h"

    using namespace std;

    class Bolinha {

        private:
            double r,g,b;
            double horizontal;
            double vertical;
            bool active;
            Comida *closestFood;
            Bolinha *closestEnemy;

        public:
            double x;
            double y;
            double mass;
            RedeNeural *redeNeural;

            Bolinha(double _mass, double _x, double _y, double _r, double _g, double _b, double _horizontal, double _vertical, vector<Bolinha>& players);
            Bolinha(double _axonsIn[][N_NEURONS], double _axonsOut[][N_OUTPUTS], double _mass, double _x, double _y, double _r, double _g, double _b, double _horizontal, double _vertical, vector<Bolinha>& players);

            double Mass();
            double Radius();
            double Speed();

            void Draw();
            void Move();
            void Collide(vector<Bolinha>& players);
            void Collide(vector<Comida>& comidas);

            double DistanceToClosestFood();
            double AngleToClosestFood();

            double DistanceToClosestEnemy();
            double AngleToClosestEnemy();
            double ClosestEnemyMass();

            bool isActive();
            void setActive(bool active);

    };

#endif