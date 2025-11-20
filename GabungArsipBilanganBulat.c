#include <stdio.h>

main() {
    //DECLARATION
    FILE *datal, *data2, *salin;
    datal = fopen("data.txt", "a+");
    data2 = fopen("data2.txt", "a+");
    salin = fopen("gabung.txt", "w+");
    char kar;

    //ALGORITHM
    printf("menyalin file %s ke %s", "data.txt", "gabung.txt");
    while((kar=fgetc(datal))!=EOF)
        fputc(kar,salin);

    printf("menyalin file %s ke %s", "data2.txt", "gabung.txt");
    while((kar=fgetc(data2))!=EOF)
        fputc(kar,salin);

    fclose(datal);
    fclose(data2);
    fclose(salin);
}