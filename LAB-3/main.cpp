#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3]; 
    Page* next;
    Page* prev;
};

Page* head = NULL;
Page* tail = NULL;
Page* current = NULL;

void visit(string u, string t, int h, int m, int s) {
    Page* newPage = new Page;
    newPage->url = u;
    newPage->title = t;
    newPage->accessTime[0] = h;
    newPage->accessTime[1] = m;
    newPage->accessTime[2] = s;
    newPage->next = NULL;
    newPage->prev = NULL;

    if (head == NULL) {
        head = newPage;
        tail = newPage;
        current = newPage;
    } else {
        tail->next = newPage;
        newPage->prev = tail;
        tail = newPage;
        current = newPage; 
    }
    cout << "Sayfa eklendi." << endl;
}

void back() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
        cout << "Geri gidildi: " << current->title << endl;
    } else {
        cout << "Geri gidilemez. Ilk sayfadasiniz." << endl;
    }
}

void forward() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
        cout << "Ileri gidildi: " << current->title << endl;
    } else {
        cout << "Ileri gidilemez. Son sayfadasiniz." << endl;
    }
}

void deleteEntry() {
    if (current == NULL) {
        cout << "Gecmis bos." << endl;
        return;
    }

    Page* toDelete = current;

    if (toDelete->prev != NULL) {
        toDelete->prev->next = toDelete->next;
    } else {
        head = toDelete->next; 
    }

    if (toDelete->next != NULL) {
        toDelete->next->prev = toDelete->prev;
    } else {
        tail = toDelete->prev; 
    }

    if (toDelete->prev != NULL) {
        current = toDelete->prev;
    } else {
        current = toDelete->next;
    }

    delete toDelete;
    cout << "Mevcut sayfa silindi." << endl;
}

void display() {
    if (head == NULL) {
        cout << "Gecmis bos." << endl;
        return;
    }

    Page* temp = head;
    cout << "\n--- Tarayici Gecmisi ---" << endl;
    while (temp != NULL) {
        if (temp == current) {
            cout << "=> "; 
        } else {
            cout << "   ";
        }
        
        cout << temp->title << " (" << temp->url << ") - Saat: ";
        
        for (int i = 0; i < 3; i++) {
            cout << temp->accessTime[i];
            if (i < 2) cout << ":"; 
        }
        cout << endl;
        
        temp = temp->next;
    }
    cout << "------------------------\n" << endl;
}

void cleanup() {
    Page* temp = head;
    while (temp != NULL) {
        Page* nextNode = temp->next;
        delete temp; 
        temp = nextNode;
    }
    head = NULL;
    tail = NULL;
    current = NULL;
    cout << "Hafiza temizlendi. Program kapaniyor..." << endl;
}

int main() {
    string choice = "";
    string u, t;
    int h, m, s;

    while (choice != "EXIT") {
        cout << "\n1. Visit\n2. Back\n3. Forward\n4. Delete Entry\n5. Display\n6. EXIT\nSeciminiz (isim veya numara): ";
        cin >> choice;

        if (choice == "1" || choice == "Visit") {
            cout << "URL (Bosluksuz, ornek: google.com): ";
            cin >> u;
            cout << "Baslik (Bosluksuz, ornek: Google): ";
            cin >> t;
            cout << "Saat Dakika Saniye (Bosluk birakarak, ornek: 14 30 00): ";
            cin >> h >> m >> s;
            visit(u, t, h, m, s);
        }
        else if (choice == "2" || choice == "Back") {
            back();
        }
        else if (choice == "3" || choice == "Forward") {
            forward();
        }
        else if (choice == "4" || choice == "Delete") {
            deleteEntry();
        }
        else if (choice == "5" || choice == "Display") {
            display();
        }
        else if (choice == "6" || choice == "EXIT") {
            cleanup();
            break;
        }
        else {
            cout << "Gecersiz secim." << endl;
        }
    }
    return 0;
}