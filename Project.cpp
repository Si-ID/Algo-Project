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
    
}

main(){
    cout << "Hello World";
    cout << "test";
    cout << "test";
}