#ifndef HRMS_H
#define HRMS_H

#include <vector>
#include <string>
#include "employee.h"

class HRMS {
private:
	std::vector<Employee> Employees;
public:
	void EmployeeNew(const Employee& emp);
	void EmployeeList() const;
	void SaveEmployees(const std::string& savedData);
	void LoadEmployees(const std::string& savedData);
	bool Login(const std::string& username, const std::string& password);
	void SaveCVDetails(const std::string& name, const std::string& cv, const std::string& RegistrationData = "RegistrationData.txt");
	void DisplayRegistrationData(const std::string& RegistrationData = "RegistrationData.txt");
};

#endif // HRMS_H

