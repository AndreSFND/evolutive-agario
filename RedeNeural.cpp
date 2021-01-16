// Leonardo Antonetti da Motta - ICMC USP 11275338

#include <iostream> 
#include <vector>
#include <list>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "RedeNeural.h"

using namespace std;

/*
	PARA O USO DA CLASSE:
	1. 	Crie um vetor de doubles com seus inputs, o tamanho do vetor pode ser qualquer um, 
		desde que voce altere o valor da constante N_INPUTS para ficar igual a qtd de inputs
		
	2.	Cria um double que sera seu bias dos neuronios e outro para o bias dos outputs
	
	3.	Altere o numero de NEURONS e OUTPUTS a vontade, pelas constantes no comeco da classe de respectivo nome

	4.1 Instancie a classe e mande os valores dos inputs e do bias no construtor

	4.2 ATENCAO: Ao instanciar a classe, ela automaticamente randomiza os axons. Se quiser randomizar 
		os axons novamente, use a funcao populateAxons()
	
	5. Use os gets e sets a vontade, cheque cada um para ver o que eles retornam ou o que eles recebem

	6. Use a funcao feedForward() para calcular os neuronios e outputs
	
	OBS. Comente os printfs dos metodos se nao quiser que o passo-a-passo seja printado na tela
*/

// CONSTRUCTOR
RedeNeural::RedeNeural(double _input[], double _biasNeuron, double _biasOutput) 
{
	for(int i = 0; i < N_INPUTS; i++)
	{
		input[i] = _input[i];
	}
	biasNeuron = _biasNeuron;
	biasOutput = _biasOutput;
	populateAxons(); // Isso talvez seja removido depois, ja que popular os axons o usuario q faz uma vez so, e nao a cada construcao
}

// GETTERS
double* RedeNeural::getInput()
{
	return input;
}
double* RedeNeural::getOutput()
{
	return output;
}
RedeNeural::structAxons RedeNeural::getAxons()
{
	return axons;
}
double* RedeNeural::getNeuron()
{
	return neuron;
}
double RedeNeural::getBiasNeuron()
{
	return biasNeuron;
}
double RedeNeural::getBiasOutput()
{
	return biasOutput;
}

// SETTERS
void RedeNeural::setInput(double _input[])
{
	for(int i = 0; i < N_INPUTS; i++)
	{
		input[i] = _input[i];
	}
}
void RedeNeural::setOutput(double _output[])
{
	for(int i = 0; i < N_OUTPUTS; i++)
	{
		output[i] = _output[i];
	}
}
void RedeNeural::setAxonsIn(double _axonsIn[][N_NEURONS])
{
	for(int i = 0; i < N_INPUTS; i++)
	{
		for(int j = 0; j < N_NEURONS; j++)
		{
			axons.axonsIn[i][j] = _axonsIn[i][j];
		}
	}
}
void RedeNeural::setAxonsOut(double _axonsOut[][N_OUTPUTS])
{
	for(int i = 0; i < N_NEURONS; i++)
	{
		for(int j = 0; j < N_OUTPUTS; j++)
		{
			axons.axonsOut[i][j] = _axonsOut[i][j];
		}
	}
}
void RedeNeural::setNeuron(double _neuron[])
{
	for(int i = 0; i < N_NEURONS; i++)
	{
		neuron[i] = _neuron[i];
	}
}
void RedeNeural::setBiasNeuron(double _biasNeuron)
{
	biasNeuron = _biasNeuron;
}
void RedeNeural::setBiasOutput(double _biasOutput)
{
	biasOutput = _biasOutput;
}

// METODOS
void RedeNeural::populateAxons()
{
	srand( (unsigned)time(NULL) );
	
	for(int i = 0; i < N_INPUTS; i++)
	{
		for(int j = 0; j < N_NEURONS; j++)
		{
			// Randomizamos nossos Axons e dividimos eles para termos um axon decimal, que eh limitado pelos MIN_AXON e MAX_AXON
			axons.axonsIn[i][j] = (double) (rand()) / ((double) (RAND_MAX / (MAX_AXON - MIN_AXON)));
			
			// E limitamos as casas decimais. Se quiser 3 casas decimais, use 1.000 no ESCOPO_DECIMAL_AXON, e assim vai
			axons.axonsIn[i][j] = round( axons.axonsIn[i][j] * ESCOPO_DECIMAL_AXON) / ESCOPO_DECIMAL_AXON;
		}
	}
	
	for(int i = 0; i < N_NEURONS; i++)
	{
		for(int j = 0; j < N_OUTPUTS; j++)
		{
			// Randomizamos nossos Axons e dividimos eles para termos um axon decimal, que eh limitado pelos MIN_AXON e MAX_AXON
			axons.axonsOut[i][j] = (double) (rand()) / ((double) (RAND_MAX / (MAX_AXON - MIN_AXON)));
			
			// E limitamos as casas decimais. Se quiser 3 casas decimais, use 1.000 no ESCOPO_DECIMAL_AXON, e assim vai
			axons.axonsOut[i][j] = round( axons.axonsOut[i][j] * ESCOPO_DECIMAL_AXON) / ESCOPO_DECIMAL_AXON;
		}
	}
}

double RedeNeural::sigmoid(double x) // Funcao sigmoid foi usada para o caminho do feedforward, conforme visto no video
{
	return 1 / (1 + exp(-x));
}

/*double dSigmoid(double x)
{
	return x * (1 - x);
}*/

void RedeNeural::activatingFunction(double source[], int size) // Funcao de ativacao para ativar qualquer vetor de double que receber, usando sigmoid
{
	// printf("\n");
	for(int i = 0; i < size; i++)
	{
		// printf("SIGMOID: Source[%d] era %.2f... ", i, source[i]);
		source[i] = sigmoid(source[i]);
		// printf("depois da sigmoid ficou %.2f\n\n", source[i]);
	}
	//printf("\n\tSource sigmoid completa\n");
}

double RedeNeural::feedForward() // O processo de feedForward, populando os neuronios e os outputs com os calculos vistos
{
	// Calculo do valor dos neuronios conforme visto aos 11:05 de https://www.youtube.com/watch?v=d8U7ygZ48Sc
	// printf("\n\n\tFF DE NEURONIOS\n");
	for(int i = 0; i < N_NEURONS; i++) 
	{
		for(int j = 0; j < N_INPUTS; j++)
		{
			// printf("\nNEURON[%d]: Adicionando [ input[%d] * axons.axonsIn[%d][%d] >> %.2f  * %.2f ] = %.2f, totalizando... ", i, j, j, i, input[j], axons.axonsIn[j][i], input[j]*axons.axonsIn[j][i]);
			neuron[i] += input[j] * axons.axonsIn[j][i];
			// printf("%.2f\n", neuron[i]);
		}
		neuron[i] += biasNeuron;
		// printf("\nCom bias final de %.2f, totalizando %.2f (neuron[%d])\n\n", biasNeuron, neuron[i], i);
	}
	// Para os neuronios na situacao com 2 inputs e 2 neurons, 4 axonsIn, temos que...
	// neuron[0] = input[0] * axons.axonsIn[0][0] + input[1] * axons.axonsIn[1][0]
	// neuron[1] = input[0] * axons.axonsIn[0][1] + input[1] * axons.axonsIn[1][1]
	
	activatingFunction(neuron, N_NEURONS);
	
	// Calculo do valor dos neuronios conforme visto aos 13:58 de https://www.youtube.com/watch?v=d8U7ygZ48Sc
	// printf("\n\n\tFF DE OUTPUTS\n");
	for(int i = 0; i < N_OUTPUTS; i++) // A cada neuronio, faca...
	{
		for(int j = 0; j < N_NEURONS; j++) // A cada output, faca
		{
			// printf("\nOUTPUT[%d]: Adicionando [ neuron[%d] * axons.axonsOut[%d][%d] >> %.2f  * %.2f ] = %.2f, totalizando... ", i, j, j, i, neuron[j], axons.axonsOut[j][i], neuron[j]*axons.axonsOut[j][i]);
			output[i] += neuron[j] * axons.axonsOut[j][i];
			// printf("%.2f\n", output[i]);
		}
		output[i] += biasOutput;
		// printf("\nCom bias final de %.2f, totalizando %.2f (output[%d])\n\n", biasOutput, output[i], i);
	}
	// Para os outputs na situacao com 2 neurons e 2 outputs, 4 axonsOut, temos que...
	// output[0] = neuron[0] * axons.axonsOut[0][0] + neuron[1] * axons.axonsOut[1][0]
	// output[1] = neuron[0] * axons.axonsOut[0][1] + neuron[1] * axons.axonsOut[1][1]
	
	activatingFunction(output, N_OUTPUTS);

	return 0;
}

void RedeNeural::printExample() // Exemplo de caso de uso bobinho
{
	double _inputs[] = {1, 2};
	double _biasNeuron = 0;
	double _biasOutput = 0;
	RedeNeural n(_inputs, _biasNeuron, _biasOutput); 
	n.feedForward();
	
	printf("\n\n\tRESUMINDO\n\n");
	for(int i = 0; i < N_INPUTS; i++) 
		printf("Input[%d]: %.2f\n", i, n.getInput()[i]);
	printf("----\n");
	
	for(int i = 0; i < N_INPUTS; i++) 
		for(int j = 0; j < N_NEURONS; j++)
			printf("AxonIn[%d][%d]: %.2f\n", i, j, n.getAxons().axonsIn[i][j]);
	printf("----\n");
	
	for(int i = 0; i < N_NEURONS; i++) 
		printf("Neuron[%d]: %.2f\n", i, n.getNeuron()[i]);
	printf("----\n");
	
	printf("Bias Neuronio (adicionado no neuronio antes da sigmoid): %.2f\n", n.getBiasNeuron());
	printf("----\n");
	
	for(int i = 0; i < N_NEURONS; i++) 
		for(int j = 0; j < N_OUTPUTS; j++)
			printf("AxonOut[%d][%d]: %.2f\n", i, j, n.getAxons().axonsOut[i][j]);
	printf("----\n");
	
	for(int i = 0; i < N_OUTPUTS; i++) 
		printf("Output[%d]: %.2f\n", i, n.getOutput()[i]);
	printf("----\n");
	
	printf("Bias Output (adicionado no output antes da sigmoid): %.2f\n", n.getBiasOutput());
	printf("----\n");
}