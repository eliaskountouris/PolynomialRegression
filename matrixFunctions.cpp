#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

//helper function to print out vectors
void printVector(vector<long double> data){
  cout<<"\n";
  for (int i =0; i<data.size();i++){
    cout << data[i];
    cout<< ' ';
  }
  cout << "\n";
}

//---------------------------------------------------------------------

//Helper function to print out matricies
void printMatrix(vector<vector<long double>> data){
  cout<<"\n";
  int rows =  data[0].size();
  int cols = data.size();
  for (int i = 0; i < cols; i++){
    for (int j=0; j<rows;j++){
      cout << data[i][j];
      cout << ' ';
    }
    cout<<"\n";
  }
}

//---------------------------------------------------------------------

//function to transpose matrix
vector<vector<long double>> transpose(vector<vector<long double>> input){
  //creates return matrix and temp matrix
  vector<vector<long double>> returnVector;
  vector<long double> t;
  //fills in the return matrix with the mirror of the input matrix
  for (int i = 0; i < input[0].size(); i++)
  {
    t.clear();
    for (int j = 0; j <input.size(); j++)
    {
      t.push_back(input[j][i]);
    }
    returnVector.push_back(t);
  }
  return returnVector;
}

//---------------------------------------------------------------------

//helper function to multiply 2 matricies
//it is assumed that the inputs will have the same inner dimension
vector<vector<long double>> matrixMultiply(vector<vector<long double>> first, vector<vector<long double>> second){
  vector<vector<long double>> returnVector;
  vector<long double> t;
  int n = first.size();
  int sum= 0;
  //loop through every row/column
  for (int i=0; i <first.size();i++){
    t.clear();
    for (int j = 0; j < second[0].size(); j++){
      // finds the dot product
      for (int k = 0; k<second.size();k++){
        sum+=first[i][k]*second[k][j];
      }
      //adds it to the new matrix
      t.push_back(sum);
      sum = 0;
    }
    returnVector.push_back(t);
  }
  return returnVector;
}

//finds the smaller matrixes used when computing the determinent
vector<vector<long double>> determinentMatrix(vector<vector<long double>> input, int ji, int ii){
  vector<vector<long double>> returnVector;
  vector<long double> t;
  //loops through every element, if its in the same row or column it doesnt add it to the output
  for (int i = 0; i<input.size();i++){
    t.clear();
    for (int j = 0;j<input.size();j++){
      if (j!=ji && i!=ii){
        t.push_back(input[i][j]);
      }
    }
    if (!t.empty()){
      returnVector.push_back(t);
    }
  }
  return returnVector;
}

//---------------------------------------------------------------------

//calculates the determinent using recursive method 
int determinent(vector<vector<long double>> input){
  //case for none square matrix
  if (input[0].size()!=input.size()) {
    return 0;
  }
  else{
    //case for 1x1 matrix
    if (input.size()==1){
      return input[0][0];
    }
    //case for 2x2 matrix
    else if(input.size()==2){
      return ((input[0][0]*input[1][1])-(input[0][1]*input[1][0]));
    }
    //for NxN method calls determinent again with sub matricies.
    else{
      int sum = 0;
      int sign = -1;
      for (int i = 0; i < input.size();i++){
        sum += pow(sign,i)*input[0][i]*determinent(determinentMatrix(input, i, 0));
      }
      return sum;

    }
  }
}

//---------------------------------------------------------------------

//calculates inverse using adjoint method
vector<vector<long double>> inverse(vector<vector<long double>> input){
  int det = determinent(input);
  vector<vector<long double>> adjointVector;
  vector<vector<long double>> returnVector;
  // check if its a square matrix and the determinent is not 0
  if (det==0 || input.size()!=input[0].size()){
    return input;
  }
  int sign = -1;
  vector<long double> t;
  //loops through every element and calcuates the cofactor
  for (int i =0; i<input.size();i++){
    t.clear();
    for(int j = 0; j<input.size();j++){
      t.push_back(pow(sign,i+j)*determinent(determinentMatrix(input, j, i)));
    }
    adjointVector.push_back(t);
  }
  //multipies every element by 1/det
  for (int i =0; i<input.size();i++){
    t.clear();
    for(int j = 0; j<input.size();j++){
      t.push_back(adjointVector[i][j]/det);
    }
    returnVector.push_back(t);
  }
  return returnVector;
}

//-------------------------------------------------------------------

//creates the vandermode matrix
vector<vector<long double>> vandermonde(int degree, vector<long double> input){
  vector<vector<long double>> returnVector;
  vector<long double> t;
  //loops through every number in input, and adds a number for every value up to the degree chosen
  for (int i = 0; i < input.size(); i++){
    t.clear();
    for (int j = 0; j <=degree ;j++){
      t.push_back(pow(input[i],j));
    }
    returnVector.push_back(t);
  }
  return returnVector;
}