#include<bits/stdc++.h>
using namespace std;
class Employee			//class declaration
{
private:
  int employee_id;
  char employee_name[50];
  long long int employee_phone;
  char assessment_date[50];
  char assessment_time[50];
  char assessment_duration[50];
  char assessment_status;
  char rm_name[50];
  int age;
  int rm_id;
  char gender;

public:
  void insertAssessmentDetails();
  void displayAssessmentDetails();
  int getInfo()
  {
    return employee_id;				//to be used in modify,delete etc functions
  }
} obj;



