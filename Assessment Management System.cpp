/*Written By Mohd Aman(52042715)
Assessment Management System in C++ 
with binary file handling and validations*/

#include <bits/stdc++.h>
#include"class.h"							//class declaration
#include"valid.h"							//validation of ID
using namespace std;
void Employee::insertAssessmentDetails()	//Insert data to file
{
  
  cout << "\n...ENTER EMPLOYEE DETAILS...\n";
  cin.clear();
  cin.ignore(256, '\n');

  cout << "Enter Employee SAP ID : \n";
  cin >> employee_id;

  while (cin.fail())						//To validate input and return if wrong
  {
    cout << "SAP ID has to be integer only\n";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> employee_id;
  }

  bool is_valid = isValidID(employee_id);
  if(!is_valid)
    return;

  cout << "Enter Name : \n";
  cin.ignore();
  cin.getline(employee_name, 50);
  while (cin.fail())
  {
    cout << "Name has to be string only\n";
    cin.clear();
    cin.ignore(256, '\n');
    cin.getline(employee_name, 50);
  }

  cout << "Enter Gender (M/F) : \n";
  cin >> gender;
  while (cin.fail())
  {
    cout << "Please enter M or F only\n";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> gender;
  }

  cout << "Enter Employee Phone : \n";
  cin >> employee_phone;

  cout << "Enter Employee Age : \n";
  cin >> age;

  cout << "Enter RM Name : \n";
  cin.ignore();
  cin.getline(rm_name, 50);
  
  cout << "Enter RM SAP ID : \n";
  cin.ignore();
  cin >> rm_id;
  
  cout << "Enter Assessment Date(DD/MM/YYYY) : \n";
  cin.ignore();
  cin.getline(assessment_date,50);
  
  cout << "Enter Assessment Time (HH:MM , 24 HR FORMAT) : \n";
  cin.ignore();
  cin.getline(assessment_time,50);
  
  cout << "Enter Assessment Duration(HH:MM) : \n";
  cin.ignore();
  cin.getline(assessment_duration,50);						//cin with string is dumping code
  cout << "Enter Current Assessment Status (P for Pass/ F for Faill) : \n";
  cin >> assessment_status;

  cout << "\n Information addedd to the file successfully \n";
  cout << "\n";
}

void Employee::displayAssessmentDetails()				//To display data
{
  cout << "...Employee Details...\n";
  cout << "\n==========================\n";
  cout << "Name : " << employee_name << endl;
  cout << "SAP ID : " << employee_id << endl;
  cout << "Gender : " << gender << endl;
  cout << "Age : " << age << endl;
  cout << "Contact Number : " << employee_phone << endl;
  cout << "RM Name : " << rm_name << endl;
  cout << "RM ID : " << rm_id << endl;
  cout << "Assessment Date : " << assessment_date << endl;
  cout << "Assessment Time : " << assessment_time << endl;
  cout << "Assessment Duration : " << assessment_duration << endl;
  cout << "Assessment Status : " << assessment_status << endl;
}

void addData()								//adding data in binary file Employee.dat
{
  ofstream fout;
  fout.open("Employee.dat", ios::binary | ios::out | ios::app);
  Employee emp;
  emp.insertAssessmentDetails();
  fout.write((char *)&emp, sizeof(emp));
  fout.close();
}

void displayData()							//to read data from file 
{
  ifstream fin;
  fin.open("Employee.dat", ios::in | ios::binary);
  while (fin.read((char *)&obj, sizeof(obj)))
  {
    obj.displayAssessmentDetails();
  }
  fin.close();
  cout << "\n Data Successfully read from file...\n";
  cout << "\n";
}

void searchData()				//To search a particular data
{
  int n, flag = 0;
  ifstream fin;
  fin.open("Employee.dat", ios::in | ios::binary);
  cout << "\nEnter Employee ID to be searched : \n";
  cin >> n;
  while (fin.read((char *)&obj, sizeof(obj)))
  {
    if (n == obj.getInfo())
    {
      cout << "Following are the required details...\n";
      obj.displayAssessmentDetails();
      flag++;
    }
  }
  fin.close();
  if (flag == 0)
    cout << "\n The Employee ID " << n << " not found\n";
  cout << "\n";
}

void deleteData()						//To remove an existing data
{
  int n, flag = 0;
  ifstream fin;
  ofstream fout, tout;
  fin.open("Employee.dat", ios::in | ios::binary);
  fout.open("Temp.dat", ios::out | ios::app | ios::binary);
  cout << "Employee ID to be deleted : \n";
  cin >> n;
  while (fin.read((char *)&obj, sizeof(obj)))
  {
    if (n == obj.getInfo())
    {
      cout << "Employee ID " << n << " has been deleted successfully\n";
      obj.displayAssessmentDetails();
      tout.write((char *)&obj, sizeof(obj));
      flag++;
    }
    else
    {
      fout.write((char *)&obj, sizeof(obj));
    }
  }
  fout.close();
  tout.close();
  fin.close();
  if (flag == 0)
    cout << "\n The Employee ID " << n << " not found\n";
  cout << "\n";
  remove("Employee.dat");
  rename("Temp.dat", "Employee.dat");
}

void modifyData()								//to modify data
{
  int n, flag = 0, pos;
  fstream fio;
  fio.open("Employee.dat", ios::in | ios::out | ios::binary);
  cout << "\nEnter Employee SAP ID whose details are to be modified : \n";
  cin >> n;
  while (fio.read((char *)&obj, sizeof(obj)))
  {
    pos = fio.tellg();
    if (n == obj.getInfo())
    {
      cout << "Employee ID " << n << " will be modified\n";
      obj.displayAssessmentDetails();
      cout << "\nEnter New Details\n";
      cout <<"\nKindly note SAP ID is unique and can not be modified use any other temp ID to modify other details\n";
      obj.insertAssessmentDetails();
      fio.seekg(pos - sizeof(obj));
      fio.write((char *)&obj, sizeof(obj));
      flag++;
    }
  }
  fio.close();
  if (flag == 0)
    cout << "The Employee ID " << n << " not found\n";
  cout << "\n";
}

void writeOptions()									//Menu with options to choose
{
  cout << "\t\t\t...ASSESSMENT MANAGEMENT SYSTEM..." << endl;
  cout << "\t\t\t==================================" << endl;
  cout << "\t\t\t1. Write Data To Records\n";
  cout << "\t\t\t2. Read Data From Records\n";
  cout << "\t\t\t3. Search Data From Records\n";
  cout << "\t\t\t4. Delete Data From Records\n";
  cout << "\t\t\t5. Modify Data In Records\n";
  cout << "\t\t\t6. Exit\n";
  cout << "\t\t\t==================================" << endl;
  cout << "\t\t\t...Enter Your Choice...\n";
}

void project()
{
  int choice;
  do
  {
    writeOptions();
    cin >> choice;

    switch (choice)
    {
    case 1:
      addData();
      break;
    case 2:
      displayData();
      break;
    case 3:
      searchData();
      break;
    case 4:
      deleteData();
      break;
    case 5:
      modifyData();
      break;
    case 6:														//Exit Case
      break;
    default:
      cout << "Please Enter Valid Choice Number\n";				//validation of input
      cin.clear();
      cin.ignore(256, '\n');
      break;
    }
  } while (choice != 6);
}
int main()
{
  project();
}

