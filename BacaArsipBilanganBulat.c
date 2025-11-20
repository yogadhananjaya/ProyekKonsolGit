#include <stdio.h>

main() {

    //DECLARATION
    FILE *Bil;    /* { arsip bilangan bulat } */
    int x;        /* { peubah bil bulat dibaca dari keyboard } */

    //ALGORITHM
    Bil = fopen("data.txt", "r"); /* { buka arsip Bil untuk perekaman dalam mode teks } */
    fscanf(Bil, "%d", &x);
    while (!feof(Bil))
    {
        printf("%d \n", x); /* { baca data dari keyboard } */
        fscanf(Bil, "%d", &x); /* { simpan data integer tsb dalam Bil } */
    }
    fclose(Bil);
}