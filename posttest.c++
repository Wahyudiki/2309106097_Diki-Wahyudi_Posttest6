#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Task {
    string nama;
    string deskripsi;
    bool selesai;
    int id;  // Unique ID for each task
};

class DaftarTugas {
private:
    stack<Task> stackTugas;
    queue<Task> queueTugas;
    vector<Task> allTasks; // Store all tasks for easier access
    int taskIdCounter = 0;  // Counter for task IDs

    // Function to get valid input from user
    string getValidInput(const string& prompt) {
        string input;
        cout << prompt;
        getline(cin, input);
        return input;
    }

    int getValidChoice(int min, int max) {
        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail() || choice < min || choice > max) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Pilihan tidak valid. Silakan coba lagi: ";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
                break;
            }
        }
        return choice;
    }

public:
    void tambahTugasStack() {
        Task tugasBaru;
        tugasBaru.nama = getValidInput("Masukkan nama tugas: ");
        tugasBaru.deskripsi = getValidInput("Masukkan deskripsi tugas: ");
        tugasBaru.selesai = false;
        tugasBaru.id = ++taskIdCounter;  // Assign unique ID
        
        stackTugas.push(tugasBaru);
        allTasks.push_back(tugasBaru); // Add to allTasks for easier management
        cout << "Tugas berhasil ditambahkan ke Stack dengan ID: " << tugasBaru.id << endl;
    }

    void tambahTugasQueue() {
        Task tugasBaru;
        tugasBaru.nama = getValidInput("Masukkan nama tugas: ");
        tugasBaru.deskripsi = getValidInput("Masukkan deskripsi tugas: ");
        tugasBaru.selesai = false;
        tugasBaru.id = ++taskIdCounter;  // Assign unique ID
        
        queueTugas.push(tugasBaru);
        allTasks.push_back(tugasBaru); // Add to allTasks for easier management
        cout << "Tugas berhasil ditambahkan ke Queue dengan ID: " << tugasBaru.id << endl;
    }

    void tampilkanTugasStack() {
        if (stackTugas.empty()) {
            cout << "Stack kosong." << endl;
            return;
        }
        
        cout << "Daftar Tugas di Stack:" << endl;
        stack<Task> tempStack = stackTugas; // Create a temporary stack to display tasks
        while (!tempStack.empty()) {
            Task t = tempStack.top();
            cout << "ID: " << t.id << ", Nama: " << t.nama << ", Deskripsi: " << t.deskripsi << endl;
            tempStack.pop();
        }
    }

    void tampilkanTugasQueue() {
        if (queueTugas.empty()) {
            cout << "Queue kosong." << endl;
            return;
        }

        cout << "Daftar Tugas di Queue:" << endl;
        queue<Task> tempQueue = queueTugas; // Create a temporary queue to display tasks
        while (!tempQueue.empty()) {
            Task t = tempQueue.front();
            cout << "ID: " << t.id << ", Nama: " << t.nama << ", Deskripsi: " << t.deskripsi << endl;
            tempQueue.pop();
        }
    }

    void hapusTugasStack() {
        if (stackTugas.empty()) {
            cout << "Tidak ada tugas untuk dihapus dari Stack." << endl;
            return;
        }
        
        Task removedTask = stackTugas.top();
        stackTugas.pop();
        cout << "Tugas dengan ID: " << removedTask.id << " telah dihapus dari Stack." << endl;
    }

    void hapusTugasQueue() {
        if (queueTugas.empty()) {
            cout << "Tidak ada tugas untuk dihapus dari Queue." << endl;
            return;
        }

        Task removedTask = queueTugas.front();
        queueTugas.pop();
        cout << "Tugas dengan ID: " << removedTask.id << " telah dihapus dari Queue." << endl;
    }

    void sortTasks() {
        sort(allTasks.begin(), allTasks.end(), [](const Task& a, const Task& b) { return a.id < b.id; });
    }

    void cariTugasString() {
        if (allTasks.empty()) {
            cout << "Tidak ada tugas untuk dicari." << endl;
            return;
        }

        string pattern = getValidInput("Masukkan nama tugas yang dicari: ");
        
        vector<int> foundIndices;

        for (int i = 0; i < allTasks.size(); i++) {
            if (allTasks[i].nama.find(pattern) != string::npos) { // Simple substring search
                foundIndices.push_back(i);
            }
        }

        if (foundIndices.empty()) {
            cout << "Tidak ditemukan tugas dengan nama tersebut." << endl;
            return;
        }

        cout << "\nHasil pencarian:" << endl;
        for (int idx : foundIndices) {
            cout << "Ditemukan: ID: " << allTasks[idx].id 
                 << ", Nama: " << allTasks[idx].nama 
                 << ", Deskripsi: " << allTasks[idx].deskripsi 
                 << endl;
        }
    }

    void cariTugasId() {
       if (allTasks.empty()) {
           cout << "Tidak ada tugas untuk dicari."<<endl; 
           return; 
       } 

       int searchId; 
       cout<<"Masukkan ID tugas yang dicari: "; 
       cin>>searchId; 

       auto it = find_if(allTasks.begin(), allTasks.end(), [searchId](const Task& t) { return t.id == searchId; }); 

       if(it != allTasks.end()) { 
           cout<<"Ditemukan: ID: "<<it->id<<", Nama: "<<it->nama<<", Deskripsi: "<<it->deskripsi<<endl; 
       } else { 
           cout<<"Tidak ditemukan dengan ID tersebut."<<endl; 
       } 
   }
};

int main() {
    DaftarTugas daftarTugas;
    int pilihan;

    do {
       cout<<"\nMenu Manajemen Tugas dengan Stack dan Queue"<<endl; 
       cout<<"1. Tambah Tugas ke Stack"<<endl; 
       cout<<"2. Tambah Tugas ke Queue"<<endl; 
       cout<<"3. Tampilkan Tugas dari Stack"<<endl; 
       cout<<"4. Tampilkan Tugas dari Queue"<<endl; 
       cout<<"5. Hapus Tugas dari Stack"<<endl; 
       cout<<"6. Hapus Tugas dari Queue"<<endl; 
       cout<<"7. Cari Tugas berdasarkan Nama"<<endl; 
       cout<<"8. Cari Tugas berdasarkan ID"<<endl; 
       cout<<"9. Keluar"<<endl;

       pilihan = daftarTugas.getValidChoice(1, 9);

       switch (pilihan) { 
           case 1:
               daftarTugas.tambahTugasStack(); break; 
           case 2:
               daftarTugas.tambahTugasQueue(); break; 
           case 3:
               daftarTugas.tampilkanTugasStack(); break; 
           case 4:
               daftarTugas.tampilkanTugasQueue(); break; 
           case 5:
               daftarTugas.hapusTugasStack(); break; 
           case 6:
               daftarTugas.hapusTugasQueue(); break; 
           case 7:
               daftarTugas.cariTugasString(); break; 
           case 8:
               daftarTugas.cariTugasId(); break; 
           case 9:
               cout<<"Terima kasih pren"<<endl; break; 
       } 
   } while (pilihan != 9);

   return 0; 
}