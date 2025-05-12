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
    file    = fopen("dataPasien.txt","a"); // Append utk menambahkan data baru
    
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

main(){
int pilihan;
    
    do {
        cout << "\n===== MENU SISTEM MANAJEMEN PASIEN =====\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Lihat Antrian\n";
        cout << "3. Keluar\n";
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
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 0);
    
    return 0;

}