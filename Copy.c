#include <stdio.h>

typedef struct {
    int id;
    char name[25];
    float grade;
} StudentData;

void copyArchive(FILE * studentFile, FILE * studentFILE2);

void main() {
    FILE *studentFile;
    FILE *studentFile2;

    copyArchive(studentFile, studentFile2);
    printf("\n File Copied");
    getchar();
}
void copyArchive(FILE * studentFile, FILE * studentFile2)
{
    StudentData studentRec;
    studentFile = fopen("StudentFile.dat", "wb");
    studentFile2 = fopen("StudentFile2.dat", "wb");
    while (fread(&studentRec,sizeof(studentRec), 1, studentFile) == 1) {
        fwrite(&studentRec, sizeof(studentRec), 1, studentFile2);
    }
fclose(studentFile);
fclose(studentFile2);
}

