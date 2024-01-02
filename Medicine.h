#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_MEDICINES = 100; // Adjust the size according to your needs


struct Medicine {
    int NDC;
    string name;
    int weight;
    string chemicalName;
};

Medicine medicines[MAX_MEDICINES] = {}; // Added declaration for medicines array
int medicineCount = 0; // Added declaration for medicineCount

// Function prototypes for Medicine entity
void medicineMenu();
void addMedicine();
void searchMedicine();
void viewMedicineRecord();
void deleteMedicineRecord();
void updateMedicineRecord();

void medicineMenu() {
    int choice;
    cout << "===== Medicine Record System =====\n";
    cout << "1. Add Medicine\n";
    cout << "2. Search Medicine\n";
    cout << "3. View Records\n";
    cout << "4. Delete Record\n";
    cout << "5. Update Record\n";
    cout << "6. Back to main\n";

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addMedicine();
            break;
        case 2:
            searchMedicine();
            break;
        case 3:
            viewMedicineRecord();
            break;
        case 4:
            deleteMedicineRecord();
            break;
        case 5:
            updateMedicineRecord();
            break;
        case 6:
            cout << "Returning to the main menu.\n";
          //  mainmenu();
            break;






        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

void addMedicine() {
    Medicine newMedicine;
    cout << "Enter the National Drug Code of the medicine: ";
    cin >> newMedicine.NDC;
    cout << "Enter the name of the medicine: ";
    cin.ignore();
    getline(cin, newMedicine.name);
    cout << "Enter the weight of the medicine in mg: ";
    cin >> newMedicine.weight;
    cout << "Enter the chemical name of the medicine: ";
    cin.ignore();
    getline(cin, newMedicine.chemicalName);

    if (medicineCount < MAX_MEDICINES) {
        medicines[medicineCount] = newMedicine;
        medicineCount++;

        ofstream fout("medicinereport.txt", ios::app);
        fout << newMedicine.NDC << setw(17) << newMedicine.name << setw(17) << newMedicine.weight << setw(17) << newMedicine.chemicalName << endl;
        fout.close();
        cout << "Medicine added successfully!\n";

    }
    else {
        cout << "Error: Medicines array is full.\n";
    }
}

void viewMedicineRecord() {
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
    cout << "NDC   \t" << "MEDICINE     \t" << "WEIGHT \t" << "CHEMICAL NAME" << endl;

    while (fin >> tempMedicine.NDC >> tempMedicine.name >> tempMedicine.weight >> tempMedicine.chemicalName) {
        cout << tempMedicine.NDC << "\t" << tempMedicine.name << "\t" << tempMedicine.weight << "\t" << tempMedicine.chemicalName << endl;
        if (fin.eof()) {
            cout << "Reached the end of the file." << endl;
        }
        else if (fin.fail()) {
            throw runtime_error("Error reading from the file. The file may contain incorrectly formatted data.");
        }
    }










    fin.close();

}


void searchMedicine() {
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
    int searchNDC;
    bool found = false;

    cout << "Enter the National Drug Code to search: ";
    cin >> searchNDC;

    while (fin >> tempMedicine.NDC >> tempMedicine.name >> tempMedicine.weight >> tempMedicine.chemicalName) {
        if (tempMedicine.NDC == searchNDC) {
            found = true;
            cout << "Record found:\n";
            cout << tempMedicine.NDC << "\t" << tempMedicine.name << "\t" << tempMedicine.weight << "\t" << tempMedicine.chemicalName << endl;
            break;
        }
    }

    if (!found) {
        cout << "Record not found for NDC: " << searchNDC << endl;
    }

    fin.close();

}


void updateMedicineRecord() {
    ifstream fin("medicinereport.txt");
    ofstream temp("temp.txt");

    int updateNDC;
    bool found = false;

    cout << "Enter the National Drug Code to update: ";
    cin >> updateNDC;

    Medicine tempMedicine;

    while (fin >> tempMedicine.NDC >> tempMedicine.name >> tempMedicine.weight >> tempMedicine.chemicalName) {
        if (tempMedicine.NDC == updateNDC) {
            found = true;
            cout << "Enter updated details:\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, tempMedicine.name);







            cout << "Weight (mg): ";
            cin >> tempMedicine.weight;
            cout << "Chemical Name: ";
            cin.ignore();
            getline(cin, tempMedicine.chemicalName);
        }
        temp << tempMedicine.NDC << setw(17) << tempMedicine.name << setw(17) << tempMedicine.weight << setw(17) << tempMedicine.chemicalName << endl;
    }

    cout << (found ? "Record updated successfully!\n" : "Record not found for NDC\n");


    fin.close();
    temp.close();

    remove("medicinereport.txt");
    rename("temp.txt", "medicinereport.txt");
}

void deleteMedicineRecord() {
    // Define file names for the medicine records and temporary file
    string filename = "medicinereport.txt";
    string tempFilename = "temp.txt";

    try {
        // Open input file stream to read from the medicine records file
        ifstream fin(filename);
        if (!fin) {
            // Throw an exception if there's an error opening the file
            throw runtime_error("Error opening file");
        }

        // Open output file stream to write to a temporary file
        ofstream temp(tempFilename);
        if (!temp) {
            // Throw an exception if there's an error creating the temporary file
            throw runtime_error("Error creating temporary file");
        }

        // Variables for user input and checking if a record is found
        int deleteNDC;
        bool found = false;

        // Prompt user for the National Drug Code (NDC) to delete
        cout << "Enter the National Drug Code to delete: ";
        cin >> deleteNDC;

        // Temporary Medicine object to store data read from the file
        Medicine tempMedicine;

        // Iterate through each record in the file
        while (fin >> tempMedicine.NDC >> tempMedicine.name >> tempMedicine.weight >> tempMedicine.chemicalName) {
            if (tempMedicine.NDC == deleteNDC) {
                // If the NDC matches, mark as found and skip writing to temporary file
                found = true;
                cout << "Record deleted successfully!\n";
                continue;
            }
            else {
                // Write the record to the temporary file if NDC doesn't match
                temp << tempMedicine.NDC << setw(17) << tempMedicine.name << setw(17) << tempMedicine.weight << setw(17) << tempMedicine.chemicalName << endl;
            }
        }

        // Check if the record was not found and inform the user
        if (!found) {
            cout << "Record not found for NDC: " << deleteNDC << endl;
        }

        // Close input and output files
        fin.close();
        temp.close();

        // Remove the original file
        if (remove(filename.c_str()) != 0) {
            throw runtime_error("Error removing the original file.");
        }

        // Rename the temporary file to the original filename
        if (rename(tempFilename.c_str(), filename.c_str()) != 0) {
            throw runtime_error("Error renaming temporary file.");
        }

    }
    catch (const runtime_error& e) {
        // Catch and display any runtime errors that occur
        cout << e.what() << endl;
    }
}



