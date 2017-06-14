const float alpha = 0.05

const float noisemax = 0.4

//define Perception object
class Perceptron
{
public:
	int getPrediction(int*);
	float getRawPrediction(int*);
	bool train(int*, int);
	Perceptron(int);
	float* outputweight;
	float** hiddenweight;
	int size;
}