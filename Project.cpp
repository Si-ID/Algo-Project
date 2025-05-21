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
    fprintf(filePointer, "================================\n");
    
    // Menutup file
    fclose(filePointer);
    
    cout << "Data pasien berhasil disimpan ke file dataPasien.txt" << endl;
}

// Fungsi untuk menyimpan ulang semua data setelah proses penghapusan 
void simpanSeluruhDataKeFile(PtrPasien head) {
    FILE *filePointer; 
    filePointer = fopen("dataPasien.txt", "w");  // Mode tulis (write mode)

    // Cek apakah file berhasil dibuka 
    if (filePointer == NULL) {
        cout << "Error: Tidak dapat membuka file dataPasien.txt" << endl;
        return;
    } 

    PtrPasien temp = head; 
    while (temp != NULL) {
        fprintf(filePointer, "Nama: %s\n", temp->nama);
        fprintf(filePointer, "Alamat: %s\n", temp->alamat);
        fprintf(filePointer, "NIK: %s\n", temp->nik);
        fprintf(filePointer, "TTL: %s\n", temp->ttl);
        fprintf(filePointer, "Poli: %s\n", temp->poli);
        fprintf(filePointer, "================================\n");
        temp = temp->next; 
    }

    // Menutup file
    fclose(filePointer); 
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

    cout << "\n<===== DAFTAR DATA PASIEN =====>\n";

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

// Fungsi untuk melakukan searching atau pencarian berdasarkan nama menggunakan linear search 
void searchingNama(PtrPasien head, const char* cariNama) {
    bool ditemukan = false;
    int nomor = 1; // Untuk menunjukkan urutan pasien yang sedang ditampilkan ada di node berapa (#)

    while (head != NULL) {
        if (strcmp(head->nama, cariNama) == 0) {
            cout << "\nData Pasien Ditemukan #" << nomor << endl; 
            cout << "Nama   : " << head->nama << endl;
            cout << "Alamat : " << head->alamat << endl; 
            cout << "NIK    : " << head->nik << endl; 
            cout << "TTL    : " << head->ttl << endl; 
            cout << "Poli   : " << head->poli << endl;
            cout << "================================" << endl; 
            ditemukan = true; 
        }
        head = head->next; 
        nomor++; 
    }

    if (!ditemukan) {
        cout << "Pasien dengan nama " << cariNama << " tidak ditemukan" << endl; 
    }
}

void cariPasien(PtrPasien headPasien) {
    char cariNama[100]; 
    cin.ignore(); 
    cout << "Masukkan nama pasien yang ingin dicari : "; 
    cin.getline(cariNama, 100);  
    searchingNama(headPasien, cariNama); 
}

void muatDataPasienDariFile(PtrPasien &head) {
    FILE *file = fopen("dataPasien.txt", "r");

    if (file == NULL) {
        cout << "File tidak ditemukan atau belum ada data pasien." << endl;
        return;
    }

    char buffer[256];  // buffer untuk baca baris
    while (true) {
        PtrPasien pasienBaru = new Pasien;
        pasienBaru->next = NULL;

        // Membaca setiap field dengan fgets + sscanf agar lebih aman supaya dapat membaca data baris per baris 
        if (!fgets(buffer, sizeof(buffer), file)) break;
        sscanf(buffer, "Nama: %[^\n]\n", pasienBaru->nama);

        if (!fgets(buffer, sizeof(buffer), file)) break;
        sscanf(buffer, "Alamat: %[^\n]\n", pasienBaru->alamat);

        if (!fgets(buffer, sizeof(buffer), file)) break;
        sscanf(buffer, "NIK: %[^\n]\n", pasienBaru->nik);

        if (!fgets(buffer, sizeof(buffer), file)) break;
        sscanf(buffer, "TTL: %[^\n]\n", pasienBaru->ttl);

        if (!fgets(buffer, sizeof(buffer), file)) break;
        sscanf(buffer, "Poli: %[^\n]\n", pasienBaru->poli);

        // Lewati garis pemisah
        fgets(buffer, sizeof(buffer), file);

        // Tambahkan ke linked list
        tambahPasien(head, pasienBaru);
    }

    fclose(file);
} 

// Fungsi untuk melakukan sorting atau pengurutan berdasarkan nama menggunakan bubble sort 
void bubbleSortNama(PtrPasien &head) {
    if (head == NULL) return; 

    bool swapped;
    PtrPasien ptr; 
    PtrPasien lastSorted = NULL;  

    do {
        swapped = false; 
        ptr = head; 

        while (ptr->next != lastSorted) {
            if (strcmp(ptr->nama, ptr->next->nama) > 0) {
                // Untuk menukar seluruh data pasien 
                swap(ptr->nama, ptr->next->nama); 
                swap(ptr->alamat, ptr->next->alamat); 
                swap(ptr->nik, ptr->next->nik); 
                swap(ptr->ttl, ptr->next->ttl); 
                swap(ptr->poli, ptr->next->poli); 
                swapped = true; 
            } 
            ptr = ptr->next; 
        }
        lastSorted = ptr; 
    } while (swapped); 
}

// Fungsi untuk menampilkan isi linked list 
void tampilkanDataDariLinkedList(PtrPasien head) {
    if (head == NULL) {
        cout << "Data pasien kosong\n";
        return;
    }

    PtrPasien temp = head;
    cout << "\n<===== DAFTAR DATA PASIEN TERURUT =====>\n";
    cout << endl; 

    while (head) {
        cout << "Nama   : " << head->nama << endl;
        cout << "Alamat : " << head->alamat << endl;
        cout << "NIK    : " << head->nik << endl;
        cout << "TTL    : " << head->ttl << endl;
        cout << "Poli   : " << head->poli << endl;
        cout << "================================\n"; 
        head = head->next;
    }
}

// Fungsi untuk menghapus data pasien berdasarkan nama 
void hapusPasien(PtrPasien &head, const char* namaTarget) {
    // Jika list kosong 
    if (head == NULL) {
        cout << "Data pasien kosong" << endl; 
        return; 
    }

    // Jika pasien yang dihapus adalah yang pertama 
    if (strcmp(head->nama, namaTarget) == 0) {
        PtrPasien hapus = head; 
        head = head->next; 
        delete hapus; 
        cout << "Data pasien berhasil dihapus" << endl; 
        return; 
    }

    // Mencari pasien di tengah atau akhir 
    PtrPasien sebelum = head;  // sebelum = menunjuk ke node sebelumnya dari sekarang 
    PtrPasien sekarang = head->next;  // sekarang = menunjuk ke node yang ingin dihapus 

    while (sekarang != NULL) {
        if (strcmp(sekarang->nama, namaTarget) == 0) {
            sebelum->next = sekarang->next; 
            delete sekarang; 
            cout << "Data pasien berhasil dihapus" << endl; 
            return; 
        }
        sebelum = sekarang; 
        sekarang = sekarang->next; 
    }
    cout << "Data pasien tidak ditemukan" << endl; 
}

void menghapusPasien(PtrPasien &head) {
    char cariNama[100]; 
    cin.ignore(); 
    cout << "Masukkan nama pasien yang ingin dihapus : "; 
    cin.getline(cariNama, 100); 
    hapusPasien(head, cariNama); 
    simpanSeluruhDataKeFile(head); 
}

int main() {
    PtrPasien headPasien = NULL;
    muatDataPasienDariFile(headPasien); 
    int pilihan;
    
    do {
        cout << "\n<==== SISTEM MANAJEMEN DATA PASIEN ====>" << endl;
        cout << "\n1. Tambah Data Pasien" << endl;
        cout << "2. Tampilkan Semua Data Pasien" << endl;
        cout << "3. Mencari Data Pasien" << endl; 
        cout << "4. Mengurutkan Data Pasien" << endl; 
        cout << "5. Menghapus Data Pasien" << endl; 
        cout << "0. Keluar" << endl;
        cout << "Pilihan : ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                system("cls"); 
                PtrPasien pasienBaru = buatPasienBaru();
                inputDataPasien(pasienBaru);
                tambahPasien(headPasien, pasienBaru);
                simpanDataPasienKeFile(pasienBaru);
                system("pause"); 
                break;
            }
            case 2:
                system("cls"); 
                tampilkanPasienDariFile();
                system("pause"); 
                break;
            case 3: 
                system("cls"); 
                cariPasien(headPasien); 
                system("pause"); 
                break; 
            case 4:
                system("cls"); 
                bubbleSortNama(headPasien); 
                tampilkanDataDariLinkedList(headPasien); 
                system("pause"); 
                break; 
            case 5: 
                system("cls"); 
                menghapusPasien(headPasien); 
                system("pause"); 
                break; 
            case 0:
                cout << "\nTerima kasih telah menggunakan sistem ini.\n" << endl;
                break;
            default:
                cout << "\nPilihan tidak valid.\n" << endl;
        }
    } while (pilihan != 0);
    
    // Membersihkan memori sebelum program berakhir
    bersihkanMemori(headPasien);
    
    return 0;
}