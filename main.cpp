#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struktur Data untuk Peminjam (Node)
struct Peminjam {
    string nama;
    string nim;
    string namaAlat;
    string tanggalPinjam;
    string kondisiAlat;
    
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
        if (daftarAlat.empty()) {
            cout << "Belum ada alat di inventaris.\n";
            return;
        }

        cout << "\n--- Daftar Alat ---\n";
        for (int i = 0; i < daftarAlat.size(); i++) {
            cout << i + 1 << ". " << daftarAlat[i].nama << (daftarAlat[i].tersedia ? " [Tersedia]" : " [Dipinjam]") << endl;
        }

        int pilihan;
        cout << "Pilih nomor alat: ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > daftarAlat.size() || !daftarAlat[pilihan - 1].tersedia) {
            cout << "Alat tidak tersedia atau pilihan salah.\n";
            return;
        }

        Peminjam* baru = new Peminjam();
        cin.ignore();
        cout << "Nama Peminjam: "; getline(cin, baru->nama);
        cout << "NIM: "; getline(cin, baru->nim);
        cout << "Tanggal Pinjam: "; getline(cin, baru->tanggalPinjam);
        cout << "Kondisi Alat saat ini: "; getline(cin, baru->kondisiAlat);
        
        baru->namaAlat = daftarAlat[pilihan - 1].nama;
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
    }

    // 3. Fitur Kembalikan Alat
    void kembalikanAlat() {
        string namaAlat;
        cout << "Masukkan nama alat yang dikembalikan: ";
        cin.ignore();
        getline(cin, namaAlat);

        for (auto &a : daftarAlat) {
            if (a.nama == namaAlat && !a.tersedia) {
                a.tersedia = true;
                cout << "Alat '" << namaAlat << "' telah tersedia kembali.\n";
                return;
            }
        }
        cout << "Alat tidak ditemukan atau sudah ada di lab.\n";
    }

    // 4. Fitur Tampilkan Riwayat (Traversal)
    void tampilkanRiwayat() {
        if (!head) {
            cout << "Belum ada riwayat peminjaman.\n";
            return;
        }
        Peminjam* temp = head;
        cout << "\n=== RIWAYAT PEMINJAMAN (Kronologis) ===\n";
        while (temp) {
            cout << "[" << temp->nama << " | " << temp->namaAlat << " | " << temp->kondisiAlat << "]\n";
            temp = temp->next;
        }
    }

    // 5. Fitur Lacak Peminjam (Audit Mode)
    void lacakPeminjam() {
        if (!head) return;
        string target;
        cout << "Masukkan nama peminjam yang ingin dilacak: ";
        cin.ignore();
        getline(cin, target);

        Peminjam* temp = head;
        while (temp) {
            if (temp->nama == target) {
                cout << "\n--- Hasil Pelacakan ---\n";
                cout << "Peminjam: " << temp->nama << " (" << temp->namaAlat << ")\n";
                
                if (temp->prev) 
                    cout << "Sebelumnya dipegang oleh: " << temp->prev->nama << " (Kondisi: " << temp->prev->kondisiAlat << ")\n";
                else 
                    cout << "Sebelumnya: (Peminjam Pertama)\n";

                if (temp->next)
                    cout << "Setelahnya dipegang oleh: " << temp->next->nama << "\n";
                else
                    cout << "Setelahnya: (Masih dipegang/Peminjam Terakhir)\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Data peminjam tidak ditemukan.\n";
    }

    // 6. Cek Peminjam Terakhir
    void cekPeminjamTerakhir() {
        if (tail) {
            cout << "Peminjam terakhir secara keseluruhan adalah: " << tail->nama 
                 << " meminjam " << tail->namaAlat << " (" << tail->kondisiAlat << ")\n";
        } else {
            cout << "Belum ada data.\n";
        }
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
