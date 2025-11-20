#include <stdio.h>
#include <stdlib.h>

void main() {
    //DECLARATION
    FILE *baca, *salin;
    char kar;

    //ALGORITHM
    baca = fopen("data.txt", "a+");       /* { buka arsip data untuk perekaman dalam mode teks } */
    salin = fopen("salin.txt", "w+");     /* { salin arsip data.txt ke arsip salin.txt } */

    printf("menyalin file %s ke %s", "baca.txt", "salin.txt");
    while((kar=fgetc(baca))!=EOF)
        fputc(kar,salin);                     /* { simpan data melalui variabel kar} */

    fclose(baca);                         /* { tutup arsip } */
    fclose(salin);                        /* { tutup arsip } */
}