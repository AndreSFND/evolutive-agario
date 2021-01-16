// Leonardo Antonetti da Motta - ICMC USP 11275338

#include <iostream> 
#include <vector>
#include <list>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MIN_AXON -1
#define MAX_AXON 1
//#define ESCOPO_DECIMAL_AXON 100

#define N_INPUTS 6
#define N_NEURONS 4
#define N_OUTPUTS 2

class RedeNeural {

    private:
        typedef struct 
		{
			double axonsIn[N_INPUTS][N_NEURONS]; // [x][y] -> [x] eh para o input, signifca qual input veio, [y] eh para neuronio, signifca para qual neuronio vai
			double axonsOut[N_NEURONS][N_OUTPUTS]; // [x][y] -> [x] eh para o neuronio, signifca qual neuronio veio, [y] eh para output, signifca para qual output vai
		} structAxons;

    	double input[N_INPUTS], output[N_OUTPUTS];
        double neuron[N_NEURONS];
		structAxons axons;
        double biasNeuron, biasOutput;

    public:
        RedeNeural(double _input[], double _biasNeuron, double _biasOutput);
		
		double* getInput();
		double* getOutput();
		structAxons getAxons();
		double* getNeuron();
		double getBiasNeuron();
		double getBiasOutput();
		
		void setInput(double _input[]);
		void setOutput(double _output[]);
		void setAxonsIn(double _axonsIn[][N_NEURONS]);
		void setAxonsOut(double _axonsOut[][N_OUTPUTS]);
		void setNeuron(double _neuron[]);
		void setBiasNeuron(double _biasNeuron);
		void setBiasOutput(double _biasOutput);
		
		void populateAxons();
		double sigmoid(double x);
		
		void activatingFunction(double source[], int size);
		double feedForward();
		void printExample();

};