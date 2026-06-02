#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Kontak {
    string nama;
    long long no_telp;
    string email;
};

long long inputNoTelp() {
    long long noTelp;
    while (true) {
        cin >> noTelp;
        if (cin.fail()) {
            cout << "\t| ERROR!!! No Telepon JUST boleh berisi angka YO!" << endl;
            cout << "\t| No Telepon\t";
            cin.clear();
            cin.ignore(1000, '\n'); 
        } 
        else {
			cin.ignore();
            return noTelp;
        }
    }
}

int inputJumlahKontak() {
    int jumlah;

    while (true) {
        cin >> jumlah;
        if (cin.fail()) {
            cout << "\tERROR! Jumlah kontak harus berupa angka bulat.\n";
            cout << "\tMasukkan jumlah kontak: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (jumlah <= 0) {
            cout << "\tERROR! Jumlah kontak harus lebih dari 0.\n";
            cout << "\tMasukkan jumlah kontak: ";
            cin.ignore(1000, '\n');
        }
        else {
            cin.ignore(1000, '\n');
            return jumlah;
        }
    }
}

Kontak daftarKontak[100];
int totalKontak = 0;

void tambahKontak() {
    if (totalKontak >= 100) {
        cout << "\t SUdah penuh nggih!" << endl;
        return;
    }
    
    int jumlah;
    cout << "\tMasukkan jumlah kontak mbak: ";
    jumlah = inputJumlahKontak();
     if (totalKontak + jumlah > 100) {
        cout << "\tKapasitas tidak mencukupi!" << endl;
        cout << "\tSisa slot kontak: " << 100 - totalKontak << endl;
        return;
    }
    for (int i = 0; i < jumlah; i++) {
        cout << "\n\t=============== KONTAK KE-" << i + 1 << " ===============" << endl;
		cout << "\t| Nama\t\t:";
		getline(cin, daftarKontak[totalKontak].nama);
		cout << "\t| No Telepon\t:";
		daftarKontak[totalKontak].no_telp = inputNoTelp();
		cout << "\t| Email\t\t:";
		getline(cin, daftarKontak[totalKontak].email);
		totalKontak++;
		cout << "\t|-----------------------------------------|" << endl;
		cout << "\n\t THE DATA BERHASIL DITAMBAHKAN NGGIH." << endl;
	}
}

void lihatKontakRekursif(int i) {
    if (i >= totalKontak) {
        return;
    }
    cout << "\t|" << i+1 << ". Nama\t\t: " << daftarKontak[i].nama << endl;
    cout << "\t|   No Telpon\t\t: " << daftarKontak[i].no_telp << endl;
    cout << "\t|   Email\t\t: " << daftarKontak[i].email << endl;
    cout << "\t__________________________________________" << endl;
    lihatKontakRekursif(i + 1);
}

void tampilkanSemua() {
    cout << "\t,_________________________________________," << endl;
    cout << "\t|                                         |" << endl;
    cout << "\t|               DAFTAR KONTAK             |" << endl;
    cout << "\t|-----------------------------------------|" << endl;
    if (totalKontak == 0) {
        cout << "\t Masih kosong bro, tambah dulu" << endl;
        return;
    }
    lihatKontakRekursif(0);
}

void swapKontak(Kontak *a, Kontak *b) {
    Kontak temp = *a;
    *a = *b;
    *b = temp;
}

void urutkanBerdasarkanNama() {
    if (totalKontak == 0) {
        cout << "\t Masih Kosong atuh kang, ga bisa ngurutin. " << endl;
        return;
    }
    for (int i = 0; i < totalKontak - 1; i++) {
        for (int j = 0; j < totalKontak - i - 1; j++) {
            if (daftarKontak[j].nama > daftarKontak[j+1].nama) {
                swapKontak(&daftarKontak[j], &daftarKontak[j+1]);
            }
        }
    }
    cout << "\t=== HASIL SETELAH DIURUTKAN ===" << endl;
    tampilkanSemua();  
}

int cariKontakRekursif(int kiri, int kanan, string target) {
    if (kiri > kanan) {
        return -1;
    }
    int tengah = (kiri + kanan) / 2;
    if (daftarKontak[tengah].nama == target) {
        return tengah;
    }
    else if (daftarKontak[tengah].nama > target) {
        return cariKontakRekursif(kiri, tengah - 1, target);
    }
    else {
        return cariKontakRekursif(tengah + 1, kanan, target);
    }
}

void cariKontak() {
    if (totalKontak == 0) {
        cout << "\t Masih kosong ih \n";
        return;
    }
    
    string keyword;
    cout << "\t=============== CARI KONTAK =============="  << endl;
    cout << "\t| Nama yang dicari: ";
    cin.ignore();
    getline(cin, keyword);
    
    for (int i = 0; i < totalKontak - 1; i++) {
        for (int j = 0; j < totalKontak - i - 1; j++) {
            if (daftarKontak[j].nama > daftarKontak[j+1].nama) {
                swapKontak(&daftarKontak[j], &daftarKontak[j+1]);
            }
        }
    }
    int posisi = cariKontakRekursif(0, totalKontak - 1, keyword);
    
    if (posisi != -1) {
        cout << "\t| Nama\t\t: " << daftarKontak[posisi].nama << endl;
        cout << "\t| No Telpon\t: " << daftarKontak[posisi].no_telp << endl;
        cout << "\t| Email\t\t: " << daftarKontak[posisi].email << endl;
        cout << "\t__________________________________________" << endl;
        cout << "\tKetemu! YAYYYYY" << endl;
    } else {
        cout << "\tKontak bernama\t:" << keyword << ", ga ketemu. " << endl;
    }
}

void hapusKontak() {
    if (totalKontak == 0) {
        cout << "\tKosong, ga ada yang bisa dihapus" << endl;
        return;
    }
    string namaHapus;
   cout << "\t=============== HAPUS KONTAK ==============" << endl;
   cout << "\t| Nama kontak yang mau dihapus\t: "<< endl;
   cin.ignore();
   getline(cin, namaHapus);
    
    int posisi = -1;
    for (int i = 0; i < totalKontak; i++) {
        if (daftarKontak[i].nama == namaHapus) {
            posisi = i;
            break;
        }
    }
    
    if (posisi == -1) {
		cout << "\t__________________________________________" << endl;
        cout << "\tKontak\t\t:" << namaHapus << " ,ga ketemu."<< endl;
        return;
    }
        for (int i = posisi; i < totalKontak - 1; i++) {
        daftarKontak[i] = daftarKontak[i + 1];
    }
    
    totalKontak--;
    cout << "\t__________________________________________" << endl;
    cout << "\tKontak\t:" << namaHapus << " ,udah dihapus!"<< endl;
}

void editKontak() {
    if (totalKontak == 0) {
        cout << "\t Data Kosong, ga bisa edit bang."<< endl;
        return;
    }
    
    string namaEdit;
    cout << "\t=============== EDIT KONTAK ==============" << endl;
    cout << "\t| Nama kontak yang mau diedit: ";
    cin.ignore();
    getline(cin, namaEdit);
    
    int posisi = -1;
    for (int i = 0; i < totalKontak; i++) {
        if (daftarKontak[i].nama == namaEdit) {
            posisi = i;
            break;
        }
    }
        if (posisi == -1) {
		cout << "\t__________________________________________" << endl;
        cout << "\tKontak\t:" << namaEdit << " ga ketemu" << endl;
        return;
    }
    
    cout << "\t------------------ Data lama -----------------" <<  endl;
    cout << "\t| Nama\t\t: " << daftarKontak[posisi].nama << endl;
    cout << "\t| No Telpon\t: " << daftarKontak[posisi].no_telp << endl;
    cout << "\t| Email\t\t: " << daftarKontak[posisi].email << endl;
    cout << "\t|_____________________________________________" << endl;
    cout << "\t------------------ Data baru -----------------" <<  endl;
    cout << "\t| Nama baru\t: ";
    getline(cin, daftarKontak[posisi].nama);
    cout << "\t| No Telpon baru\t: ";
    daftarKontak[posisi].no_telp = inputNoTelp();
    cout << "\t| Email baru\t: ";
    getline(cin, daftarKontak[posisi].email);
    cout << "\t|_____________________________________________" << endl;
    cout << "\tKontak berhasil diupdate!" <<  endl;
}

void simpanKeFile() {
    ofstream file("kontak.txt");
    if (!file) {
        cout << "\tGagal nyimpen file! "  << endl;
        return;
    } 
    file << totalKontak << endl;
    for (int i = 0; i < totalKontak; i++) {
        file << daftarKontak[i].nama << endl;
        file << daftarKontak[i].no_telp << endl;
        file << daftarKontak[i].email << endl;
    }
    file.close();
    cout << "\tData disimpan ke kontak.txt (" << totalKontak << " kontak)" << endl;
}

void loadDariFile() {
    ifstream file("kontak.txt");
    if (!file) {
        cout << "\tFile kontak.txt ga ada, mulai dari kosong ajalah ndoro." << endl;
        return;
    }
    file >> totalKontak;
    file.ignore();
    
    for (int i = 0; i < totalKontak; i++) {
        getline(file, daftarKontak[i].nama);
        file >> daftarKontak[i].no_telp;
        file.ignore();
        getline(file, daftarKontak[i].email);
    }
    file.close();
    cout << "\tLoad berhasil! " << totalKontak << " kontak ditemukan" << endl;
}

int main() {
    int pilihan;
    
    ifstream cekFile("kontak.txt");
    if (cekFile) {
        cekFile.close();
        loadDariFile();
    }
    
    do {
		cout <<"\n\n";
        cout << "\t=======================================================" << endl;
        cout << "\t|            _______________________________          |" << endl;                                 
        cout << "\t|            |  APLIKASI MANAJEMEN KONTAK  |          |" << endl; 
        cout << "\t|            _______________________________          |" << endl; 
        cout << "\t|                                                     |" << endl; 
        cout << "\t=======================================================" << endl; 
        cout << "\t|    1. Tambah Kontak                                 |" << endl; 
        cout << "\t|    2. Lihat Semua Kontak                            |" << endl; 
        cout << "\t|    3. Urutkan Berdasarkan Nama                      |" << endl; 
        cout << "\t|    4. Cari Kontak                                   |" << endl; 
        cout << "\t|    5. Hapus Kontak                                  |" << endl; 
        cout << "\t|    6. Edit Kontak                                   |" << endl; 
        cout << "\t|    7. Simpan ke File                                |" << endl; 
        cout << "\t|    8. Load dari File                                |" << endl; 
        cout << "\t|    9. Keluar                                        |" << endl; 
        cout << "\t-------------------------------------------------------" << endl; 
        cout << "\tPilih nggih : "; 
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                tambahKontak();
                break;
            case 2:
                tampilkanSemua();
                break;
            case 3:
                urutkanBerdasarkanNama();
                break;
            case 4:
                cariKontak();
                break;
            case 5:
                hapusKontak();
                break;
            case 6:
                editKontak();
                break;
            case 7:
                simpanKeFile();
                break;
            case 8:
                loadDariFile();
                break;
            case 9:
                cout << "\t Matur Suwun udah pake program this! Dadah~ " << endl; 
                break;
            default:
                cout << "\t Salah pilih, coba 1-9 " << endl; 
        }
    } 
    while(pilihan != 9);
    return 0;
}
