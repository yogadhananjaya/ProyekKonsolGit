#include <stdio.h>
#include <string.h>

typedef struct kendaraan {
    int id;
    char plat[20];
    char jenis[20];
    int tahun;
}kendaraan;

void tambahKendaraan(char* transFile);
void lihatKendaraan(char* transFile);
void ubahPlat(char * transFile);
void hapusdata(char * transFile);

int main() {
    int pilih;
    char transFile[50]= "kendaraan.dat";

    do {
        printf("\n****DATA KENDARAAN****\n");
        printf("1. Tambah Kendaraan \n");
        printf("2. Lihat Kendaraan \n");
        printf("3. Ubah Plat \n");
        printf("4. Hapus Data \n");
        printf("5. Keluar \n");
        printf("Pilih Menu :\n");
        scanf("%d",&pilih);

        switch (pilih) {
            case 1: tambahKendaraan(transFile); break;
                case 2: lihatKendaraan(transFile); break;
                case 3: ubahPlat(transFile); break;
                case 4: hapusdata(transFile); break;
                case 5: printf("Keluar...\n"); break;
                default: printf("Menu Tidak Valid!\n");
        }
    } while (pilih != 5);
    return 0;
}
void tambahkendaraan(char* transFile) {
    FILE* file = fopen(transFile, "ab");
    kendaraan k ;

    printf("ID : ");
    scanf("%d",&k.id);
    printf("Plat : ");
    scanf("%d",&k.plat);
    printf("Jenis : ");
    scanf("%d",&k.jenis);
    printf("Tahun : ");
    scanf("%d",&k.tahun);

    fwrite (&k, sizeof(k), 1, file);
    fclose(file);

    printf("Data Berhasil Ditambahkan\n");
}
void lihatKendaran(char* transFile) {
    FILE* file = fopen(transFile, "rb");
    kendaraan k ;

    if (!file) {
        printf ("Arsip tidak ada\n");
        return;
    }
    printf("\n****DATA KENDARAAN****\n");
    while (fread(&k, sizeof(kendaraan), 1, file)) {
        printf("ID : %d\n", k.id);
        printf("Plat : %s\n", k.plat);
        printf("Jenis : %s\n", k.jenis);
        printf("Tahun : %d\n", k.tahun);
    }
    fclose(file);
}
void ubahPlat(char* transFile) {
    FILE* file = fopen(transFile, "rb+");
    kendaraan k ;
    int target ;
    int found = 0;

    if (!file) {
        printf ("Arsip tidak ada\n");
        return;
    }
    printf("Masukkan ID Kendaraan : ");
    scanf("%d",&target);

    while (fread(&k, sizeof(kendaraan), 1, file)) {
        if (k.id == target) {
            printf("Nomor Plat Baru :");
            scanf("%s",&k.plat);

            fseek(file, -sizeof(kendaraan), SEEK_CUR);
            fwrite(&k, sizeof(kendaraan), 1, file);

            found = 1;
            break;

        }
    }
    fclose(file);

    if (!found)
        printf ("Nomor Plat Berhasil Diubah\n");
    else
        printf("Data tidak ditemukan");
}

void hapusdata(char * transFile) {
    FILE* file = fopen(transFile, "rb");
    FILE *temp = fopen("temp.dat","wb");
    kendaraan k ;
    int target ;
    int found = 0;

    if (!file) {
        printf ("Arsip tidak ada\n");
        return;
    }

    printf("Masukkan ID Kendaraan Yang Akan Dihapus : ");
    scanf("%d",&target);

    while (fread(&k, sizeof(kendaraan), 1, file)) {
        if (k.id == target) {
            fwrite(&k, sizeof(kendaraan), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);

    remove (transFile);
    rename("temp.dat", transFile);

    if (found)
        printf("Data berhasil dihapus");
    else
        printf("Data tidak ditemukan");
}
