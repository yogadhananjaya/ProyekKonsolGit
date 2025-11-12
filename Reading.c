#include <stdio.h>

typedef struct {
    int id;
    char name[25];
    float grade;
} StudentData;

void countGraduates(FILE *stdFile, int *nOver2);

int main() {
    FILE *studentFile;
    int numberOfGraduates;

    countGraduates(studentFile, &numberOfGraduates);
    printf("\nNumber of Graduates is %d", numberOfGraduates);

    return 0;
}

void countGraduates(FILE *stdFile, int *nOver2) {
    StudentData studentRec;

    *nOver2 = 0;
    stdFile = fopen("StudentFile.dat", "rb");

    while (fread(&studentRec, sizeof(studentRec), 1, stdFile) == 1) {
        if (studentRec.grade > 2.0) {
            *nOver2 = *nOver2 + 1;
        }
    }

    fclose(stdFile);
}
