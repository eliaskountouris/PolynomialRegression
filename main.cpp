#include <iostream>
#include <math.h>
#include <vector>
#include "matrixFunctions.cpp"

using namespace std;

//--------------------------------------------------------

//main method
int main() {
  //size of data set
  int r;
  cout << "Input number of datapoints...\n";
  cin >> r;

  //first input vector 
  vector<long double> x;
  cout << "Input the values of the independent variable in the dataset..\n";
  for (int i = 0; i <r ;i++){
    long double data;
    cin>>data;
    x.push_back(data);
  }
  //second input vector
  vector<long double> y;
  cout << "Input the values of the dependent variable in the dataset..\n";
  for (int i = 0; i <r ;i++){
    long double data;
    cin>>data;
    y.push_back(data);
  }

  //get degree of polynomial
  int degree;
  cout<<" Input the degree of the polynimal... \n";
  cin>>degree;

  //prints data set
  cout<<"X: ";
  printVector(x);
  cout<<"Y: ";
  printVector(y);

  //changes data type of Y so I dont have to remake the matrixMultiply method
  vector<vector<long double>> Y;
  vector<long double> t;
  for (int i = 0; i < y.size(); i++){
    t.push_back(y[i]);
    Y.push_back(t);
  }

  //calcuates Vandermonde and prints it
  cout<<"\nVandermonde Matrix for degree ";
  cout<<degree;
  vector<vector<long double>> V = vandermonde(degree, x);
  printMatrix(V);

  //calcuates tranpose and prints it
  cout<<"\nVandermonde Transpose Matrix for degree ";
  cout<<degree;
  vector<vector<long double>> VT = transpose(V);
  printMatrix(VT);

  //calcuates V^T * V and prints it
  cout<<"\nTranspose times Vandermonde";
  vector<vector<long double>> VTV = matrixMultiply(VT, V);
  printMatrix(VTV);

  //calcuates inverse and prints it
  cout<<"\nThe Inverse";
  vector<vector<long double>> matrixInverse =inverse(VTV);
  printMatrix(matrixInverse);

  //solves equation and prints solution
  cout<<"\nCoeffiecents: \n";
  vector<vector<long double>> coeffiecents = matrixMultiply(matrixInverse, matrixMultiply(VT, Y));
  printMatrix(coeffiecents);
}