#include <stdio.h>

main() {
    //DECLARATION
    FILE *Bil;    /* { arsip bilangan bulat } */
    int n;        /* { banyaknya bilangan bulat } */
    int i;        /* { pencacah pengulangan } */
    int x;        /* { peubah bil bulat dibaca dari keyboard } */

    //ALGORITHM
    Bil = fopen("data.txt", "w"); /* { buka arsip ArsBil untuk perekaman dalam mode teks } */
    printf("jumlah bilangan = "); scanf("%d", &n);
    for(i=1;i <=n;i++)
    {
        printf("bilangan = "); scanf("%d", &x); /* { baca data dari keyboard } */
        fprintf(Bil, "%d\n", x); /* { simpan data integer tsb dalam ArsBil} */
    }
    fclose(Bil);
}