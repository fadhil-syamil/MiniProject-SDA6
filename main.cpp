#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struktur Data untuk Peminjam (Node)
struct Peminjam {
    string nama;
    string nim;
    string ruangan;
    string namaAlat;
    string kondisi;
    int jam, tgl, bln, thn;
    bool masihDipinjam; // Status untuk fitur No 4 & 5
    
    Peminjam* next;
    Peminjam* prev;
};

// Struktur Data untuk Alat
struct Alat {
    string nama;
    bool tersedia;
};

class SimulatorPeminjaman {
private:
    Peminjam* head;
    Peminjam* tail;
    vector<Alat> daftarAlat;

    // Fungsi Pembantu untuk Navigasi (Fitur No 6)
    void kembaliKeMenu() {
        cout << "\n------------------------------------------\n";
        cout << "Tekan Enter untuk kembali ke menu utama...";
        cin.ignore();
        cin.get();
    }

public:
    SimulatorPeminjaman() {
        head = nullptr;
        tail = nullptr;
    }

    // 1. Fitur Tambah Data Alat
    void tambahAlat(string nama) {
        daftarAlat.push_back({nama, true});
        cout << "Alat '" << nama << "' berhasil ditambahkan ke inventaris.\n";
    }

    // 2. Fitur Pinjam Alat (Insert Tail)
    void pinjamAlat() {
        system("cls");
        if (daftarAlat.empty()) {
            cout << "Belum ada alat di inventaris.\n";
            kembaliKeMenu();
            return;
        }

        cout << "\n=== FORM PEMINJAMAN ALAT (JAM KERJA 07:00 - 18:00) ===\n";
        for (int i = 0; i < daftarAlat.size(); i++) {
            cout << i + 1 << ". " << daftarAlat[i].nama << (daftarAlat[i].tersedia ? " [Tersedia]" : " [Dipinjam]") << endl;
        }

        int pilihan, j, t, b, th;
        cout << "Pilih nomor alat: ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > daftarAlat.size() || !daftarAlat[pilihan - 1].tersedia) {
            cout << "Alat tidak tersedia atau pilihan salah.\n";
            kembaliKeMenu();
            return;
        }

        cout << "Masukkan Jam (7-18): "; cin >> j;
        cout << "Masukkan Tanggal (1-31): "; cin >> t;
        cout << "Masukkan Bulan (1-12): "; cin >> b;
        cout << "Masukkan Tahun (Min. 2026): "; cin >> th;

        // VAlidasi Waktu & Tahun (Fitur No 1 & 2)
        if (th < 2026 || j < 7 || j > 18) {
            cout << "\n[ERROR]Waktu atau tahun tidak valid!\n";
            kembaliKeMenu();
            return;
        }

        Peminjam* baru = new Peminjam();
        cin.ignore();
        cout << "Nama Peminjam  : "; getline(cin, baru->nama);
        cout << "NIM            : "; getline(cin, baru->nim);
        cout << "Ruangan        : "; getline(cin, baru->ruangan);
        cout << "Kondisi Alat saat ini: "; getline(cin, baru->kondisi);
        
        baru->namaAlat = daftarAlat[pilihan - 1].nama;
        baru->jam = j; baru->tgl = t; baru->bln = b; baru->thn = th;
        baru->masihDipinjam = true;
        baru->next = nullptr;
        baru->prev = nullptr;

        // Logika Double Linked List (Insert Tail)
        if (head == nullptr) {
            head = tail = baru;
        } else {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        }

        daftarAlat[pilihan - 1].tersedia = false;
        cout << "Peminjaman berhasil dicatat!\n";
        kembaliKeMenu();
    }

    // 3. Fitur Kembalikan Alat
    void kembalikanAlat() {
        system("cls");
        string namaAlat;
        cout << "=== PENGEMBALIAN ALAT ===\n";
        cout << "Masukkan nama alat yang dikembalikan: ";
        cin.ignore();
        getline(cin, namaAlat);

        for (auto &a : daftarAlat) {
            if (a.nama == namaAlat && !a.tersedia) {
                a.tersedia = true;
                // Update status di riwayat (Fitur No 5)
                Peminjam* temp = head;
                while (temp) {
                    if (temp->namaAlat == namaAlat) temp->masihDipinjam = false;
                    temp = temp->next;
                }
                cout << "Alat '" << namaAlat << "' telah tersedia kembali.\n";
                return;
            }
        }
        cout << "Alat tidak ditemukan atau sudah ada di lab.\n";
        kembaliKeMenu();
    }

    // 4. Fitur Tampilkan Riwayat (Traversal)
    void tampilkanRiwayat() {
        system("cls");
        if (!head) {
            cout << "Belum ada riwayat peminjaman.\n";
            return;
        } else {
        Peminjam* temp = head;
        cout << "\n=== RIWAYAT PEMINJAMAN (Kronologis) ===\n";
        while (temp) {
            cout << "Nama     : " << temp->nama << " (" << temp->nim << ")\n";
            cout << "Ruangan  : " << temp->ruangan << "\n";
            cout << "Alat     : " << temp->namaAlat << "\n";
            cout << "Kondisi  : " << temp->kondisi << "\n";
            cout << "Waktu    : " << temp->tgl << "/" << temp->bln << "/" << temp->thn << " | Jam " << temp->jam << ":00\n";
            cout << "Status   : " << (temp->masihDipinjam ? "Dipinjam" : "Sudah Dikembalikan") << "\n";
            cout << "------------------------------------------\n";
            temp = temp->next;
        }
    }
    kembaliKeMenu();
    }

    // 5. Fitur Lacak Peminjam (Audit Mode)
    void lacakPeminjam() {
        system("cls");
        string target;
        cout << "Masukkan nama peminjam yang ingin dilacak: ";
        cin.ignore();
        getline(cin, target);

        Peminjam* temp = head;
        bool ketemu = false;
        while (temp) {
            if (temp->nama == target && temp->masihDipinjam) {
                cout << "\n[DATA DITEMUKAN]\n";
                cout << "Nama     : " << temp->nama << " \n";
                cout << "NIM      : " << temp->nim << "\n";
                cout << "ruangan  : " << temp->ruangan << "\n";
                ketemu = true;
                
            }
            temp = temp->next;
            }
            
        if (!ketemu) {
            cout << "Data peminjam tidak ditemukan.\n";
        }
        
    }

    // 6. Cek Peminjam Terakhir
    void cekPeminjamTerakhir() {
        system("cls");
        cout << "=== CEK PEMINJAM TERAKHIR ===\n";
        if (tail) {
            cout << "Peminjam Terakhir: " << tail->nama << "\n";
            cout << "NIM              : " << tail->nim << "\n";
            cout << "Alat             : " << tail->namaAlat << "\n";
            cout << "Status           : " << (tail->masihDipinjam ? "Masih Membawa Alat" : "Sudah Mengembalikan") << "\n";
        } else {
            cout << "Belum ada data peminjaman.\n";
        }
        kembaliKeMenu();
    }
};

int main() {
    SimulatorPeminjaman sim;
    int pilihan;

    do {
        cout << "\n==============================\n";
        cout << " SIMULATOR PEMINJAMAN ALAT \n";
        cout << "==============================\n";
        cout << "1. Tambah Data Alat\n";
        cout << "2. Pinjam Alat\n";
        cout << "3. Kembalikan Alat\n";
        cout << "4. Tampilkan Riwayat\n";
        cout << "5. Lacak Peminjam (Audit)\n";
        cout << "6. Cek Peminjam Terakhir\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string n; cout << "Nama Alat: "; cin.ignore(); getline(cin, n);
                sim.tambahAlat(n); break;
            }
            case 2: sim.pinjamAlat(); break;
            case 3: sim.kembalikanAlat(); break;
            case 4: sim.tampilkanRiwayat(); break;
            case 5: sim.lacakPeminjam(); break;
            case 6: sim.cekPeminjamTerakhir(); break;
        }
    } while (pilihan != 0);

    return 0;
}