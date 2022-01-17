#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

void printVector(vector<long double> data)
{
  cout << "\n";
  for (int i = 0; i < data.size(); i++)
  {
    cout << data[i];
    cout << ' ';
  }
  cout << "\n";
}

class Matrix
{
public:
  //---------------------------------------------------------------------
  Matrix(int m, int n, vector<vector<long double>> d)
  {
    (*this).numr = m;
    (*this).numc = n;
    (*this).data = d;
  }
  Matrix(int m, int n)
  {
    (*this).numr = m;
    (*this).numc = n;
    for (int i = 0; i < m; i++)
    {
      vector<long double> temp;
      for (int j = 0; j < n; j++)
      {
        if (i == j)
        {
          temp.push_back(1);
        }
        else
        {
          temp.push_back(0);
        }
      }
      (*this).data.push_back(temp);
    }
  }

  int retRows()
  {
    return (*this).numr;
  }
  int retCols()
  {
    return (*this).numc;
  }
  long double accData(int i, int j)
  {
    if (i < 0 || i > (*this).numr || j < 0 || j > (*this).numc)
    {
      return 0;
    }
    else
    {
      return (*this).data[i][j];
    }
  }
  //Helper function to print out matricies
  void printMatrix()
  {
    cout << "\n";
    for (int i = 0; i < (*this).numr; i++)
    {
      for (int j = 0; j < (*this).numc; j++)
      {
        cout << (*this).data[i][j];
        cout << ' ';
      }
      cout << "\n";
    }
  }
  Matrix transpose()
  {
    //creates return matrix and temp matrix
    vector<vector<long double>> returnVector;
    vector<long double> t;
    //fills in the return matrix with the mirror of the input matrix
    for (int i = 0; i < (*this).numc; i++)
    {
      t.clear();
      for (int j = 0; j < (*this).numr; j++)
      {
        t.push_back((*this).data[j][i]);
      }
      returnVector.push_back(t);
    }
    return Matrix((*this).numc, (*this).numr, returnVector);
  }

  Matrix operator*(Matrix &second)
  {
    vector<vector<long double>> returnMatrix;
    vector<long double> t;
    int n = (*this).numc;
    int sum = 0;
    //loop through every row/column
    for (int i = 0; i < (*this).numr; i++)
    {
      t.clear();
      for (int j = 0; j < second.retCols(); j++)
      {
        // finds the dot product
        for (int k = 0; k < second.retRows(); k++)
        {
          sum += (*this).data[i][k] * second.accData(k, j);
        }
        //adds it to the new matrix
        t.push_back(sum);
        sum = 0;
      }
      returnMatrix.push_back(t);
    }
    return Matrix((*this).numr, second.retCols(), returnMatrix);
  }

private:
  int numr;
  int numc;
  vector<vector<long double>> data;
};

//---------------------------------------------------------------------

//function to transpose matrix

//---------------------------------------------------------------------

//helper function to multiply 2 matrices
//it is assumed that the inputs will have the same inner dimension

//finds the smaller matrixes used when computing the determinant

//---------------------------------------------------------------------

//calculates inverse using adjoint method
Matrix determinantMatrix(Matrix input, int ji, int ii)
{
  vector<vector<long double>> returnVector;
  vector<long double> t;
  //loops through every element, if its in the same row or column it doesnt add it to the output
  for (int i = 0; i < input.retRows(); i++)
  {
    t.clear();
    for (int j = 0; j < input.retCols(); j++)
    {
      if (j != ji && i != ii)
      {
        t.push_back(input.accData(i, j));
      }
    }
    if (!t.empty())
    {
      returnVector.push_back(t);
    }
  }
  return Matrix(input.retRows() - 1, input.retCols() - 1, returnVector);
}

//---------------------------------------------------------------------

//calculates the determinant using recursive method
int determinant(Matrix input)
{
  //case for none square matrix
  if (input.retCols() != input.retRows())
  {
    return 0;
  }
  else
  {
    //case for 1x1 matrix
    if (input.retRows() == 1)
    {
      return input.accData(0, 0);
    }
    //case for 2x2 matrix
    else if (input.retRows() == 2)
    {
      return ((input.accData(0, 0) * input.accData(1, 1)) - (input.accData(0, 1) * input.accData(1, 0)));
    }
    //for NxN method calls determinant again with sub matricies.
    else
    {
      int sum = 0;
      int sign = -1;
      for (int i = 0; i < input.retRows(); i++)
      {
        sum += pow(sign, i) * input.accData(0, i) * determinant(determinantMatrix(input, i, 0));
      }
      return sum;
    }
  }
}

Matrix inverse(Matrix input)
{
  int det = determinant(input);
  vector<vector<long double>> adjointVector;
  vector<vector<long double>> returnVector;
  // check if its a square matrix and the determinant is not 0
  if (det == 0 || input.retRows() != input.retCols())
  {
    return input;
  }
  int sign = -1;
  vector<long double> t;
  //loops through every element and calculates the cofactor
  for (int i = 0; i < input.retRows(); i++)
  {
    t.clear();
    for (int j = 0; j < input.retRows(); j++)
    {
      t.push_back(pow(sign, i + j) * determinant(determinantMatrix(input, j, i)));
    }
    adjointVector.push_back(t);
  }
  //multipies every element by 1/det
  for (int i = 0; i < input.retRows(); i++)
  {
    t.clear();
    for (int j = 0; j < input.retRows(); j++)
    {
      t.push_back(adjointVector[i][j] / det);
    }
    returnVector.push_back(t);
  }
  return Matrix(input.retRows(), input.retCols(), returnVector);
}

//-------------------------------------------------------------------

//creates the vandermode matrix
Matrix vandermonde(int degree, vector<long double> input)
{
  vector<vector<long double>> returnVector;
  vector<long double> t;
  //loops through every number in input, and adds a number for every value up to the degree chosen
  for (int i = 0; i < input.size(); i++)
  {
    t.clear();
    for (int j = 0; j <= degree; j++)
    {
      t.push_back(pow(input[i], j));
    }
    returnVector.push_back(t);
  }
  return Matrix(input.size(), degree + 1, returnVector);
}