#include <stdio.h>
#include <string.h>
#define MAX_RECORDS 10

struct Employee {
    char fullName[100];
    char birthDate[15];
    int employeeID;
    char workDepartment[50];
    float monthlySalary;
};

struct Employee employeeRecords[MAX_RECORDS];
int totalEmployees = 0;
void addEmployee() {
    if (totalEmployees < MAX_RECORDS) {
        struct Employee newRecord;

        printf("\nEnter Full Name: ");
        getchar(); 
        fgets(newRecord.fullName, sizeof(newRecord.fullName), stdin);
        newRecord.fullName[strcspn(newRecord.fullName, "\n")] = '\0';

        printf("Enter Date of Birth (DD-MM-YYYY): ");
        fgets(newRecord.birthDate, sizeof(newRecord.birthDate), stdin);
        newRecord.birthDate[strcspn(newRecord.birthDate, "\n")] = '\0';

        printf("Enter Employee ID: ");
        scanf("%d", &newRecord.employeeID);

        printf("Enter Work Department: ");
        getchar();
        fgets(newRecord.workDepartment, sizeof(newRecord.workDepartment), stdin);
        newRecord.workDepartment[strcspn(newRecord.workDepartment, "\n")] = '\0';

        printf("Enter Monthly Salary: ");
        scanf("%f", &newRecord.monthlySalary);

        employeeRecords[totalEmployees++] = newRecord;

        printf("\nEmployee added successfully!\n");
    } else {
        printf("\nCannot add more employees. The employee list is full.\n");
    }
}
void deleteEmployee() {
    int targetID;
    printf("\nEnter Employee ID to delete: ");
    scanf("%d", &targetID);

    int isFound = 0;
    for (int i = 0; i < totalEmployees; i++) {
        if (employeeRecords[i].employeeID == targetID) {
            for (int j = i; j < totalEmployees - 1; j++) {
                employeeRecords[j] = employeeRecords[j + 1];
            }
            totalEmployees--;
            isFound = 1;
            printf("\nEmployee with ID %d deleted successfully.\n", targetID);
            break;
        }
    }

    if (!isFound) {
        printf("\nEmployee with ID %d not found.\n", targetID);
    }
}
void displayEmployees() {
    if (totalEmployees == 0) {
        printf("\nNo employees to display.\n");
        return;
    }

    printf("\nEmployee Records:\n");
    printf("---------------------------------------------------\n");
    printf("Name\t\tDOB\t\tEmployee ID\tDepartment\tSalary\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < totalEmployees; i++) {
        printf("%s\t%s\t%d\t%s\t%.2f\n", 
                employeeRecords[i].fullName, 
                employeeRecords[i].birthDate, 
                employeeRecords[i].employeeID, 
                employeeRecords[i].workDepartment, 
                employeeRecords[i].monthlySalary);
    }

    printf("---------------------------------------------------\n");
}

// Main function
int main() {
    int userChoice;

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add an Employee\n");
        printf("2. Delete an Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                displayEmployees();
                break;
            case 4:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

