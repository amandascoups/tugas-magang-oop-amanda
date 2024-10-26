#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Presensi {
private:
    int hadir;
    int izin;
    int alpa;
    string alasan;
    string bukti;

public:
    Presensi() : hadir(0), izin(0), alpa(0), alasan(""), bukti("") {}

    void tambahHadir() { hadir++; }
    void tambahIzin(const string& alasan, const string& bukti) {
        izin++;
        this->alasan = alasan;
        this->bukti = bukti;
    }
    void tambahAlpa() { alpa++; }

    void tampilkanPresensi() const {
        cout << "Presensi - Hadir: " << hadir << ", Izin: " << izin << ", Alpa: " << alpa << endl;
        if (izin > 0) {
            cout << "Alasan Izin: " << alasan << "\nBukti Izin: " << bukti << endl;
        }
    }
};

class UKM {
private:
    string nama;
    string jadwal;
    string materi;
    bool sertifikat;
    Presensi presensi;

public:
    UKM(string nama, string jadwal, string materi, bool sertifikat) 
        : nama(nama), jadwal(jadwal), materi(materi), sertifikat(sertifikat) {}

    string getNama() const { return nama; }

    void tampilkanInfo() const {
        cout << "Nama UKM: " << nama << "\nJadwal: " << jadwal 
             << "\nMateri: " << materi << endl; 
        if (sertifikat) {
            string pilihan;
            cout << "Unduh Sertifikat? (Ya/Tidak): ";
            cin >> pilihan;
            if (pilihan == "Ya" || pilihan == "ya") {
                cout << "Sertifikat sedang diunduh untuk " << nama << "...\n";
                cout << "Pengunduhan sertifikat dibatalkan.\n";
            }
        }
    }

    void tambahPresensi(const string& status, const string& alasan = "", const string& bukti = "") {
        if (status == "hadir") {
            presensi.tambahHadir();
        } else if (status == "izin") {
            presensi.tambahIzin(alasan, bukti);
        } else if (status == "alpa") {
            presensi.tambahAlpa();
        }
    }

    void tampilkanPresensi() const {
        presensi.tampilkanPresensi();
    }
};

class Mahasiswa {
private:
    string nama;
    string nrp;
    vector<UKM> daftarUKM;

public:
    Mahasiswa() : nama(""), nrp("") {}
    Mahasiswa(string nama, string nrp) : nama(nama), nrp(nrp) {}

    void setNama(const string& nama) { this->nama = nama; }
    string getNama() const { return nama; }
    void setNRP(const string& nrp) { this->nrp = nrp; }
    string getNRP() const { return nrp; }

    void tambahUKM(const UKM& ukm) {
        daftarUKM.push_back(ukm);
    }

    void tampilkanUKM() {
        cout << "Daftar UKM yang diikuti " << nama << " (" << nrp << "):\n";
        for (auto it = daftarUKM.begin(); it != daftarUKM.end();) {
            it->tampilkanInfo();
            it->tampilkanPresensi();
            cout << endl;

            string pilihan;
            cout << "Apakah Anda ingin keluar dari UKM " << it->getNama() << "? (Ya/Tidak): ";
            cin >> pilihan;
            if (pilihan == "Ya" || pilihan == "ya") {
                it = daftarUKM.erase(it);  
                cout << "Anda telah keluar dari UKM: " << it->getNama() << endl;
            } else {
                ++it;  
            }
        }
    }

    void ubahPresensi(const string& namaUKM, const string& status) {
        string alasan, bukti, kode;

        if (status == "hadir") {
            cout << "Kode presensi: ";
            cin >> kode;
            if (kode.length() != 6 || !all_of(kode.begin(), kode.end(), ::isdigit)) {
                cout << "Kode presensi harus 6 digit. Akses ditolak." << endl;
                return;
            }
        } else if (status == "izin") {
            cout << "Alasan izin: ";
            cin.ignore();
            getline(cin, alasan);
            cout << "Bukti izin: ";
            getline(cin, bukti);
        }

        for (auto &ukm : daftarUKM) {
            if (ukm.getNama() == namaUKM) {
                ukm.tambahPresensi(status, alasan, bukti);
                cout << "Presensi diperbarui untuk " << namaUKM << endl;
                return;
            }
        }
        cout << "UKM tidak ditemukan." << endl;
    }

    void hapusUKM(const string& namaUKM) {
        auto it = remove_if(daftarUKM.begin(), daftarUKM.end(),
                             [&namaUKM](const UKM& ukm) { return ukm.getNama() == namaUKM; });
        if (it != daftarUKM.end()) {
            daftarUKM.erase(it, daftarUKM.end());
            cout << "Anda telah keluar dari " << namaUKM << endl;
        } else {
            cout << "UKM tidak ditemukan dalam daftar.\n";
        }
    }
};

int main() {
    map<string, Mahasiswa> databaseMahasiswa;

    Mahasiswa amanda("Amanda Widya Pitaloka Hafizah", "5023241098");

    vector<UKM> daftarUKM = {
        UKM("UKM Basket", "Jumat 16:00 - 18:00", "Materi dasar basket", true),
        UKM("UKM Sepak Bola", "Selasa 18:00 - 20:00", "Materi dasar sepak bola", false),
        UKM("UKM Bridge", "Kamis 17:00 - 19:00", "Materi dasar bridge", false),
        UKM("ITS Badminton Club", "Rabu 19:00 - 21:00", "Materi dasar bulutangkis", true),
        UKM("UKM Tenis", "Sabtu 10:00 - 12:00", "Materi dasar tenis", true),
        UKM("UKM Billiard", "Minggu 14:00 - 16:00", "Materi dasar billiard", false),
        UKM("UKM Catur", "Senin 19:00 - 21:00", "Materi dasar catur", false),
        UKM("UKM Futsal", "Selasa 16:00 - 18:00", "Materi dasar futsal", true),
        UKM("UKM Softball", "Rabu 18:00 - 20:00", "Materi dasar softball", false),
        UKM("UKM Panahan", "Jumat 14:00 - 16:00", "Materi dasar panahan", true),
        UKM("UKM Flag Football", "Senin 17:00 - 19:00", "Materi dasar flag football", true),
        UKM("UKM Bola Voli", "Kamis 18:00 - 20:00", "Materi dasar voli", false),
        UKM("Technopreneurship Development Center", "Senin 09:00 - 11:00", "Materi technopreneurship", true),
        UKM("Kopma Dr Angka", "Selasa 10:00 - 12:00", "Materi koperasi", false),
        UKM("ITS MUN Club", "Kamis 15:00 - 17:00", "Materi Model United Nations", true),
        UKM("UKM LPM 1.0", "Rabu 16:00 - 18:00", "Materi LPM", true),
        UKM("ITS Foreign Language Society (IFLS)", "Jumat 18:00 - 20:00", "Materi bahasa asing", true),
        UKM("UKM Penalaran", "Sabtu 10:00 - 12:00", "Materi penalaran", true),
        UKM("Maritime Challenge", "Minggu 13:00 - 15:00", "Materi maritim", true),
        UKM("UKM Robotika", "Senin 17:00 - 19:00", "Materi dasar robotika", true),
        UKM("ITS Astronomy Club", "Selasa 19:00 - 21:00", "Materi astronomi", false),
        UKM("UKM PMR", "Rabu 18:00 - 20:00", "Materi PMR", true),
        UKM("UKM Resimen Mahasiswa", "Jumat 15:00 - 17:00", "Materi resimen mahasiswa", false),
        UKM("UKM Pramuka", "Kamis 10:00 - 12:00", "Materi pramuka", true),
        UKM("UKM PLH Siklus", "Minggu 10:00 - 12:00", "Materi lingkungan", true),
        UKM("UKM Muay Thai", "Senin 19:00 - 21:00", "Materi Muay Thai", true),
        UKM("UKM PSHT", "Rabu 16:00 - 18:00", "Materi PSHT", true),
        UKM("UKM Merpati Putih", "Kamis 17:00 - 19:00", "Materi Merpati Putih", true),
        UKM("UKM Shorinji Kempo", "Selasa 19:00 - 21:00", "Materi Shorinji Kempo", true),
        UKM("UKM Taekwondo", "Sabtu 08:00 - 10:00", "Materi Taekwondo", true)
    };

    amanda.tambahUKM(daftarUKM[19]); // UKM Robotik
    amanda.tambahUKM(daftarUKM[8]);  // UKM Softball
    amanda.tambahUKM(daftarUKM[0]);  // UKM Basket

    databaseMahasiswa[amanda.getNRP()] = amanda;

    string nama, nrp;

    cout << "=== Selamat Datang di UKM ITS ===\n";
    cout << "Nama : ";
    getline(cin, nama);
    if (nama.length() > 50) {
        cout << "Nama terlalu panjang. Maksimal 50 karakter." << endl;
        return 1;
    }

    cout << "NRP : ";
    getline(cin, nrp);
    if (nrp.length() > 10) {
        cout << "NRP terlalu panjang. Maksimal 10 karakter." << endl;
        return 1;
    }

    if (databaseMahasiswa.find(nrp) == databaseMahasiswa.end()) {
        Mahasiswa mahasiswaBaru(nama, nrp);
        string tambahUKM;

        do {
            cout << "Masukkan nama UKM yang ingin diikuti (ketik 'daftar' untuk selesai): ";
            getline(cin, tambahUKM);

            auto it = find_if(daftarUKM.begin(), daftarUKM.end(),
                [&tambahUKM](const UKM& ukm) { return ukm.getNama() == tambahUKM; });

            if (tambahUKM != "daftar") {
                if (it != daftarUKM.end()) {
                    mahasiswaBaru.tambahUKM(*it);
                } else {
                    cout << "UKM tidak ditemukan. Silakan coba lagi.\n";
                }
            }
        } while (tambahUKM != "daftar");

        databaseMahasiswa[nrp] = mahasiswaBaru;
        cout << "Mahasiswa baru berhasil didaftarkan!\n";
    }

    Mahasiswa &mahasiswa = databaseMahasiswa[nrp];

    int pilihan;
    do {
        cout << "\n=== Selamat Datang di UKM ITS ===\n";
        cout << "1. Lihat UKM\n2. Presensi\n3. Log Out\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        if (pilihan == 1) {
            mahasiswa.tampilkanUKM();
        } else if (pilihan == 2) {
            string namaUKM, status;

            cout << "Nama UKM: ";
            cin.ignore();
            getline(cin, namaUKM);
            cout << "Status presensi (hadir/izin/alpa): ";
            cin >> status;

            mahasiswa.ubahPresensi(namaUKM, status);
        } else if (pilihan == 3) {
            cout << "Log out dari program.\n";
        } else {
            cout << "Opsi tidak ditemukan.\n";
        }
    } while (pilihan != 3);

    return 0;
}
