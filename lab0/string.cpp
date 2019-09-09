#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


void PrintArray(string array[], int size)
{

	int count;

	for (count = 0; count < size; count++) {
		cout << array[count] << endl;

	}
}

void SortArray(string array[], int size)
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
			string minSoFar = array[i];
			string trueMin = array[jMin];
			array[i] = trueMin;
			array[jMin] = minSoFar;
		}
	}
}

int main()
{

	string inputarray[10];

	for (int count = 0; count < 10; count++) {

		cout << "Please enter a string." << endl;

		cin >> inputarray[count];

		cout << "You entered: " << inputarray[count] << endl;
	}

	 //Sort inputarray in ascending order
	cout << "Sorting the Arrray..." << endl;
	SortArray(inputarray, 10);

	//Display inputrray
	PrintArray(inputarray, 10);

	 return 0;
}

