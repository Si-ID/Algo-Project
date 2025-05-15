#include <iostream>
#include <cstring>
using namespace std;

struct Pasien{
    char nama[100];
    char alamat[200];
    char nik[20];
    char ttl[20];
    char poli[50];
};

void lihatAntrian(){
    FILE *file;
    file = fopen("dataPasien.txt","r");

    if (file == NULL)
    {
        cout << "File tidak ditemukan atau belum ada daftar antrian!" << endl;
        return;
    }

    char line[500];
    int nomorPasien = 0;
    
    cout << "\n===== DAFTAR ANTRIAN PASIEN =====\n";
    
    // Membaca file dan tampilkan langsung
    while (fgets(line, sizeof(line), file) != NULL) {
        // Jika menemukan baris "Nama:", berarti data pasien baru
        if (strncmp(line, "Nama:", 5) == 0) {
            nomorPasien++;
            cout << "\nPasien " << nomorPasien << "." << endl;
        }
        
        // Tampilkan baris data
        cout << line;
    }
    
    fclose(file);
    
    if (nomorPasien == 0) {
        cout << "Belum ada data pasien yang tersimpan.\n";
    }    
}

void tambahPasien(){
    Pasien pasien;

    cout << "<========== TAMBAHKAN DATA PASIEN =======>\n";
    cin.ignore();
    cout << "Nama: "; cin.getline(pasien.nama, 100);
    cout << "Alamat: "; cin.getline(pasien.alamat, 200);
    cout << "NIK: "; cin.getline(pasien.nik, 20); 
    cout << "Tanggal Lahir: "; cin.getline(pasien.ttl, 20);
    cout << "Poli: "; cin.getline(pasien.poli, 50);

    FILE *file;
    file = fopen("dataPasien.txt","a"); // Append utk menambahkan data baru
    
    if (file == NULL)
    {
        cout << "Error Tidak dapat membuka File!" << endl;
        return;
    }

    // Menulis Data Pasien ke file
    fprintf(file, "Nama: %s\n", pasien.nama);
    fprintf(file, "Alamat: %s\n", pasien.alamat);
    fprintf(file, "NIK: %s\n", pasien.nik);
    fprintf(file, "Tanggal Lahir: %s\n", pasien.ttl);
    fprintf(file, "Poli: %s\n", pasien.poli);
    fprintf(file, "================================\n");

    fclose(file);
    cout << "\nData pasien Berhasil di simpan!";
}

// Searching atau pencarian berdasarkan nama 
int searchingPasien(Pasien data[], int x, string nama) {
    for (int i = 0; i < x; i++) {
        if (data[i].nama == nama) {
            return i; 
        }
    }
    return -1; 
}

// Searching dengan metode sequential search (linear search)
void searching_Pasien() {
    Pasien data[100]; 
    int pasien = 0; 
    string cari_nama; 

    FILE *file;
    file = fopen("dataPasien.txt","r"); // Append utk menambahkan data baru
    
    if (file == NULL)
    {
        cout << "Error Tidak dapat membuka File!" << endl;
        return;
    }  

    char line[200]; 

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Nama:", 5) == 0) {
            strcpy(data[pasien].nama, line + 6); // Lewati "Nama:"
            data[pasien].nama[strcspn(data[pasien].nama, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].alamat, line + 8); 
            data[pasien].alamat[strcspn(data[pasien].alamat, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].nik, line + 5); 
            data[pasien].nik[strcspn(data[pasien].nik, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].ttl, line + 15); 
            data[pasien].ttl[strcspn(data[pasien].ttl, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].poli, line + 6); 
            data[pasien].poli[strcspn(data[pasien].poli, "\n")] = 0; 

            fgets(line, sizeof(line), file); // Baris pemisah "==========="
            pasien++; 
        }
    }

    fclose(file); 

    cin.ignore(); 
    cout << "Masukkan nama pasien yang akan dicari : "; 
    getline(cin, cari_nama); 
    cout << endl; 

    int hasil_nama = searchingPasien(data, pasien, cari_nama); 

    if (hasil_nama != -1) {
        cout << "Data pasien ditemukan\n"; 
        cout << "Nama           : " << data[hasil_nama].nama << endl; 
        cout << "Alamat         : " << data[hasil_nama].alamat << endl;
        cout << "NIK            : " << data[hasil_nama].nik << endl; 
        cout << "Tanggal Lahir  : " << data[hasil_nama].ttl << endl;
        cout << "Poli           : " << data[hasil_nama].poli << endl;
    } else {
        cout << "Pasien dengan nama " << cari_nama << " tidak ditemukan\n"; 
    }
}

// Sorting atau pengurutan berdasarkan nama dengan straight insertion sort 
int sortingPasien(Pasien arr[], int n) {
    int i, j; 
    Pasien key; 

    for (i = 1; i < n; i++) {
        key = arr[i]; 
        j = i - 1; 
        while (j >= 0 && arr[j].nama > key.nama) {
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        }
        arr[j + 1] = key; 
    }
}

void sorting_Pasien() {
    Pasien data[100]; 
    int pasien = 0; 

    FILE *file;
    file = fopen("dataPasien.txt","r"); // Append utk menambahkan data baru
    
    if (file == NULL)
    {
        cout << "Error Tidak dapat membuka File!" << endl;
        return;
    }  

    char line[200]; 

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Nama:", 5) == 0) {
            strcpy(data[pasien].nama, line + 6); // Lewati "Nama:"
            data[pasien].nama[strcspn(data[pasien].nama, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].alamat, line + 8); 
            data[pasien].alamat[strcspn(data[pasien].alamat, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].nik, line + 5); 
            data[pasien].nik[strcspn(data[pasien].nik, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].ttl, line + 15); 
            data[pasien].ttl[strcspn(data[pasien].ttl, "\n")] = 0; 

            fgets(line, sizeof(line), file); 
            strcpy(data[pasien].poli, line + 6); 
            data[pasien].poli[strcspn(data[pasien].poli, "\n")] = 0; 

            fgets(line, sizeof(line), file); // Baris pemisah "==========="
            pasien++; 
        }
    }

    fclose(file); 

    sortingPasien(data, pasien); 

    cout << "\nBerikut adalah data pasien setelah diurutkan berdasarkan nama :\n"; 
    for (int i = 0; i < pasien; i++) { 
        cout << "Nama           : " << data[i].nama << endl; 
        cout << "Alamat         : " << data[i].alamat << endl;
        cout << "NIK            : " << data[i].nik << endl; 
        cout << "Tanggal Lahir  : " << data[i].ttl << endl;
        cout << "Poli           : " << data[i].poli << endl;
        cout << "================================" << endl; 
    }
}

int main(){
int pilihan;
    
    do {
        cout << "\n===== MENU SISTEM MANAJEMEN PASIEN =====\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Lihat Antrian\n";
        cout << "3. Mencari Data Pasien\n"; 
        cout << "4. Mengurutkan Data Pasien\n"; 
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        system("cls");
        switch(pilihan) {
            case 1:
                system("cls");
                tambahPasien();
                break;
            case 2: 
                system("cls");
                lihatAntrian();
                system("pause");
                break;
            case 3: 
                system("cls"); 
                searching_Pasien(); 
                system("pause"); 
                break; 
            case 4: 
                system("cls"); 
                sorting_Pasien(); 
                system("pause"); 
                break; 
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 0);
    
    return 0; 
}