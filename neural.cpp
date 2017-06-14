#include <iostream>
#include <cstlib>
#include <ctime>
#include <math.h>

#include "neural.h"

using namespace std;

float sigmoid(float x)
{
	return 1/(1+pow(2.71828, -x));
}

Perceptron::Perceptron(int nodes)
{
	size = nodes;
	outputweight = new float[nodes+1];

	for(int i=0; i<nodes+1; i++)
		outputweight[i]=(float)(((rand()%1000)/1000.0)*noisemax - noisemax/2);

	hiddenweight = new float*[nodes];
	for(int i=0; i<nodes;i++)
	{
		hiddenweight[i]=new float[nodes+1];
		for(int j=0; j<nodes+1; j++)
			niddenweight[i][j]=(float)(((rand()%1000)/1000.0)*noisemax - noisemax/2);

	}
}

int Perceptron::getPrediction(int* inputs)
{
	float hidden[size];
	for(int hn=0; hn<size;hn++)
	{
		float sum = 0;
		for(int i=0; i<size;i++)
			sum += (inputs[i]==0?-1:1) * hiddenweight[hn][i];
		sum += hiddenweight[hn][size];
		hidden[hn] = sigmoid(sum);
	}

	float sum=0;
	for(int i=0; i<size; i++)
	{
		sum += hidden[i] * outputweight[i];
	}
	sum+=outputweight[size];
	return sigmoid(sum)>=0.5? 1:0;
}

int Perceptron::getRawPrediction(int* inputs)
{
	float hidden[size];

	for(int hn=0; hn<size;hn++)
	{
		float sum = 0;
		for(int i=0; i<size;i++)
			sum += (inputs[i]==0?-1:1) * hiddenweight[hn][i];
		sum += hiddenweight[hn][size];
		hidden[hn] = sigmoid(sum);
	}

	float sum=0;
	for(int i=0; i<size; i++)
	{
		sum += hidden[i] * outputweight[i];
	}
	sum+=outputweight[size];
	return sum;
}

bool Perceptron::train(int* inputs, int want)
{
	float hidden[size];

	for(int hn=0; hn<size; hn++)
	{
		float sum=0
		for(int i=0; i<size; i++)
			sum += (inputs[i]==0?-1:1) * hiddenweight[hn][i];
		sum += hiddenweight[hn][size];
		hidden[hn] = sigmoid(sum);
	}

	float sum = 0; 
	for(int i=0; i<size; i++)
	{
		sum += hidden[i] * outputweight[i];
	}

	sum += outputweight[size];
	float prediction = sigmoid(sum);


	float error = (want - prediction) * prediction * (1-prediction);
	float hiddenerror[size+1];

	for(int i=0; i<size; i++)
	{
		hiddenerror[i]=hidden[i]*(1-hidden[i])*outputweight[i]*error;
		outputweight[i]+= error * hidden[i] * alpha;
	}

	outputweight[size]+= alpha * error;

	for(int hn=0; hn<size; hn++)
	{
		for(int i=0; i<size; i++)
		{
			hiddenweight[hn][i]+= alpha * hiddenerror[hn] * (inputs[i]==0?-1:1);
		}
		hiddenweight[hn][size]+= alpha * hiddenerror[hn];
	}
	return ((prediction>=0.5?1:0) == want);

}