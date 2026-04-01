#include <iostream>
#include <string>
using namespace std;
struct MoneyBundle { string serialNumber; string currencyType; int billCounts[3]; };
struct MoneyNode { MoneyBundle data; MoneyNode* next; };
struct Customer { string customerName; string transactionType; };
const int CAPACITY = 5;
void receiveMoney(MoneyNode*& top) {
	MoneyBundle b;
	cout << "Enter serial number: ";
	cin >> b.serialNumber;
	cout << "Enter currency type (TL/USD/etc.): ";
	cin >> b.currencyType;
	cout << "Enter count of 100 bills: ";
	cin >> b.billCounts[0];
	cout << "Enter count of 50 bills: ";
	cin >> b.billCounts[1];
	cout << "Enter count of 20 bills: ";
	cin >> b.billCounts[2];
	MoneyNode* newNode = new MoneyNode;
	newNode->data = b;
	newNode->next = top;
	top = newNode;
	cout << "Money bundle received and pushed to safe.\n";
}
void newCustomer(Customer q[], int& rear, int& count) {
	if (count == CAPACITY) { cout << "Queue is full (capacity 5). Customer cannot be added.\n"; return; }
	Customer c;
	cout << "Enter customer name: ";
	getline(cin >> ws, c.customerName);
	cout << "Enter transaction type (Withdraw/Deposit): ";
	getline(cin, c.transactionType);
	rear = (rear + 1) % CAPACITY;
	q[rear] = c;
	count++;
	cout << "Customer added to queue.\n";
}
void processTransaction(MoneyNode*& top, Customer q[], int& front, int& count) {
	if (count == 0) { cout << "No customer in queue.\n"; return; }
	if (top == nullptr) { cout << "Safe has no money bundle. Cannot process transaction.\n"; return; }
	Customer served = q[front];
	front = (front + 1) % CAPACITY;
	count--;
	cout << "Serving customer: " << served.customerName << " (" << served.transactionType << ")\n";
	cout << "Using top bundle: Serial " << top->data.serialNumber << ", Currency " << top->data.currencyType << "\n";
	MoneyNode* temp = top;
	top = top->next;
	delete temp;
	cout << "Transaction completed. Customer dequeued and top money bundle popped.\n";
}
void displaySystem(MoneyNode* top, Customer q[], int front, int count) {
	cout << "\n===== SYSTEM STATUS =====\n";
	if (top == nullptr) cout << "Safe is empty.\n";
	else {
		cout << "Money bundles in safe (top to bottom):\n";
		int i = 1;
		MoneyNode* cur = top;
		while (cur != nullptr) {
			cout << i << ") Serial: " << cur->data.serialNumber
				 << ", Currency: " << cur->data.currencyType
				 << ", Bills[100,50,20]: ["
				 << cur->data.billCounts[0] << ", "
				 << cur->data.billCounts[1] << ", "
				 << cur->data.billCounts[2] << "]\n";
			cur = cur->next;
			i++;
		}
	}
	cout << "-------------------------\n";
	if (count == 0) cout << "No customers waiting.\n";
	else {
		cout << "Customers in queue (front to rear):\n";
		for (int i = 0; i < count; i++) {
			int idx = (front + i) % CAPACITY;
			cout << (i + 1) << ") Name: " << q[idx].customerName
				 << ", Transaction: " << q[idx].transactionType << "\n";
		}
	}
	cout << "=========================\n";
}
void clearStack(MoneyNode*& top) {
	while (top != nullptr) {
		MoneyNode* temp = top;
		top = top->next;
		delete temp;
	}
}
int main() {
	MoneyNode* safeTop = nullptr;
	Customer queue[CAPACITY];
	int front = 0;
	int rear = -1;
	int count = 0;
	int choice;
	do {
		cout << "\n=== Bank Branch Management System ===\n";
		cout << "1. Receive Money (Push)\n";
		cout << "2. New Customer (Enqueue)\n";
		cout << "3. Process Transaction (Pop & Dequeue)\n";
		cout << "4. Display\n";
		cout << "0. Exit\n";
		cout << "Choose: ";
		cin >> choice;
		switch (choice) {
			case 1: receiveMoney(safeTop); break;
			case 2: newCustomer(queue, rear, count); break;
			case 3: processTransaction(safeTop, queue, front, count); break;
			case 4: displaySystem(safeTop, queue, front, count); break;
			case 0: cout << "Exiting...\n"; break;
			default: cout << "Invalid choice. Try again.\n";
		}
	} while (choice != 0);
	clearStack(safeTop);
	return 0;
}