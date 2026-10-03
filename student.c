#include <stdio.h>
#include <string.h>

struct Student
{
    int rollNo;
    char name[50];
    float marks;
};

void addStudent()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully.\n");
}

void displayStudents()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("\nStudent Records:\n");

    while(fread(&s, sizeof(s), 1, fp))
    {
        printf("\nRoll Number: %d", s.rollNo);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    int roll, found = 0;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.rollNo == roll)
        {
            printf("\nRoll Number: %d", s.rollNo);
            printf("\nName: %s", s.name);
            printf("\nMarks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
        printf("Student not found.\n");
}

void updateStudent()
{
    struct Student s;
    int roll, found = 0;
    FILE *fp;

    fp = fopen("students.dat", "rb+");

    if(fp == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.rollNo == roll)
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            printf("Student updated successfully.\n");
            break;
        }
    }

    fclose(fp);

    if(!found)
        printf("Student not found.\n");
}

void deleteStudent()
{
    struct Student s;
    int roll, found = 0;
    FILE *fp, *temp;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if(fp == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.rollNo == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== Student Management System =====");
        printf("\n1. Add Student");
        printf("\n2. Delete Student");
        printf("\n3. Update Student");
        printf("\n4. Search Student");
        printf("\n5. Display Students");
        printf("\n6. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
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
                searchStudent();
                break;

            case 5:
                displayStudents();
                break;

            case 6:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 6);

    return 0;
}