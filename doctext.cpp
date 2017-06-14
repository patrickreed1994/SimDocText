#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#include "neural.h"

int textlength;

string operation, symbol;

void train()
{
	ifstream datafile;
	string line;
	datafile.open("doctext.txt");
	if(!datafile.is_open())
	{
		cout<<"Couldn't open doctext.txt"<<endl;
		return;
	}
	int linecount=0;

	while(getline(datafile,line))
	{
		linecount++
	}
	datafile.close();

	int sample_input[linecount][textlength];
	char sample_output[linecount];

	datafile.open("doctext.txt");

	for(int i=0; i<linecount; i++)
	{
		getline(datafile, line);
		sample_output[i] = line[0];
		textlength = line.length();
		for(int j = 0; j<textlength; j++)
		{
			sample_input[i][j]=line[j+2];
		}
	}
	datafile.close();

	//MAKE NEURAL NETS AND TRAIN THEM HERE. SAVE WEIGHT TO PERCEPTRON.TXT
	char numarray[8];
	int uniquenums = 0;
	for(int k = 0; k<linecount;k++)
	{
		for(int m=0; m < 8; m++)
		{
			if(sample_output[k] == numarray[m])
				break;
			if(sample_output[k] != numarray[m])
			{
				if(numarray[m] == NULL)
				{
					numarray[uniquenums] = sample_output[k];
					uniquenums += 1;
					break;
				}
			}
		}
	}

	//Instantiate and fill perceptron array
	Perceptron* perceptronarray[uniquenums];
	for(int n = 0; n<uniquenums; n++)
		perceptronarray[n] = new Perceptron(200);

	count<<"Begin training..."<<endl;
	for(int p = 0; p < uniquenums; p++)
	{
		char trainednum = numarray[p];
		for (int q=0; q<100000; q++)
		{
			bool desired = false;
			bool trained = true;
			for(int r = 0; r<linecount; r++)
			{
				if(sample_output[r] == trainednum)
				{
					desired = true;
				}
				else
				{
					desired = false;
				}
				if(perceptronarray[p]->train(sample_input[r], desired) == false)
				{
					perceptronarray[p]->train(sample_input[r], desired);
					trained = false;
				}
			}
			if (trained == true)
				break;
		}
	}
	cout<<"...training complete."<<endl;

	ofstream myfile;
	myfile.open("perceptron.txt", ios::out | ios::trunc);

	count<<"Begin writing weight file..."<<endl;
	for(int s = 0; s < uniquenums; s++)
	{
		for(int t = 0; t<perceptronarray[s]->size+1; t++)
		{
			myfile<<perceptronarray[s]->outputweight[t]<<endl;
		}
		for (int u = 0; u<perceptronarray[s]->size;u++)
		{
			for(int v = 0; v < perceptronarray[s]->size;v++)
			{
				myfile<<perceptronarray[s]->hiddenweight[u][v]<<endl;
			}
		}
	}
	myfile.close();
	cout<<"...weight file complete."<<endl;

}

void test()
{

}

void doOperation()
{
	if(operation.compare("train")==0)
	{
		train();
	}

}

int main(int argc, char **argv)
{
	if(argc>=2)
		operation=argv[1];
	if(argc==3)
		symbol=argv[2];
	else
		symbol=" ";
	//if the user didn't give any, print out some help and stop
	if(argc==1)
	{
		cout << "Usage: " << endl;
		cout << " ocr sample A" << endl;
		cout << " ocr train" << endl;
		cout << " ocr test" << endl;
		exit(0);
	}
}