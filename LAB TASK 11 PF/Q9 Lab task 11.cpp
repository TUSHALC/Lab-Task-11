#include <stdio.h>
#include <string.h>
#define MAX_DIVISIONS 5
#define MAX_SUBJECTS 10
#define MAX_ENROLLEES 50

typedef struct {
    char studentName[50];
    int studentID;
} Enrollee;

typedef struct {
    char facultyName[50];
    char credentials[50];
} Educator;

typedef struct {
    char subjectCode[10];
    char subjectName[50];
    Educator instructor;
    int enrolleeCount;
    Enrollee enrollees[MAX_ENROLLEES];
} Subject;

typedef struct {
    char divisionName[50];
    int subjectCount;
    Subject subjects[MAX_SUBJECTS];
} Division;

Division divisions[MAX_DIVISIONS];
int divisionCount = 0;

void createDivision();
void createSubject();
void registerStudent();
void displayDetails();
void displayDivisionDetails();
void mainMenu();

void createDivision() {
    if (divisionCount >= MAX_DIVISIONS) {
        printf("Maximum divisions reached.\n");
        return;
    }

    printf("Enter division name: ");
    scanf(" %[^\n]", divisions[divisionCount].divisionName);
    divisions[divisionCount].subjectCount = 0;
    divisionCount++;
    printf("Division added successfully!\n");
}

void createSubject() {
    if (divisionCount == 0) {
        printf("No divisions available. Create a division first.\n");
        return;
    }

    int divisionIndex;
    printf("Enter division index (0 to %d): ", divisionCount - 1);
    scanf("%d", &divisionIndex);

    if (divisionIndex < 0 || divisionIndex >= divisionCount) {
        printf("Invalid division index.\n");
        return;
    }

    Division *division = &divisions[divisionIndex];
    if (division->subjectCount >= MAX_SUBJECTS) {
        printf("Maximum subjects reached for this division.\n");
        return;
    }

    Subject *subject = &division->subjects[division->subjectCount];
    printf("Enter subject code: ");
    scanf(" %[^\n]", subject->subjectCode);
    printf("Enter subject name: ");
    scanf(" %[^\n]", subject->subjectName);
    printf("Enter educator name: ");
    scanf(" %[^\n]", subject->instructor.facultyName);
    printf("Enter educator credentials: ");
    scanf(" %[^\n]", subject->instructor.credentials);

    subject->enrolleeCount = 0;
    division->subjectCount++;
    printf("Subject added successfully!\n");
}

void registerStudent() {
    if (divisionCount == 0) {
        printf("No divisions available. Create a division first.\n");
        return;
    }

    int divisionIndex, subjectIndex;
    printf("Enter division index (0 to %d): ", divisionCount - 1);
    scanf("%d", &divisionIndex);

    if (divisionIndex < 0 || divisionIndex >= divisionCount) {
        printf("Invalid division index.\n");
        return;
    }

    Division *division = &divisions[divisionIndex];
    if (division->subjectCount == 0) {
        printf("No subjects available in this division. Create a subject first.\n");
        return;
    }

    printf("Enter subject index (0 to %d): ", division->subjectCount - 1);
    scanf("%d", &subjectIndex);

    if (subjectIndex < 0 || subjectIndex >= division->subjectCount) {
        printf("Invalid subject index.\n");
        return;
    }

    Subject *subject = &division->subjects[subjectIndex];
    if (subject->enrolleeCount >= MAX_ENROLLEES) {
        printf("Maximum enrollees reached for this subject.\n");
        return;
    }

    Enrollee *enrollee = &subject->enrollees[subject->enrolleeCount];
    printf("Enter student name: ");
    scanf(" %[^\n]", enrollee->studentName);
    printf("Enter student ID: ");
    scanf("%d", &enrollee->studentID);

    subject->enrolleeCount++;
    printf("Student registered successfully!\n");
}

void displayDetails() {
    if (divisionCount == 0) {
        printf("No divisions available.\n");
        return;
    }

    for (int i = 0; i < divisionCount; i++) {
        Division division = divisions[i];
        printf("\nDivision: %s\n", division.divisionName);
        for (int j = 0; j < division.subjectCount; j++) {
            Subject subject = division.subjects[j];
            printf("  Subject: %s (%s)\n", subject.subjectName, subject.subjectCode);
            printf("    Educator: %s (%s)\n", subject.instructor.facultyName, subject.instructor.credentials);
            printf("    Enrollees:\n");
            for (int k = 0; k < subject.enrolleeCount; k++) {
                Enrollee enrollee = subject.enrollees[k];
                printf("      %d. %s (ID: %d)\n", k + 1, enrollee.studentName, enrollee.studentID);
            }
        }
    }
}

void displayDivisionDetails() {
    if (divisionCount == 0) {
        printf("No divisions available.\n");
        return;
    }

    int divisionIndex;
    printf("Enter division index (0 to %d): ", divisionCount - 1);
    scanf("%d", &divisionIndex);

    if (divisionIndex < 0 || divisionIndex >= divisionCount) {
        printf("Invalid division index.\n");
        return;
    }

    Division division = divisions[divisionIndex];
    printf("\nDivision: %s\n", division.divisionName);
    for (int j = 0; j < division.subjectCount; j++) {
        Subject subject = division.subjects[j];
        printf("  Subject: %s (%s)\n", subject.subjectName, subject.subjectCode);
        printf("    Educator: %s (%s)\n", subject.instructor.facultyName, subject.instructor.credentials);
        printf("    Enrollees:\n");
        for (int k = 0; k < subject.enrolleeCount; k++) {
            Enrollee enrollee = subject.enrollees[k];
            printf("      %d. %s (ID: %d)\n", k + 1, enrollee.studentName, enrollee.studentID);
        }
    }
}

void mainMenu() {
    int option;
    do {
        printf("\nEducation Management System\n");
        printf("1. Create Division\n");
        printf("2. Create Subject\n");
        printf("3. Register Student\n");
        printf("4. View All Details\n");
        printf("5. View Division Details\n");
        printf("0. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                createDivision();
                break;
            case 2:
                createSubject();
                break;
            case 3:
                registerStudent();
                break;
            case 4:
                displayDetails();
                break;
            case 5:
                displayDivisionDetails();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (option != 0);
}

int main() {
    mainMenu();
    return 0;
}

