#include<bits/stdc++.h>			//valid uniqueness of SAP ID
using namespace std;
bool isValidID(int emp_id){

  ifstream fin;
  fin.open("Employee.dat", ios::in | ios::binary);
  while (fin.read((char *)&obj, sizeof(obj)))
  {
    if (obj.getInfo() == emp_id)
    {
      cout << "Employee ID already exists.\n";
      return false;
    }
  }
  fin.close();
  return true;
}
