#include <iostream>
#include <limits> // used to clear the input cache
using namespace std;

//for testing
void createSheet() {
    cout << "   [System] CALL createSheet()... (Function executing)" << endl;
}

void insertRow() {
    cout << "   [System] CALL insertRow()... (Function executing)" << endl;
}

void viewCSV() {
    cout << "   [System] CALL viewCSV()... (Function executing)" << endl;
}

void mainMenu() {

    int choice;
    bool isSheetCreated = false;

    do {
        cout << "==============================" << endl;
        cout << " Student Attendance Tracker Menu " << endl;
        cout << "==============================" << endl;
        cout << "1. Create Attendance Sheet" << endl;
        cout << "2. Insert Attendance Row" << endl;
        cout << "3. View Attendance Sheet (CSV)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        //avoid infinite loops when user input char or string 
        if (cin.fail()) {
            cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean cache
            choice = 0; // set choice as invalid option
        }

        if (choice == 1) {
            createSheet(); 
            isSheetCreated = true; 
            cout << "   [System] Sheet created flag set to TRUE." << endl;
        }
        
        else if (choice == 2) {
            if (isSheetCreated == true) {
                insertRow();
            } else {
                cout << "Error: Please create a sheet first (Option 1)." << endl;
            }
        }

        else if (choice == 3) {
            if (isSheetCreated == true) {
                viewCSV();
            } else {
                cout << "Error: Please create a sheet first (Option 1)." << endl;
            }
        }

        else if (choice == 4) {
            cout << "Exiting program..." << endl;
        }

        else {
            cout << "Invalid option. Please enter 1 - 4." << endl;
        }

        cout << endl;

    } while (choice != 4);
}


int main() {
    mainMenu();
    return 0;
}

