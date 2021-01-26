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
            double r,g,b;           // Cor
            double horizontal;      // Movimentacao horizontal
            double vertical;        // Movimentacao vertical
            bool active;            // Esta vivo
            Comida *closestFood;    // Comida mais proxima
            Bolinha *closestEnemy;  // Inimigo mais proximo

        public:
            double x;   // x
            double y;   // y
            double mass;    // massa
            RedeNeural *redeNeural; // Rede neural

            // Construtor
            Bolinha(double _axonsIn[][N_NEURONS], double _axonsOut[][N_OUTPUTS], double _mass, double _x, double _y, double _r, double _g, double _b, double _horizontal, double _vertical, vector<Bolinha>& players);

            double Mass();      // Retorna a massa
            double Radius();    // Calcula o raio com base na massa
            double Speed();     // Calcula a velocidade com base na massa

            void Draw();    // Desenha
            void Move();    // Move o jogador
            void Collide(vector<Bolinha>& players); // Calcula a colisao com outros jogadores
            void Collide(vector<Comida>& comidas);  // Calcula a colisao com outras comidas

            double DistanceToClosestFood(); // Calcula a distancia ate a comida mais proxima
            double AngleToClosestFood();    // Calcula o angulo ate a comida mais proxima

            double DistanceToClosestEnemy(); // Calcula a distancia ate o inimigo mais proximo
            double AngleToClosestEnemy(); // Calcula o angulo ate o inimigo mais proximo
            double ClosestEnemyMass(); // Retorna a massa do inimigo mais proximo

            bool isActive(); // Verifica se esta vivo
            void setActive(bool active); // Define se esta vivo

    };

#endif