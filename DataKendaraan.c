#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char plat[20];
    char jenis[30];
    int tahun;
} Kendaraan;

const char *KENDARAAN_FILE = "kendaraan.dat";

void tambahKendaraan();
void lihatKendaraan();
void ubahPlat();
void hapusKendaraan();
void resetData();
int cekIdAda(int id);

int main() {
    int pilih;

    do {
        printf("\n****** DATA KENDARAAN ******\n\n");
        printf("[1] Tambah Data Kendaraan\n");
        printf("[2] Lihat Data Kendaraan\n");
        printf("[3] Ubah Data Kendaraan\n");
        printf("[4] Hapus Data Kendaraan\n");
        printf("[5] Keluar Program\n");
        printf("Pilih Menu : ");

        if (scanf("%d", &pilih) != 1) {
            while(getchar() != '\n');
            pilih = 0;
        }

        switch(pilih) {
            case 1: tambahKendaraan(); break;
            case 2: lihatKendaraan(); break;
            case 3: ubahPlat(); break;
            case 4: hapusKendaraan(); break;
            case 5: printf("\nProgram selesai.\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilih != 5);

    return 0;
}

int cekIdAda(int id) {
    FILE *f = fopen(KENDARAAN_FILE, "rb");
    Kendaraan k;
    if (!f) return 0;
    while (fread(&k, sizeof(Kendaraan), 1, f)) {
        if (k.id == id) { fclose(f); return 1; }
    }
    fclose(f);
    return 0;
}

void tambahKendaraan() {
    FILE *f = fopen(KENDARAAN_FILE, "ab");
    Kendaraan k;

    printf("\n*** Tambah Data Kendaraan ***\n\n");

    while (1) {
        printf("ID Kendaraan   : ");
        scanf("%d", &k.id);

        if (k.id == 9999) {
             printf("Input selesai.\n");
             break;
        }

        if (cekIdAda(k.id)) {
            printf("ID %d sudah ada. Gunakan ID lain.\n\n", k.id);
            continue;
        }

        printf("Nomor Plat     : ");
        scanf(" %[^\n]", k.plat);
        printf("Jenis Kendaraan: ");
        scanf(" %[^\n]", k.jenis);
        printf("Tahun Produksi : ");
        scanf("%d", &k.tahun);

        printf("\n");
        fwrite(&k, sizeof(Kendaraan), 1, f);
        fflush(f);
    }
    fclose(f);
}

void lihatKendaraan() {
    FILE *f = fopen(KENDARAAN_FILE, "rb");
    Kendaraan k;

    if (!f) {
        printf("\n*** Lihat Data Kendaraan ***\n");
        printf("\nData masih kosong.\n");
        return;
    }

    printf("\n*** Lihat Data Kendaraan ***\n");

    while (fread(&k, sizeof(Kendaraan), 1, f)) {
        printf("\nID Kendaraan   : %d\n", k.id);
        printf("Nomor Plat     : %s\n", k.plat);
        printf("Jenis Kendaraan : %s\n", k.jenis);
        printf("Tahun Produksi : %d\n", k.tahun);
    }
    fclose(f);
}

void ubahPlat() {
    FILE *f = fopen(KENDARAAN_FILE, "rb+");
    Kendaraan k;
    int target, found = 0;

    if (!f) { printf("\nFile tidak ditemukan.\n"); return; }

    printf("\n*** Ubah Data Kendaraan ***\n");
    printf("ID Kendaraan : ");
    scanf("%d", &target);

    while (fread(&k, sizeof(Kendaraan), 1, f)) {
        if (k.id == target) {
            printf("\nMasukkan nomor plat baru : ");
            scanf(" %[^\n]", k.plat);

            fseek(f, -(long)sizeof(Kendaraan), SEEK_CUR);
            fwrite(&k, sizeof(Kendaraan), 1, f);
            found = 1;
            printf("Data Kendaraan berhasil diperbaharui!\n");
            break;
        }
    }

    if (!found) {
        printf("\nData Kendaraan dengan ID %d tidak ditemukan!\n", target);
    }
    fclose(f);
}

void hapusKendaraan() {
    FILE *f = fopen(KENDARAAN_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Kendaraan k;
    int target, found = 0;

    if (!f) { printf("\nFile tidak ditemukan.\n"); return; }

    printf("\n*** Hapus Data Kendaraan ***\n");
    printf("ID Kendaraan : ");
    scanf("%d", &target);

    while (fread(&k, sizeof(Kendaraan), 1, f)) {
        if (k.id != target) {
            fwrite(&k, sizeof(Kendaraan), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(f);
    fclose(temp);

    if (found) {
        remove(KENDARAAN_FILE);
        rename("temp.dat", KENDARAAN_FILE);
        printf("Data berhasil dihapus!\n");
    } else {
        remove("temp.dat");
        printf("Data Kendaraan dengan ID %d tidak ditemukan!\n", target);
    }
}
