#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void RandomArray(int array[], int size)
{
	int count;

	srand (time(NULL));

	for (count = 0; count < size; count++) {
		array[count] = rand() % 100;
	}
}

void PrintArray(int array[], int size)
{

	int count;

	for (count = 0; count < size; count++) {
		cout << array[count] << endl;

	}
}

void SortArray(int array[], int size)
{
	int i, j, jMin;
	for (i = 0; i < size - 1; i++) {
		jMin = i;

		for (j = i + 1; j < size; j++) {

			if (array[j] < array[jMin]) {
				jMin = j;
			}
		}

		if (i != jMin) {
			int minSoFar = array[i];
			int trueMin = array[jMin];
			array[i] = trueMin;
			array[jMin] = minSoFar;
		}
	}
}

int main()
{
	//Create an array to hold 10 integer values: randomarray
	int randomarray[10];

	//Generate 10 random integer values and save them to randomarray
	RandomArray(randomarray, 10);

	 //Display randomarray
	PrintArray(randomarray, 10);

	 //Sort randomarray in ascending order
	cout << "Sorting the Arrray..." << endl;
	SortArray(randomarray, 10);

	//Display randomarray
	PrintArray(randomarray, 10);

	 return 0;
}

