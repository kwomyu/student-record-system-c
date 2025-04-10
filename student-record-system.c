#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    int id;
    float grade;
} Student;

Student students[MAX];
int count = 0;

// Function Prototypes
void loadFromFile();
void saveToFile();
void addStudent();
void displayStudents();
void updateStudent();
void deleteStudent();
int findStudentById(int id);

int main() {
    int choice;
    loadFromFile();

    while (1) {
        printf("\n=== Student Record System ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        while ((getchar()) != '\n');

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: saveToFile(); exit(0);
            default: printf("❌ Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void addStudent() {
    if (count >= MAX) {
        printf("❌ Student limit reached.\n");
        return;
    }

    Student s;
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter ID: ");
    scanf("%d", &s.id);
    while ((getchar()) != '\n');

    printf("Enter Grade: ");
    scanf("%f", &s.grade);
    while ((getchar()) != '\n');

    if (findStudentById(s.id) != -1) {
        printf("❌ Student with ID %d already exists.\n", s.id);
        return;
    }

    students[count++] = s;
    printf("✅ Student added successfully.\n");
}

void displayStudents() {
    printf("\n--- Student List ---\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, ID: %d, Grade: %.2f\n", students[i].name, students[i].id, students[i].grade);
    }
}

void updateStudent() {
    int id;
    printf("Enter ID of student to update: ");
    scanf("%d", &id);
    while ((getchar()) != '\n');

    int index = findStudentById(id);
    if (index == -1) {
        printf("❌ Student not found.\n");
        return;
    }

    printf("Enter new name: ");
    fgets(students[index].name, sizeof(students[index].name), stdin);
    students[index].name[strcspn(students[index].name, "\n")] = 0;

    printf("Enter new grade: ");
    scanf("%f", &students[index].grade);
    while ((getchar()) != '\n');

    printf("✅ Student updated.\n");
}

void deleteStudent() {
    int id;
    printf("Enter ID of student to delete: ");
    scanf("%d", &id);
    while ((getchar()) != '\n');

    int index = findStudentById(id);
    if (index == -1) {
        printf("❌ Student not found.\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;
    printf("✅ Student deleted.\n");
}

int findStudentById(int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void saveToFile() {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("❌ Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %.2f\n", students[i].name, students[i].id, students[i].grade);
    }

    fclose(fp);
    printf("💾 Data saved to file.\n");
}

void loadFromFile() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        return;
    }

    while (fscanf(fp, " %49s %d %f", students[count].name, &students[count].id, &students[count].grade) == 3) {
        count++;
    }

    fclose(fp);
    printf("📂 Loaded %d students from file.\n", count);
}

