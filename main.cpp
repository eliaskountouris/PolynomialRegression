#include <iostream>
#include <math.h>
#include <vector>
#include "matrix.cpp"

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
  cout<<"Input the degree of the polynimal... \n";
  cin>>degree;

  //prints data set
  cout<<"X: ";
  printVector(x);
  cout<<"Y: ";
  printVector(y);

  vector<vector<long double>> _Y;
  vector<long double> t;
  for (int i = 0; i < y.size(); i++){
    t.push_back(y[i]);
    _Y.push_back(t);
  }

  Matrix Y = Matrix(y.size(), 1);

  //calcuates Vandermonde and prints it
  cout<<"\nVandermonde Matrix for degree ";
  cout<<degree;
  Matrix V = vandermonde(degree, x);
  V.printMatrix();

  //calcuates tranpose and prints it
  cout<<"\nVandermonde Transpose Matrix for degree ";
  cout<<degree;
  Matrix VT = V.transpose();
  VT.printMatrix();

  //calcuates V^T * V and prints it
  cout<<"\nTranspose times Vandermonde: ";
  Matrix VTV = VT*V;
  VTV.printMatrix();

  //calcuates inverse and prints it
  cout<<"\nThe Inverse:";
  Matrix matrixInverse = inverse(VTV);
  matrixInverse.printMatrix();

  //solves equation and prints solution
  cout<<"\nCoeffiecents:";
  Matrix coefficients = matrixInverse * VT * Y;
  coefficients.printMatrix();
}