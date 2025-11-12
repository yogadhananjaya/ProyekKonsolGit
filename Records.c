#include <stdio.h>

typedef struct {
    int id;
    char name[25];
    float grade;
} Student;

void main() {
    Student aStudent;
    FILE *studentFile;

    studentFile = fopen("StudentFile.dat", "wb");
    printf("Input Student ID = ");
    scanf("%d", &aStudent.id);

    while (aStudent.id != 9999) {
        printf("Name : ");
        scanf("%s", aStudent.name);
        printf("Grade : ");
        scanf("%f", &aStudent.grade);

        fwrite(&aStudent, sizeof(aStudent), 1, studentFile);

        printf("Input Student ID = ");
        scanf("%d", &aStudent.id);
    }

    fclose(studentFile);
}
