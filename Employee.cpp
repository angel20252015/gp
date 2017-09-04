#include "Employee.h"
#include <iostream>
#include <string>

Employee::Employee(int id, std::string firstName, std::string lastName, int salary)
{
	_id = id;
	_firstName = firstName;
	_lastName = lastName;
	_salary = salary;

}

int Employee::GetID()
{
	return _id;
}

std::string Employee::GetFirstName()
{
	return _firstName;
}

std::string Employee::GetLastName()
{
	return _lastName;
}

std::string Employee::GetName()
{
	return _firstName +" "+_lastName;
}

int Employee::GetSalary()
{
	return _salary;
}

void Employee::SetSalary(int salary)
{
	_salary = salary;
}

int Employee::GetAnnualSallary()
{
	return _salary*12;
}

int Employee::RaiseSalary(int percent)
{
	_salary = _salary + _salary*percent / 100;
	return _salary;
}

std::string Employee::Print()
{
	//return "Employee["+_id+", name="+_firstName+" "+_lastName+", "_salary;
	return"";
}

//int main() {
//	Employee n(5, "angel", "prado", 6);

//std::cout << n.GetFirstName << std::endl;
//	std::cin.get();
//}
