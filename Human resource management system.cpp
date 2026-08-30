#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>

class Employee {
public:
    std::string UserName;
    std::string Password;
    int ID;
    int Age;
    std::string Position;
    double Salary;
};

class HRMS {
private:
    std::vector<Employee> Employees; // creating a dynamic list to store employee objects in
public:
    void EmployeeNew(const Employee& emp) {
        Employees.push_back(emp); // adds an Employee object to the vector employees
        SaveEmployees("savedData.txt"); // Save every time a new employee is added
    }
    void EmployeeList() const {
        for (const auto& emp : Employees) {
            std::cout << "ID: " << emp.ID << ", Name: " << emp.UserName << ", Position: " << emp.Position << ", Salary: " << emp.Salary << std::endl;
        }
    }
    // File handling: Save and load employees
    void SaveEmployees(const std::string& savedData) {
        std::ofstream file(savedData);
        // to check for errors in finding the file
        if (!file) {
            std::cerr << "Failed to open file for writing.\n";
            return;
        }
        for (const auto& emp : Employees) {
            file << emp.ID << ", " << emp.UserName << ", " << emp.Age << ", " << emp.Password << ", " << emp.Position << ", " << emp.Salary << ", " << std::endl;
        }
        file.close();
    }
    void LoadEmployees(const std::string& savedData) {
        std::ifstream file(savedData);
        if (!file) {
            std::cerr << "Failed to open file for reading.\n" << savedData << std::endl;
            return;
        }
        Employees.clear();
        Employee emp;
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string temp;
            getline(ss, temp, ',');
            emp.ID = std::stoi(temp);
            getline(ss, emp.UserName, ',');
            getline(ss, temp, ',');
            emp.Age = std::stoi(temp);
            getline(ss, emp.Password, ',');
            getline(ss, emp.Position, ',');
            getline(ss, temp);
            emp.Salary = std::stod(temp);
            Employees.push_back(emp);
        }
        file.close();

    }

	bool Login(const std::string& username, const std::string& password) {
		for (const auto& emp : Employees) {
			if (emp.UserName == username && emp.Password == password) {
				return true; // Login successful
			}
		}
		return false; // Login failed
	}
    void SaveCVDetails(const std::string& name, const std::string& cv, const std::string& RegistrationData = "RegistrationData.txt") {
        std::ofstream file(RegistrationData, std::ios::app); // Open in append mode to add new entries
        if (!file) {
            std::cerr << "Failed to open file.\n";
            return;
        }
        file << "Name: " << name << "\nCV: " << cv << "\n\n";
        file.close();
    }
    void DisplayRegistrationData(const std::string& RegistrationData = "RegistrationData.txt") {
        std::ifstream file(RegistrationData);
        if (!file) {
            std::cerr << "Failed to open file.\n";
            return;
        }
        std::string line;
        std::cout << "Registration Data:\n";
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
 };



int main()
{
    HRMS hrms; // Creating an instance of HRMS
    hrms.LoadEmployees("savedData.txt");
    std::cout << "HUMAN RESOURCE MANAGEMENT SYSTEM!\n";
    std::cout << "MENU\n";
    std::cout << "1. Employee\n";
    std::cout << "2. Admin\n";
    std::cout << "3. Recruitment\n";
    std::cout << "PLEASE SELECT AN OPTION\n";
    
    int selection;
    int selection_two;
    bool validInput = false;

    while (!validInput) {
        std::cin >> selection;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //this means that errors in input
            //will be ignored (if characters are entered)
            std::cout << "Invalid input; please enter a number.\n";
        } else {
            validInput = true;
        }
    }
    std::string CV;
    std::string REGName;
    std::string Username1;
    std::string Password1;

    //determines what happens based on input
    switch (selection) {
    case 1: {
        std::cout << "Please select one of the options!\n";
        std::cout << "1. Login\n";
        std::cout << "2. Register account\n";
        std::cin >> selection_two;
        if (selection_two == 1) {
            std::string Username;
            std::string Password;
            std::cout << "Enter your UserName: ";
            std::cin >> Username;
            std::cout << "Enter your Password: ";
            std::cin >> Password;
            if (hrms.Login(Username, Password)) {
                std::cout << "Login successful!\n";
                std::cout << "Here are the current goals and training courses:\n";
                std::cout << "5 more jobs to complete\n";
                std::cout << "1. course for marketing\n";
                std::cout << "2. course for graphic design\n";
                std::cout << "3. course for management\n";
                std::cout << "4. course for programming in c++\n";
                std::cout << "5. course for programming in python\n";
                std::cout << "6. course for programming in java\n";
            } else {
                std::cout << "Invalid username or password.\n";
            }
        }
        else if (selection_two == 2) {
            Employee emp;
            std::cout << "Enter employee ID: ";
            std::cin >> emp.ID;
            std::cin.ignore();  // Ignore the newline after integer input
            std::cout << "Enter employee name: ";
            getline(std::cin, emp.UserName);
            std::cout << "Enter age ";
            std::cin >> emp.Age;
            std::cin.ignore();
            std::cout << "Enter Position: ";
            getline(std::cin, emp.Position);
            std::cout << "Enter salary: ";
            std::cin >> emp.Salary;
            hrms.EmployeeNew(emp);
            //hrms.SaveEmployees(emp)
        }
    break;
    }

    case 2:
        std::cout << "Enter your ADMIN UserName: ";
        std::cin >> Username1;
        std::cout << "Enter your Password: ";
        std::cin >> Password1;
        std::cout << "All employee data ";
        hrms.EmployeeList();
        hrms.DisplayRegistrationData();
        break;
    case 3:
        std::cout << "Please enter your name: ";
        std::cin >> REGName;
        std::cout << "Please paste your CV: ";
        std::cin.ignore();
        getline(std::cin, CV);
        hrms.SaveCVDetails(REGName, CV);
        std::cout << "CV has been saved successfully.\n";
        break;
    default:
        std::cout << "Invalid option selected.\n";
        break;
    }
    std::cout << "Enter any key to exit: ";
    std::string exitChoice;
    std::cin >> exitChoice;
    }