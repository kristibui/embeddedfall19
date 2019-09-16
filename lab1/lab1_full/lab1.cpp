// Example program
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

double *v;
//pointer to the first element in a sequence of elements appearing consecutively in memory
int count;
//number of elements inserted in the array so far by the user. 
int size;
// space currently allocated for the array, given in number of elements

void Grow();

void Shrink() {	
	cout << "Vector shrunk" << endl;
        cout << "Previous capacity: " <<  size << " elements" << endl;

	double *nv;
	nv = new double[size / 2]; 

	for (int i = 0; i < count; i++)
        {
                nv[i] = v[i];
        }

	size = size / 2;
	delete[] v;
	v = nv;

	cout << "New capacity: " << size << " elements" << endl;
}


void InsertElement() {	
	int userIndex;
	double userElement;

	cout << "Enter the index of new element:";
	cin >> userIndex;
	cout << "Enter the new element:";
	cin >> userElement;

	if (userIndex < 0 || userIndex > count)
	{
		cout << "Error: index out of bounds." << endl;
	}

	else
	{ 
		// Check if space is needed to grow
		if (count == size) {
			Grow();
		}

		for (int i = count; i > userIndex; i--)
		{
			v[i] =  v[i - 1];
		}
		v[userIndex] = userElement;
		count++;
	}
}


void RemoveElement() {	
	if (count == 0)
	{
		 cout << "Error: nothing to remove." << endl;
	}
	else
	{
		count--;
	}

	if (count < (size * 0.3)) Shrink();

}


void AddElement() {
	cout << "Enter the new element: ";
	double userDouble;
	cin >> userDouble;

	v[count] = userDouble;
	count ++;
}


void PrintVector() {
	for (int i = 0; i < count; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}


void Grow() {
	cout << "Vector grown" << endl;
	cout << "Previous capacity: " <<  size << " elements" << endl;

	double *nv; // new vector
	nv = new double[size * 2];

	for (int i = 0; i < size; i++)
	{
		nv[i] = v[i];
	} 
	size = size * 2;
	delete[] v;
	v = nv;
	cout << "New capacity: " << size << " elements" << endl;
} 


void Initialize() {
	count = 0;
	size = 2;
	v = new double[size];
	v[0] = 0;
	v[1] = 1;
}


void Finalize() {
	delete[] v;
}


int main() {
	Initialize();

	int userInput;

	while (userInput != 5) 
	{

		cout << "Main menu:" << endl << "1. Print the array" << endl;
		cout << "2. Append element at the end" << endl << "3. Remove last element" << endl;
		cout << "4. Insert one element" << endl << "5. Exit" << endl;
		cout << "Select an option:";


		cin >> userInput;

		switch(userInput)
		{
			case 1:
				cout << "You selected \"Print the array\"" << endl;
				PrintVector();
				break;
			case 2:
				cout << "You selected \"Append element at the end\"" << endl;
				if (count == size) Grow();
				AddElement();
				break;
			case 3:
				cout << "You selected \"Remove last element\"" << endl;
				RemoveElement();
				break;
			case 4:
				cout << "You selected \"Insert one element\"" << endl;
				InsertElement();
				break;
			case 5:
				break;
		}
	}

    //Put more code here	
	
    Finalize();
	
    return 0;
}


