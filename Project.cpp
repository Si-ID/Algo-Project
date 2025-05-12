#include <iostream>
using namespace std;

struct Pasien{
    char nama[100];
    char alamat[200];
    char nik[20];
    char ttl[20];
    char poli[50];
};

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
    
    if (file != NULL)
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
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                tambahPasien();
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