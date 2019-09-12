
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

void Shrink() {

}


void InsertElement() {

}


void RemoveElement() {

}


void AddElement() {

}


void PrintVector() {

}


void Grow() {

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
                                break;
                        case 2:
                                cout << "You selected \"Append element at the end\"" << endl;
                                break;
                        case 3:
                                cout << "You selected \"Remove last element\"" << endl;
                                break;
                        case 4:
                                cout << "You selected \"Insert one element\"" << endl;
                                break;
                        case 5:
                                break;
                }
        }
 
        // Put more code here
        
        Finalize();
        
        return 0;
}
