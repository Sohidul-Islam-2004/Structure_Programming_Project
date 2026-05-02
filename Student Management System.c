#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_SUBJECTS 5

typedef struct
{
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    int marks[MAX_SUBJECTS];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void addStudent();
void deleteStudent();
void updateStudent();
void displayAllStudents();
void displayStudent();
int isRollNumberExists(int rollNumber);
void clearInputBuffer();

int main()
{
    int x;
    while (1)
    {
        printf("\n");
        printf("===============================================\n");
        printf("            Student Management System           \n");
        printf("===============================================\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Display All Students\n");
        printf("5. Display Particular Student\n");
        printf("6. Exit\n");
        printf("===============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &x);

        switch (x)
        {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            displayAllStudents();
            break;
        case 5:
            displayStudent();
            break;
        case 6:
            printf("\nExiting the program. Goodbye!\n");
            return 0;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to clear input buffer
void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}

// Function to check if roll number already exists
int isRollNumberExists(int rollNumber)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollNumber == rollNumber)
            return 1;
    }
    return 0;
}

void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        printf("\nCannot add more students. Maximum limit reached.\n");
        return;
    }

    Student newStudent;
    int roll;

    printf("\nEnter roll number: ");
    scanf("%d", &roll);

    // Check for duplicate roll number
    if (isRollNumberExists(roll))
    {
        printf("\nRoll number %d already exists! Please use a different roll number.\n", roll);
        return;
    }
    newStudent.rollNumber = roll;

    printf("Enter name: ");
    clearInputBuffer();
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    strtok(newStudent.name, "\n"); // Remove newline character

    printf("Enter marks for %d subjects:\n", MAX_SUBJECTS);
    for (int i = 0; i < MAX_SUBJECTS; i++)
    {
        switch (i)
        {
        case 0:
            printf("  CSE103 = ");
            break;
        case 1:
            printf("  CSE106 = ");
            break;
        case 2:
            printf("  ENG099 = ");
            break;
        case 3:
            printf("  CHE109 = ");
            break;
        case 4:
            printf("  MAT101 = ");
            break;
        }
        scanf("%d", &newStudent.marks[i]);

        // Validate marks (0-100)
        if (newStudent.marks[i] < 0 || newStudent.marks[i] > 100)
        {
            printf("  Invalid marks! Please enter marks between 0 and 100.\n");
            i--; // Re-enter this subject
        }
    }

    students[studentCount++] = newStudent;
    printf("\n✓ Student added successfully!\n");
}

void deleteStudent()
{
    if (studentCount == 0)
    {
        printf("\nNo students to delete.\n");
        return;
    }

    int rollNumber;
    printf("\nEnter roll number of the student to delete: ");
    scanf("%d", &rollNumber);

    int found = 0;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollNumber == rollNumber)
        {
            printf("\nStudent found: %s (Roll: %d)\n", students[i].name, students[i].rollNumber);
            printf("Are you sure you want to delete? (1 for Yes / 0 for No): ");
            int confirm;
            scanf("%d", &confirm);

            if (confirm == 1)
            {
                for (int j = i; j < studentCount - 1; j++)
                    students[j] = students[j + 1];
                studentCount--;
                printf("\n✓ Student deleted successfully!\n");
            }
            else
            {
                printf("\nDeletion cancelled.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\n✗ Student with roll number %d not found.\n", rollNumber);
}

void updateStudent()
{
    if (studentCount == 0)
    {
        printf("\nNo students to update.\n");
        return;
    }

    int rollNumber;
    printf("\nEnter roll number of the student to update: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollNumber == rollNumber)
        {
            printf("\n--- Updating student: %s (Roll: %d) ---\n", students[i].name, students[i].rollNumber);

            printf("Enter new name: ");
            clearInputBuffer();
            fgets(students[i].name, MAX_NAME_LENGTH, stdin);
            strtok(students[i].name, "\n");

            printf("Enter new marks for %d subjects:\n", MAX_SUBJECTS);
            for (int j = 0; j < MAX_SUBJECTS; j++)
            {
                switch (j)
                {
                case 0:
                    printf("  CSE103 = ");
                    break;
                case 1:
                    printf("  CSE106 = ");
                    break;
                case 2:
                    printf("  ENG099 = ");
                    break;
                case 3:
                    printf("  CHE109 = ");
                    break;
                case 4:
                    printf("  MAT101 = ");
                    break;
                }
                scanf("%d", &students[i].marks[j]);

                // Validate marks
                if (students[i].marks[j] < 0 || students[i].marks[j] > 100)
                {
                    printf("  Invalid marks! Please enter marks between 0 and 100.\n");
                    j--;
                }
            }
            printf("\n✓ Student updated successfully!\n");
            return;
        }
    }

    printf("\n✗ Student with roll number %d not found.\n", rollNumber);
}

void displayAllStudents()
{
    if (studentCount == 0)
    {
        printf("\nNo students to display.\n");
        return;
    }

    printf("\n============= All Students (%d total) =============\n", studentCount);

    for (int i = 0; i < studentCount; i++)
    {
        // Calculate total and percentage
        int total = 0;
        for (int j = 0; j < MAX_SUBJECTS; j++)
        {
            total += students[i].marks[j];
        }
        float percentage = (float)total / MAX_SUBJECTS;

        printf("\n-----------------------------------------\n");
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Name: %s\n", students[i].name);
        printf("Marks:\n");
        printf("  CSE103: %d\n", students[i].marks[0]);
        printf("  CSE106: %d\n", students[i].marks[1]);
        printf("  ENG099: %d\n", students[i].marks[2]);
        printf("  CHE109: %d\n", students[i].marks[3]);
        printf("  MAT101: %d\n", students[i].marks[4]);
        printf("-----------------------------------------\n");
        printf("Total: %d / %d\n", total, MAX_SUBJECTS * 100);
        printf("Percentage: %.2f%%\n", percentage);

        // Grade calculation
        printf("Grade: ");
        if (percentage >= 80)
            printf("A+ (Excellent)");
        else if (percentage >= 75)
            printf("A (Very Good)");
        else if (percentage >= 70)
            printf("A- (Good)");
        else if (percentage >= 65)
            printf("B+ (Satisfactory)");
        else if (percentage >= 60)
            printf("B (Average)");
        else if (percentage >= 55)
            printf("B- (Below Average)");
        else if (percentage >= 50)
            printf("C+ (Needs Improvement)");
        else if (percentage >= 45)
            printf("C (Poor)");
        else if (percentage >= 40)
            printf("D (Very Poor)");
        else
            printf("F (Fail)");
        printf("\n");
        printf("-----------------------------------------\n");
    }
}

void displayStudent()
{
    if (studentCount == 0)
    {
        printf("\nNo students to display.\n");
        return;
    }

    int rollNumber;
    char name[MAX_NAME_LENGTH];
    printf("\n1. Search by Roll Number\n");
    printf("2. Search by Name\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\nEnter roll number: ");
        scanf("%d", &rollNumber);

        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].rollNumber == rollNumber)
            {
                // Calculate total and percentage
                int total = 0;
                for (int j = 0; j < MAX_SUBJECTS; j++)
                {
                    total += students[i].marks[j];
                }
                float percentage = (float)total / MAX_SUBJECTS;

                printf("\n============= Student Details =============\n");
                printf("Roll Number: %d\n", students[i].rollNumber);
                printf("Name: %s\n", students[i].name);
                printf("\nMarks Details:\n");
                printf("  CSE103: %d\n", students[i].marks[0]);
                printf("  CSE106: %d\n", students[i].marks[1]);
                printf("  ENG099: %d\n", students[i].marks[2]);
                printf("  CHE109: %d\n", students[i].marks[3]);
                printf("  MAT101: %d\n", students[i].marks[4]);
                printf("\n-----------------------------------------\n");
                printf("Total Marks: %d / %d\n", total, MAX_SUBJECTS * 100);
                printf("Percentage: %.2f%%\n", percentage);

                // Grade
                printf("Grade: ");
                if (percentage >= 80)
                    printf("A+");
                else if (percentage >= 75)
                    printf("A");
                else if (percentage >= 70)
                    printf("A-");
                else if (percentage >= 65)
                    printf("B+");
                else if (percentage >= 60)
                    printf("B");
                else if (percentage >= 55)
                    printf("B-");
                else if (percentage >= 50)
                    printf("C+");
                else if (percentage >= 45)
                    printf("C");
                else if (percentage >= 40)
                    printf("D");
                else
                    printf("F");
                printf("\n===========================================\n");
                return;
            }
        }
        printf("\n✗ Student with roll number %d not found.\n", rollNumber);
    }
    else if (choice == 2)
    {
        printf("\nEnter name: ");
        clearInputBuffer();
        fgets(name, MAX_NAME_LENGTH, stdin);
        strtok(name, "\n");

        int found = 0;
        for (int i = 0; i < studentCount; i++)
        {
            if (strcmp(students[i].name, name) == 0)
            {
                // Calculate total and percentage
                int total = 0;
                for (int j = 0; j < MAX_SUBJECTS; j++)
                {
                    total += students[i].marks[j];
                }
                float percentage = (float)total / MAX_SUBJECTS;

                printf("\n============= Student Details =============\n");
                printf("Roll Number: %d\n", students[i].rollNumber);
                printf("Name: %s\n", students[i].name);
                printf("\nMarks Details:\n");
                printf("  CSE103: %d\n", students[i].marks[0]);
                printf("  CSE106: %d\n", students[i].marks[1]);
                printf("  ENG099: %d\n", students[i].marks[2]);
                printf("  CHE109: %d\n", students[i].marks[3]);
                printf("  MAT101: %d\n", students[i].marks[4]);
                printf("\n-----------------------------------------\n");
                printf("Total Marks: %d / %d\n", total, MAX_SUBJECTS * 100);
                printf("Percentage: %.2f%%\n", percentage);

                // Grade
                printf("Grade: ");
                if (percentage >= 80)
                    printf("A+");
                else if (percentage >= 75)
                    printf("A");
                else if (percentage >= 70)
                    printf("A-");
                else if (percentage >= 65)
                    printf("B+");
                else if (percentage >= 60)
                    printf("B");
                else if (percentage >= 55)
                    printf("B-");
                else if (percentage >= 50)
                    printf("C+");
                else if (percentage >= 45)
                    printf("C");
                else if (percentage >= 40)
                    printf("D");
                else
                    printf("F");
                printf("\n===========================================\n");
                found = 1;
            }
        }
        if (!found)
            printf("\n✗ Student with name '%s' not found.\n", name);
    }
    else
    {
        printf("\nInvalid choice.\n");
    }
}