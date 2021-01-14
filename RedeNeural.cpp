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

#include "RedeNeural.h"

using namespace std;

RedeNeural::RedeNeural(float _mass, float _x, float _y, float _r, float _g, float _b, float _horizontal, float _vertical, vector<Bolinha>& players) {
    
    mass = _mass;
    x = _x;
    y = _y;
    r = _r; g = _g; b = _b;
    horizontal = _horizontal;
    vertical = _vertical;

    players.push_back(*this);

}