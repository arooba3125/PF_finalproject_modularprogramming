#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Stock.h"
#include "Medicine.h"
#include "Delivery.h"

using namespace std;



void mainmenu() {
	cout << "*******MEDICAL STORE MANAGEMENT SYSTEM*******" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << endl;
	cout << "1. Medicine Record " << endl;
	cout << "2. Stock Record " << endl;
	cout << "3. Delivery Record " << endl;
	cout << "4. Exit" << endl;
	int choice;
	do {
		cout << "enter your choice" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			medicineMenu();
			break;
		case 2:
			stockMenu();
			break;

		case 3:
			deliveryMenu();
			break;

		case 4:
			return;
		default:
			cout << "enter valid choice";
		}
	} while (choice != 4);
}


int main() {
	mainmenu();

}

