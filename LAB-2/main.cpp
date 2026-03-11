#include <iostream>
#include <string>
using namespace std;

struct Node {
    string sarkiadi;
    Node* next;
};

Node* head = NULL; 

void sarkiekle(string title) {
    Node* newNode = new Node;
    newNode->sarkiadi = title;
    newNode->next = head;
    head = newNode;
}

void sarkiara(string title) {
    Node* gecici = head;
    bool found = false; 
    while (gecici != NULL) {
        if (gecici->sarkiadi == title) {
            found = true;
            break;
        }
        gecici = gecici->next;
    }
    if (found) {
        cout << title << " listede bulundu!" << endl;
    } else {
        cout << title << " listede yok." << endl;
    }
}

void ekran() {
    if (head == NULL) {
        cout << "Calma listesi bos." << endl;
        return;
    }
    
    Node* gecici = head;
    int count = 1;
    
    cout << "\n Calma listesi " << endl;
    while (gecici != NULL) {
        cout << count << ". " << gecici->sarkiadi << endl;
        gecici = gecici->next;
        count++; 
    }
    cout << endl;
}

int main() {
    int secim = 0;
    string baslik;
    while (secim != 4) {
        cout << "1. Add\n2. Search\n3. List\n4. Exit\nSeciminiz: ";
        cin >> secim;
        if (secim == 1) {
            cout << "Eklenecek sarki adi: ";
            cin.ignore(); 
            getline(cin, baslik); 
            sarkiekle(baslik);
            cout << "Sarki basa eklendi.\n" << endl;
        } 
        else if (secim == 2) {
            cout << "Aranacak sarki adi: ";
            cin.ignore();
            getline(cin, baslik);
            sarkiara(baslik);
            cout << endl;
        } 
        else if (secim == 3) {
            ekran();
        } 
        else if (secim == 4) {
            cout << "Programdan cikiliyor..." << endl;
        } 
        else {
            cout << "Gecersiz secim. Tekrar deneyin.\n" << endl;
        }
    }
    return 0;
}


