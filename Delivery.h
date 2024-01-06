
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


using namespace std;

// Structure for Delivery
struct Delivery {
	int stock_id;
	int ndc;
	int amount_in_RS;
	int no_of_tablets;
};
void deliveryMenu();
void deliveryadd_record();
void deliveryview_record();
void deliverysearch_record();
bool isValidStockId(int stockId);
bool isValidNDC(int ndc);
void saveDeliveryRecord(Delivery delivery);


void deliveryMenu() {
	cout << "***Welcome to Delivery Records***" << endl;
	cout << "------------------------------" << endl;
	cout << "1. Add Delivery Record" << endl;
	cout << "2. View Delivery Record" << endl;
	cout << "3. Search Delivery Record" << endl;
	cout << "4. Back to Main Menu" << endl;
	int choice;
	do {
		cout << "enter your choice" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			deliveryadd_record();
			break;

		case 2:
			deliveryview_record();
			break;

		case 3:
			deliverysearch_record();
			break;

		case 4:
		break;

		default:
			cout << "enter valid choice";
		}
		
	} while (choice != 5);

}

void deliveryadd_record() {
	Delivery delivery;

	cout << "Add New Delivery Record" << endl;

	// Input Stock ID
	cout << "Enter the Stock ID: ";
	cin >> delivery.stock_id;

	// Check if the Stock ID is valid
	if (!isValidStockId(delivery.stock_id)) {
		cout << "Invalid Stock ID. Please add the corresponding stock details first.\n";
		return;
	}

	// Input NDC
	cout << "Enter the NDC of the Medicine: ";
	cin >> delivery.ndc;

	// Check if the NDC is valid
	if (!isValidNDC(delivery.ndc)) {
		cout << "Invalid NDC. Please add the corresponding medicine details first.\n";
		return;
	}

	// Input amount_in_RS and no_of_tablets
	cout << "Enter the Amount in RS: ";
	cin >> delivery.amount_in_RS;

	cout << "Enter the Number of Tablets: ";
	cin >> delivery.no_of_tablets;

	// Save the delivery record
	saveDeliveryRecord(delivery);

	cout << "Delivery record added successfully!\n";
}
void deliveryview_record() {
	cout << "View Records\n";
	// Implement viewing delivery records (if needed)
	ifstream fin("deliveryreport.txt");

	try {
		if (!fin.is_open()) {
			throw runtime_error("Error opening the file for reading.");
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	Delivery tempDelivery;
	cout << "Stock ID\tNDC\tAmount in RS\tNo. of Tablets\n";

	while (fin >> tempDelivery.stock_id >> tempDelivery.ndc >> tempDelivery.amount_in_RS >> tempDelivery.no_of_tablets) {
		cout << tempDelivery.stock_id << "\t\t" << tempDelivery.ndc << "\t" << tempDelivery.amount_in_RS << "\t\t" << tempDelivery.no_of_tablets << endl;
	}

	fin.close();
}

void deliverysearch_record() {
	cout << "Search Record\n";
	ifstream fin("deliveryreport.txt");

	try {
		if (!fin.is_open()) {
			throw runtime_error("Error opening the file for reading.");
		}
	}

	catch (const exception& e) {
		cout << e.what() << endl;
	}


	Delivery tempDelivery;
	int searchStockId;
	cout << "Enter the Stock ID to search: ";
	cin >> searchStockId;

	bool found = false;

	cout << "Stock ID\tNDC\tAmount in RS\tNo. of Tablets\n";

	while (fin >> tempDelivery.stock_id >> tempDelivery.ndc >> tempDelivery.amount_in_RS >> tempDelivery.no_of_tablets) {
		if (tempDelivery.stock_id == searchStockId) {
			found = true;
			cout << tempDelivery.stock_id << "\t\t" << tempDelivery.ndc << "\t" << tempDelivery.amount_in_RS << "\t\t" << tempDelivery.no_of_tablets << endl;
			break;
		}
	}

	if (!found) {
		cout << "Record not found for Stock ID: " << searchStockId << endl;
	}

	fin.close();
}

void saveDeliveryRecord(Delivery delivery) {
	// Save the delivery record to a file
	ofstream outFile("deliveryreport.txt", ios::app);
	outFile << delivery.stock_id << setw(17) << delivery.ndc << setw(17) << delivery.amount_in_RS << setw(17) << delivery.no_of_tablets << endl;
	outFile.close();
}
bool isValidStockId(int stockId) {
	ifstream fin("stockreport.txt");

	try {
		if (!fin.is_open()) {
			throw runtime_error("Error opening the file for reading.");
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	Stock tempStock;
	while (fin >> tempStock.stock_id >> tempStock.stock_number >> tempStock.stock_description >> tempStock.stock_datearrival >> tempStock.boxes >> tempStock.tabletsInBox) {
		if (tempStock.stock_id == stockId) {
			fin.close();
			return true;
		}
	}

	fin.close();
	return false;
}
bool isValidNDC(int ndc) {
	ifstream fin("medicinereport.txt");

	try {
		if (!fin.is_open()) {
			throw runtime_error("Error opening the file for reading.");
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	Medicine tempMedicine;

	while (fin >> tempMedicine.NDC >> tempMedicine.name >> tempMedicine.weight >> tempMedicine.chemicalName) {
		if (tempMedicine.NDC == ndc) {
			fin.close();
			return true;
		}
	}

	fin.close();
	return false;
}
