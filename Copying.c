#include <stdio.h>

typedef struct {
    int id;
    char name[25];
    float grade;
} StudentData;

void copyArchive(FILE *studentFile1, FILE *studentFile2);

int main() {
    FILE *studentFile1;
    FILE *studentFile2;

    copyArchive(studentFile1, studentFile2);
    printf("\nFile copied");

    return 0;
}

void copyArchive(FILE *studentFile1, FILE *studentFile2) {
    StudentData studentRec;

    studentFile1 = fopen("StudentFile.dat", "rb");
    studentFile2 = fopen("StudentFile2.dat", "wb");

    while (fread(&studentRec, sizeof(studentRec), 1, studentFile1) == 1) {
        fwrite(&studentRec, sizeof(studentRec), 1, studentFile2);
    }

    fclose(studentFile1);
    fclose(studentFile2);
}
