#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STOCK = 100; // Adjust the size according to your needs

struct Stock {
    int stock_id;
    string stock_number;
    string stock_description;
    string stock_datearrival;
    int boxes;
    int tabletsInBox;
};

Stock stocks[MAX_STOCK] = {};
int stockCount = 0;

// Function prototypes for Stock entity
void stockMenu();
void addStock();
void viewStock();
void searchStock(int searchId);
void updateStock(int updateId);


void stockMenu() {
    int choice;
    cout << "===== Stock Management System =====\n";
    cout << "1. Add Stock\n";
    cout << "2. View Stock\n";
    cout << "3. Search Stock\n";
    cout << "4. Update Stock\n";
    cout << "5. Back to main\n";

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStock();
            break;
        case 2:
            viewStock();
            break;
        case 3:
            int searchId;
            cout << "Enter the Stock ID to search: ";
            cin >> searchId;
            searchStock(searchId);
            break;
        case 4:
            int updateId;
            cout << "Enter the Stock ID to update: ";
            cin >> updateId;
            updateStock(updateId);
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void addStock() {
    Stock newStock;

    cout << "Enter the Stock ID: ";
    cin >> newStock.stock_id;

    cout << "Enter the Stock Number: ";
    cin >> newStock.stock_number;

    cout << "Enter the Stock Description: ";
    cin >> newStock.stock_description;

    cout << "Enter the Stock Arrival Date (YYYY-MM-DD): ";
    cin >> newStock.stock_datearrival;

    cout << "Enter the number of boxes arrived in stock: ";
    cin >> newStock.boxes;

    cout << "Enter the number of tablets in one box: ";
    cin >> newStock.tabletsInBox;

    if (stockCount < MAX_STOCK) {
        stocks[stockCount] = newStock;
        stockCount++;

        ofstream outFile("stockreport.txt", ios::app);
        outFile << newStock.stock_id << setw(17) << newStock.stock_number << setw(17) << newStock.stock_description
            << setw(17) << newStock.stock_datearrival << setw(17) << newStock.boxes << setw(17) << newStock.tabletsInBox << endl;
        outFile.close();
        cout << "Stock added successfully and saved to file.\n";

    }
    else {
        cout << "Error: Stock array is full.\n";
    }
}

void viewStock() {
    try {
        ifstream fin("stockreport.txt");
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
    ifstream fin("stockreport.txt");

    Stock tempStock;
    cout << "ID\t" << "Number\t" << "Description\t" << "Arrival Date\t" << "BOXES\t" << "TABLETS" << endl;

    while (fin >> tempStock.stock_id >> tempStock.stock_number >> tempStock.stock_description
        >> tempStock.stock_datearrival >> tempStock.boxes >> tempStock.tabletsInBox) {








        cout << tempStock.stock_id << "\t" << tempStock.stock_number << "\t" << tempStock.stock_description << "   \t"
            << tempStock.stock_datearrival << "\t" << tempStock.boxes << "\t" << tempStock.tabletsInBox << endl;
        if (fin.eof()) {
            cout << "Reached the end of the file." << endl;
        }
        else if (fin.fail()) {
            cout << "Error reading from the file.The file may contain incorrectly formatted data." << endl;
        }
    }


    fin.close();

}

void searchStock(int searchId) {
    try {
        ifstream fin("stockreport.txt");
        if (!fin.is_open()) {
            throw runtime_error("Error opening the file for reading.");
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
    ifstream fin("stockreport.txt");

    Stock tempStock;
    bool found = false;

    while (fin >> tempStock.stock_id >> tempStock.stock_number >> tempStock.stock_description
        >> tempStock.stock_datearrival >> tempStock.boxes >> tempStock.tabletsInBox) {
        if (tempStock.stock_id == searchId) {
            found = true;
            cout << "Record found:\n";
            cout << "ID: " << tempStock.stock_id << "\nNumber: " << tempStock.stock_number << "\nDescription: "
                << tempStock.stock_description << "\nArrival Date: " << tempStock.stock_datearrival
                << "\nBoxes: " << tempStock.boxes << "\nTablets in Box: " << tempStock.tabletsInBox << endl;
            break;
        }
    }

    if (!found) {
        cout << "Record not found for ID: " << searchId << endl;
    }

    fin.close();

}


void updateStock(int updateId) {
    ifstream fin("stockreport.txt");
    ofstream temp("tempstock.txt");
    bool found = false;

    Stock tempStock;









    while (fin >> tempStock.stock_id >> tempStock.stock_number >> tempStock.stock_description
        >> tempStock.stock_datearrival >> tempStock.boxes >> tempStock.tabletsInBox) {
        if (tempStock.stock_id == updateId) {
            found = true;
            cout << "Enter updated details:\n";

            cout << "Enter the Stock Number: ";
            cin >> tempStock.stock_number;

            cout << "Enter the Stock Description: ";
            cin >> tempStock.stock_description;

            cout << "Enter the Stock Arrival Date (YYYY-MM-DD): ";
            cin >> tempStock.stock_datearrival;

            cout << "Enter the number of boxes arrived in stock: ";
            cin >> tempStock.boxes;

            cout << "Enter the number of tablets in one box: ";
            cin >> tempStock.tabletsInBox;
        }
        temp << tempStock.stock_id << setw(17) << tempStock.stock_number << setw(17) << tempStock.stock_description
            << setw(17) << tempStock.stock_datearrival << setw(17) << tempStock.boxes << setw(17) << tempStock.tabletsInBox << endl;
    }

    if (!found) {
        cout << "Record not found for ID: " << updateId << endl;
    }
    else {
        cout << "Record updated successfully!\n";
    }

    fin.close();
    temp.close();

    remove("stockreport.txt");
    rename("tempstock.txt", "stockreport.txt");
}





