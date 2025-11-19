#include <stdio.h>

typedef struct {
    int id;
    char name[25];
    float grade;
} StudentData;

typedef StudentData StudentTab[100];

void copyStudent(char *StudentFile, StudentTab students, int *n);
void countGraduates(char *StudentFile, int *nOver2);
void printAllStudents(StudentTab students, int n);
void exportToCsv(char *StudentFile, StudentTab students, int n);
void averageGradeFromArray(StudentTab students, int n);

int main() {
    StudentTab students;
    int n;
    int numberOfGraduates;

    copyStudent("StudentFile.dat", students, &n);

    printf("\n-- Lihat Data Mahasiswa --\n\n");
    printAllStudents(students, n);

    countGraduates("StudentFile.dat", &numberOfGraduates);
    printf("\nJumlah Mahasiswa Lulus : %d\n", numberOfGraduates);

    exportToCsv("StudentOutput.csv", students, n);

    printf("\n-- Hitung Rata-rata Grade Mahasiswa --\n");
    averageGradeFromArray(students, n);

    return 0;
}

void copyStudent(char *StudentFile, StudentTab students, int *n) {
    FILE *stdFile = fopen(StudentFile, "rb");
    if (stdFile == NULL) {
        printf("Error opening %s (file not found?)\n", StudentFile);
        *n = 0;
        return;
    }

    StudentData studentRec;
    int i = 0;

    while (fread(&studentRec, sizeof(StudentData), 1, stdFile) == 1 && i < 100) {
        students[i] = studentRec;
        i++;
    }

    fclose(stdFile);
    *n = i;
}

void countGraduates(char *StudentFile, int *nOver2) {
    FILE *stdFile = fopen(StudentFile, "rb");
    if (stdFile == NULL) {
        printf("Error opening %s\n", StudentFile);
        return;
    }

    StudentData studentRec;
    *nOver2 = 0;

    while (fread(&studentRec, sizeof(StudentData), 1, stdFile) == 1) {
        if (studentRec.grade > 2.0) {
            (*nOver2)++;
        }
    }

    fclose(stdFile);
}

void printAllStudents(StudentTab students, int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Grade: %.2f\n\n", students[i].grade);
    }
}

void exportToCsv(char *StudentFile, StudentTab students, int n) {
    FILE *file = fopen(StudentFile, "w");
    if (file == NULL) {
        printf("Couldn't open %s for writing\n", StudentFile);
        return;
    }

    fprintf(file, "sep=,\n");
    fprintf(file, "ID,Name,Grade\n");

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d,%s,%.2f\n",
                students[i].id,
                students[i].name,
                students[i].grade);
    }

    fclose(file);
    printf("Data successfully saved to %s\n", StudentFile);
}

void averageGradeFromArray(StudentTab students, int n) {
    if (n == 0) {
        printf("Tidak ada data mahasiswa.\n");
        return;
    }

    float total = 0.0;
    for (int i = 0; i < n; i++) {
        total += students[i].grade;
    }

    float avg = total / n;

    printf("Rata-rata Grade %d Mahasiswa adalah : %.2f\n", n, avg);
}
