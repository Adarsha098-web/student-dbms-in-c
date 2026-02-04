#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student details
struct student {
    int roll;
    char name[50];
    char course[50];
    int marks;
};

// Function declarations
void add_student();
void display_students();
void search_student();
void delete_student();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Database Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Delete Student by Roll No\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                delete_student();
                break;
            case 0:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again!\n");
        }
    }

    return 0;
}

// Function to add student details to file
void add_student() {
    struct student s;
    FILE *fp = fopen("students.dat", "ab"); // append in binary mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);   // read string with spaces
    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);
    printf("Enter Marks: ");
    scanf("%d", &s.marks);

    fwrite(&s, sizeof(struct student), 1, fp);
    fclose(fp);

    printf("Student record added successfully!\n");
}

// Function to display all students
void display_students() {
    struct student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n%-10s %-20s %-20s %-10s\n", "Roll", "Name", "Course", "Marks");
    printf("---------------------------------------------------------------\n");
    while (fread(&s, sizeof(struct student), 1, fp)) {
        printf("%-10d %-20s %-20s %-10d\n", s.roll, s.name, s.course, s.marks);
    }
    fclose(fp);
}

// Function to search a student by roll number
void search_student() {
    struct student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found!\n");
            printf("Roll: %d\nName: %s\nCourse: %s\nMarks: %d\n",
                   s.roll, s.name, s.course, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with Roll %d not found!\n", roll);
    }
    fclose(fp);
}

// Function to delete a student by roll number
void delete_student() {
    struct student s;
    int roll, found = 0;

    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            continue; // skip writing this record
        }
        fwrite(&s, sizeof(struct student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Record with Roll %d deleted successfully!\n", roll);
    } else {
        printf("Record not found!\n");
    }
}
