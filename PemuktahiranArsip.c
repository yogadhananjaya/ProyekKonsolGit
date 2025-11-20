#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Untuk tipe data boolean

// Definisi tipe data rekaman (DataMhs)
typedef struct {
    int NIM;
    char Nama[50];
    float IP;
} DataMhs;

// Prosedur UpdateData sesuai Pseudocode
void UpdateData(char *namaFile, int X) {
    // DEKLARASI
    FILE *Asal;     // ArsipMhs
    FILE *Temp;     // ArsipMhs (arsip temporer)
    DataMhs RekMhs;
    float Ipbaru;
    bool Ketemu;

    // ALGORITMA
    // 1. Buka arsip
    Asal = fopen(namaFile, "rb"); // Mode "rb" untuk membaca binary data
    if (Asal == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }
    Temp = fopen("temp.dat", "wb"); // Mode "wb" untuk menulis binary data

    // 2. Cari rekaman dengan NIM = X
    Ketemu = false;

    // Teknik membaca file di C agar sesuai logika While Not EOF
    // Kita lakukan pembacaan pertama (priming read)
    fread(&RekMhs, sizeof(DataMhs), 1, Asal);

    while (!Ketemu && !feof(Asal)) {
        if (RekMhs.NIM == X) {
            Ketemu = true;
            // Loop berhenti, data target ada di variabel RekMhs
        } else {
            // Salin ke arsip Temp rekaman yang NIM-nya != X
            fwrite(&RekMhs, sizeof(DataMhs), 1, Temp);
            // Baca rekaman selanjutnya
            fread(&RekMhs, sizeof(DataMhs), 1, Asal);
        }
    }

    // 3. Proses Update jika ketemu
    if (Ketemu) {
        // Tampilkan data yang lama
        printf("\nData Ditemukan:\n");
        printf("NIM : %d\n", RekMhs.NIM);
        printf("Nama: %s\n", RekMhs.Nama);
        printf("IP  : %.2f\n", RekMhs.IP);

        // Baca IP yang baru
        printf("Masukkan IP Baru: ");
        scanf("%f", &Ipbaru);

        // Ubah IP lama dengan IPbaru
        RekMhs.IP = Ipbaru;

        // Salin rekaman yang baru ke Temp
        fwrite(&RekMhs, sizeof(DataMhs), 1, Temp);

        // Salin rekaman yang tersisa (setelah rekaman X)
        // Lanjutkan membaca dari file Asal sampai habis
        while (fread(&RekMhs, sizeof(DataMhs), 1, Asal)) {
            fwrite(&RekMhs, sizeof(DataMhs), 1, Temp);
        }
        printf("Update Berhasil.\n");

    } else {
        printf("\nNIM %d tidak ada di dalam arsip Asal.\n", X);
    }

    // 4. Tutup Arsip
    fclose(Asal);
    fclose(Temp);

    // TAMBAHAN (Agar file asli terupdate secara fisik di komputer)
    // Hapus file lama, ganti nama file temp menjadi file asli
    remove(namaFile);
    rename("temp.dat", namaFile);
}

// Main program untuk testing
int main() {
    const char *FILENAME = "data_mhs.dat";

    // --- BAGIAN INI HANYA UNTUK MEMBUAT DUMMY DATA AGAR BISA DITEST ---
    FILE *f = fopen(FILENAME, "wb");
    DataMhs mhs1 = {101, "Budi", 3.20};
    DataMhs mhs2 = {102, "Siti", 3.50};
    DataMhs mhs3 = {103, "Andi", 2.75};
    fwrite(&mhs1, sizeof(DataMhs), 1, f);
    fwrite(&mhs2, sizeof(DataMhs), 1, f);
    fwrite(&mhs3, sizeof(DataMhs), 1, f);
    fclose(f);
    // ------------------------------------------------------------------

    int cariNIM;

    printf("=== PROGRAM UPDATE IP MAHASISWA ===\n");
    printf("Masukkan NIM yang akan diupdate (contoh: 102): ");
    scanf("%d", &cariNIM);

    UpdateData((char*)FILENAME, cariNIM);

    // Verifikasi hasil (Tampilkan semua data setelah update)
    printf("\n=== ISI FILE SETELAH UPDATE ===\n");
    f = fopen(FILENAME, "rb");
    DataMhs tempMhs;
    while(fread(&tempMhs, sizeof(DataMhs), 1, f)){
        printf("NIM: %d | Nama: %s | IP: %.2f\n", tempMhs.NIM, tempMhs.Nama, tempMhs.IP);
    }
    fclose(f);

    return 0;
}