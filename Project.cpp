#include <iostream>
#include <cstdio> // For FILE operations
#include <cstring> // For string operations
using namespace std;

// Struktur data Pasien
struct Pasien {
    char nama[100];
    char alamat[200];
    char nik[20];
    char ttl[20];
    char poli[50];
    struct Pasien* next; // Pointer untuk linked list
};

// Alias untuk pointer ke struktur Pasien
typedef Pasien* PtrPasien;

// Fungsi untuk membuat node pasien baru
PtrPasien buatPasienBaru() {
    PtrPasien pasienBaru = new Pasien;
    pasienBaru->next = NULL;
    return pasienBaru;
}

// Fungsi untuk menginput data pasien
void inputDataPasien(PtrPasien pasien) {
    cout << "Masukkan Nama Pasien: ";
    cin.ignore();
    cin.getline(pasien->nama, 100);
    
    cout << "Masukkan Alamat Pasien: ";
    cin.getline(pasien->alamat, 200);
    
    cout << "Masukkan NIK Pasien: ";
    cin.getline(pasien->nik, 20);
    
    cout << "Masukkan Tanggal Lahir Pasien: ";
    cin.getline(pasien->ttl, 20);
    
    cout << "Masukkan Poli yang dituju: ";
    cin.getline(pasien->poli, 50);
}

// Fungsi untuk menambahkan pasien ke linked list
void tambahPasien(PtrPasien &head, PtrPasien pasienBaru) {
    if (head == NULL) {
        head = pasienBaru;
    } else {
        PtrPasien temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = pasienBaru;
    }
}

// Fungsi untuk menyimpan data pasien ke file menggunakan pointer FILE
void simpanDataPasienKeFile(PtrPasien pasien) {
    FILE *filePointer;
    
    // Membuka file dalam mode append (menambahkan data)
    filePointer = fopen("dataPasien.txt", "a");
    
    // Cek apakah file berhasil dibuka
    if (filePointer == NULL) {
        cout << "Error: Tidak dapat membuka file dataPasien.txt" << endl;
        return;
    }
    
    // Menulis data pasien ke file
    fprintf(filePointer, "Nama: %s\n", pasien->nama);
    fprintf(filePointer, "Alamat: %s\n", pasien->alamat);
    fprintf(filePointer, "NIK: %s\n", pasien->nik);
    fprintf(filePointer, "TTL: %s\n", pasien->ttl);
    fprintf(filePointer, "Poli: %s\n", pasien->poli);
    fprintf(filePointer, "--------------------------------\n");
    
    // Menutup file
    fclose(filePointer);
    
    cout << "Data pasien berhasil disimpan ke file dataPasien.txt" << endl;
}

// Fungsi untuk menampilkan semua data pasien dari linked list
void tampilkanPasienDariFile() {
    FILE *file = fopen("dataPasien.txt", "r");

    if (file == NULL) {
        cout << "File tidak ditemukan atau belum ada data pasien." << endl;
        return;
    }

    char baris[200];
    int nomor = 1;

    cout << "\n===== DAFTAR DATA PASIEN =====\n";

    while (fgets(baris, sizeof(baris), file)) {
        if (strncmp(baris, "Nama:", 5) == 0) {
            cout << "\nData Pasien #" << nomor++ << endl;
        }
        cout << baris; // Tampilkan setiap baris seperti aslinya
    }

    fclose(file);
}


// Fungsi untuk membersihkan memori linked list
void bersihkanMemori(PtrPasien &head) {
    PtrPasien temp;
    
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    PtrPasien headPasien = NULL;
    int pilihan;
    
    do {
        cout << "\n==== SISTEM MANAJEMEN DATA PASIEN ====" << endl;
        cout << "1. Tambah Data Pasien" << endl;
        cout << "2. Tampilkan Semua Data Pasien" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                PtrPasien pasienBaru = buatPasienBaru();
                inputDataPasien(pasienBaru);
                tambahPasien(headPasien, pasienBaru);
                simpanDataPasienKeFile(pasienBaru);
                break;
            }
            case 2:
                tampilkanPasienDariFile();
                break;
            case 3:
                cout << "Terima kasih telah menggunakan sistem ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 3);
    
    // Membersihkan memori sebelum program berakhir
    bersihkanMemori(headPasien);
    
    return 0;
}