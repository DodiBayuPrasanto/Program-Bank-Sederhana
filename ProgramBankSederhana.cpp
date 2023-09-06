#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Nasabah{
    int nomorRekening;
    string nama;
    string alamat;
    int saldo;
    vector<string> mutasi;
};

struct Pengguna{
    string username;
    string password;
    bool isAdmin;
};

vector<Nasabah> nasabahs;
vector<Pengguna> penggunas;

const string FILE_NASABAH = "nasabah.txt";

void loadDataNasabah(){
    ifstream file(FILE_NASABAH);
    if (!file){
        cout << "Gagal membaca file nasabah.txt." << endl;
        return;
    }

    nasabahs.clear();

    int nomorRekening;
    string nama, alamat;
    int saldo;
    string line;

    while (getline(file, line)){
        nomorRekening = stoi(line);
        getline(file, nama);
        getline(file, alamat);
        getline(file, line);
        saldo = stoi(line);

        Nasabah nasabah;
        nasabah.nomorRekening = nomorRekening;
        nasabah.nama = nama;
        nasabah.alamat = alamat;
        nasabah.saldo = saldo;

        string mutasiLine;
        while (getline(file, mutasiLine)){
            if (mutasiLine.empty())
                break;
            nasabah.mutasi.push_back(mutasiLine);
        }

        nasabahs.push_back(nasabah);
    }

    file.close();
}

void saveDataNasabah(){
    ofstream file(FILE_NASABAH);
    if (!file){
        cout << "Gagal menulis file nasabah.txt." << endl;
        return;
    }

    for (const auto &nasabah : nasabahs){
        file << nasabah.nomorRekening << endl;
        file << nasabah.nama << endl;
        file << nasabah.alamat << endl;
        file << nasabah.saldo << endl;

        for (const auto &mutasi : nasabah.mutasi){
            file << mutasi << endl;
        }

        file << endl;
    }

    file.close();
}

void inputDataNasabah(){
    cout << endl;
    Nasabah nasabah;
    cout << "Masukkan Nomor Rekening: ";
    cin >> nasabah.nomorRekening;
    cin.ignore();
    cout << "Masukkan Nama Nasabah: ";
    getline(cin, nasabah.nama);
    cout << "Masukkan Alamat Nasabah: ";
    getline(cin, nasabah.alamat);
    cout << "Masukkan Saldo Awal: ";
    cin >> nasabah.saldo;
    nasabahs.push_back(nasabah);
    saveDataNasabah();
    cout << endl;
    cout << "Data nasabah berhasil ditambahkan." << endl;
}

void cekSaldo(){
    cout << endl;
    int nomorRekening;
    cout << "Masukkan Nomor Rekening: ";
    cin >> nomorRekening;
    bool nasabahDitemukan = false;
    for (const auto &nasabah : nasabahs){
        if (nasabah.nomorRekening == nomorRekening){
            nasabahDitemukan = true;
            cout << "Saldo Nasabah " << nasabah.nama << ": " << nasabah.saldo << endl;
            break;
        }
    }

    if (!nasabahDitemukan){
        cout << "Nasabah dengan nomor rekening tersebut tidak ditemukan." << endl;
    }
}

void transfer(){
    cout << endl;
    int pengirim, penerima, nominal;
    cout << "Masukkan Nomor Rekening Pengirim: ";
    cin >> pengirim;
    cout << "Masukkan Nomor Rekening Penerima: ";
    cin >> penerima;
    cout << "Masukkan Nominal Transfer: ";
    cin >> nominal;

    bool pengirimDitemukan = false;
    bool penerimaDitemukan = false;
    for (auto &nasabah : nasabahs){
        if (nasabah.nomorRekening == pengirim){
            pengirimDitemukan = true;
            if (nasabah.saldo >= nominal){
                nasabah.saldo -= nominal;
                nasabah.mutasi.push_back("Transfer keluar ke nomor rekening " + to_string(penerima) + " sebesar " + to_string(nominal));
                cout << endl;

                cout << "Transfer Berhasil" << endl;
            }else{
                cout << "Saldo pengirim tidak mencukupi." << endl;
            }
        }else if (nasabah.nomorRekening == penerima){
            penerimaDitemukan = true;
            nasabah.saldo += nominal;
            nasabah.mutasi.push_back("Transfer masuk dari nomor rekening " + to_string(pengirim) + " sebesar " + to_string(nominal));
        }
    }

    if (!pengirimDitemukan){
        cout << "Nasabah pengirim dengan nomor rekening tersebut tidak ditemukan." << endl;
    }
    if (!penerimaDitemukan){
        cout << "Nasabah penerima dengan nomor rekening tersebut tidak ditemukan." << endl;
    }
}

void cekMutasi(){
    cout << endl;
    int nomorRekening;
    cout << "Masukkan Nomor Rekening: ";
    cin >> nomorRekening;
    bool nasabahDitemukan = false;
    for (const auto &nasabah : nasabahs){
        if (nasabah.nomorRekening == nomorRekening){
            nasabahDitemukan = true;
            cout << "Mutasi Rekening untuk Nasabah " << nasabah.nama << ":" << endl;
            for (const auto &mutasi : nasabah.mutasi){
                cout << "- " << mutasi << endl;
            }
            break;
        }
    }
    if (!nasabahDitemukan){
        cout << "Nasabah dengan nomor rekening tersebut tidak ditemukan." << endl;
    }
}

void stortunai(){
    cout << endl;
    int nomorRekening;
    cout << "Masukkan Nomor Rekening: ";
    cin >> nomorRekening;
    bool nasabahDitemukan = false;

    for (auto &nasabah : nasabahs){
        if (nasabah.nomorRekening == nomorRekening){
            nasabahDitemukan = true;
            int tambahanSaldo;
            cout << "Masukkan Jumlah Saldo yang Ditambahkan: ";
            cin >> tambahanSaldo;
            nasabah.saldo += tambahanSaldo;
            nasabah.mutasi.push_back("Penambahan saldo sebesar " + to_string(tambahanSaldo));
            cout << "Saldo berhasil ditambahkan." << endl;
            break;
        }
    }
     if (!nasabahDitemukan){
        cout << "Nasabah dengan nomor rekening tersebut tidak ditemukan." << endl;
    }
}

void hapusHistoryTransfer(){
    cout << endl;
    int nomorRekening;
    cout << "Masukkan Nomor Rekening: ";
    cin >> nomorRekening;
    bool nasabahDitemukan = false;

    for (auto &nasabah : nasabahs){
        if (nasabah.nomorRekening == nomorRekening){
            nasabahDitemukan = true;
            nasabah.mutasi.clear();
            cout << "History transfer nasabah berhasil dihapus." << endl;
            break;
        }
    }

    if (!nasabahDitemukan){
        cout << "Nasabah dengan nomor rekening tersebut tidak ditemukan." << endl;
    }
}

void cekRekeningPalingBanyakMutasi(){
    cout << endl;
    unsigned int maxMutasi = 0;
    Nasabah nasabahTerbanyak;

    for (const auto &nasabah : nasabahs){
        if (nasabah.mutasi.size() > maxMutasi){
            maxMutasi = nasabah.mutasi.size();
            nasabahTerbanyak = nasabah;
        }
    }

    if (maxMutasi > 0){
        cout << "Nasabah dengan paling banyak mutasi:" << endl;
        cout << "Nomor Rekening: " << nasabahTerbanyak.nomorRekening << endl;
        cout << "Nama Nasabah: " << nasabahTerbanyak.nama << endl;
        cout << "Jumlah Mutasi: " << nasabahTerbanyak.mutasi.size() << endl;
    }else{
        cout << "Belum ada nasabah yang memiliki mutasi." << endl;
    }
}

void cekHistoryMutasiNasabah(){
    cout << endl;
    int nomorRekening;
    cout << "Masukkan Nomor Rekening: ";
    cin >> nomorRekening;
    bool nasabahDitemukan = false;

    for (const auto &nasabah : nasabahs){
        if (nasabah.nomorRekening == nomorRekening){
            nasabahDitemukan = true;
            cout << "History Mutasi Rekening untuk Nasabah " << nasabah.nama << ":" << endl;
            for (const auto &mutasi : nasabah.mutasi){
                cout << "- " << mutasi << endl;
            }
            break;
        }
    }

    if (!nasabahDitemukan){
        cout << "Nasabah dengan nomor rekening tersebut tidak ditemukan." << endl;
    }
}

void tampilkanMenuNasabah(){
    cout << endl;
    cout << "========================" << endl;
    cout << "  Menu Nasabah" << endl;
    cout << "========================" << endl;
    cout << "1. Input Data Nasabah" << endl;
    cout << "2. Cek Saldo" << endl;
    cout << "3. Transfer" << endl;
    cout << "4. Cek Mutasi" << endl;
    cout << "5. Stor Tunai" << endl;
    cout << "6. Hapus History Transfer" << endl;
    cout << "7. Keluar" << endl;
    cout << "========================" << endl;
    cout << "Pilih menu (1-7): ";
}

void tampilkanMenuAdmin(){
    cout << endl;
    cout << "========================" << endl;
    cout << "  Menu Admin" << endl;
    cout << "========================" << endl;
    cout << "1. Cek Rekening Paling Banyak Mutasi" << endl;
    cout << "2. Cek History Mutasi Nasabah" << endl;
    cout << "3. Keluar" << endl;
    cout << "========================" << endl;
    cout << "Pilih menu (1-3): ";
}

bool login(){
    cout << endl;
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    for (const auto &pengguna : penggunas){
        if (pengguna.username == username && pengguna.password == password){
            return true;
        }
    }

    return false;
}

int main(){
    cout << endl;
    loadDataNasabah();
    // Tambahkan pengguna admin
    Pengguna admin;
    admin.username = "admin";
    admin.password = "admin123";
    admin.isAdmin = true;
    penggunas.push_back(admin);

    int pilihan;
    bool isAdmin = login();

    do{
        if (isAdmin){
            tampilkanMenuAdmin();
        }else{
            tampilkanMenuNasabah();
        }

        cin >> pilihan;

        if (isAdmin){
            switch (pilihan){
            case 1:
                cekRekeningPalingBanyakMutasi();
                break;
            case 2:
                cekHistoryMutasiNasabah();
                break;
            case 3:
                cout << "Keluar dari menu admin." << endl;
                isAdmin = false;
                break;
            default:
                cout << "Pilihan menu tidak valid." << endl;
                break;
            }
        }else{
            switch (pilihan){
            case 1:
                inputDataNasabah();
                break;
            case 2:
                cekSaldo();
                break;
            case 3:
                transfer();
                break;
            case 4:
                cekMutasi();
                break;
            case 5:
                stortunai();
                break;
            case 6:
                hapusHistoryTransfer();
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan menu tidak valid." << endl;
                break;
            }
        }
    } while (pilihan != 7);
    saveDataNasabah();

    return 0;
}
