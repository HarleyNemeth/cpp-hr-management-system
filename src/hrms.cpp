#include "hrms.h"
#include <iostream>
#include <fstream>
#include <sstream>

void HRMS::EmployeeNew(const Employee& emp) {
	Employees.push_back(emp);
	SaveEmployees("savedData.txt");
}

void HRMS::EmployeeList() const {
	for (const auto& emp : Employees) {
		std::cout << "ID: " << emp.ID << ", Name: " << emp.UserName << ", Position: " << emp.Position << ", Salary: " << emp.Salary << std::endl;
	}
}

void HRMS::SaveEmployees(const std::string& savedData) {
	std::ofstream file(savedData);
	if (!file) { std::cerr << "Failed to open file for writing.\n"; return; }
	for (const auto& emp : Employees) {
		file << emp.ID << ", " << emp.UserName << ", " << emp.Age << ", " << emp.Password << ", " << emp.Position << ", " << emp.Salary << ", " << std::endl;
	}
}

void HRMS::LoadEmployees(const std::string& savedData) {
	std::ifstream file(savedData);
	if (!file) { std::cerr << "Failed to open file for reading.\n" << savedData << std::endl; return; }
	Employees.clear();
	Employee emp;
	std::string line;
	while (getline(file, line)) {
		std::stringstream ss(line);
		std::string temp;
		if (!getline(ss, temp, ',')) continue;
		emp.ID = std::stoi(temp);
		if (!getline(ss, emp.UserName, ',')) emp.UserName = "";
		if (!getline(ss, temp, ',')) temp = "0";
		emp.Age = std::stoi(temp);
		if (!getline(ss, emp.Password, ',')) emp.Password = "";
		if (!getline(ss, emp.Position, ',')) emp.Position = "";
		if (!getline(ss, temp)) temp = "0";
		// trim leading spaces from temp
		if (!temp.empty() && temp[0] == ' ') temp.erase(0, 1);
		try {
			emp.Salary = std::stod(temp);
		} catch (...) {
			emp.Salary = 0.0;
		}
		Employees.push_back(emp);
	}
}

bool HRMS::Login(const std::string& username, const std::string& password) {
	for (const auto& emp : Employees) {
		if (emp.UserName == username && emp.Password == password) return true;
	}
	return false;
}

void HRMS::SaveCVDetails(const std::string& name, const std::string& cv, const std::string& RegistrationData) {
	std::ofstream file(RegistrationData, std::ios::app);
	if (!file) { std::cerr << "Failed to open file.\n"; return; }
	file << "Name: " << name << "\nCV: " << cv << "\n\n";
}

void HRMS::DisplayRegistrationData(const std::string& RegistrationData) {
	std::ifstream file(RegistrationData);
	if (!file) { std::cerr << "Failed to open file.\n"; return; }
	std::string line;
	std::cout << "Registration Data:\n";
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}
}
