#include <iostream>
#include <string>
using namespace std;

void insertRow()
{
    bool validID, validstatus;
    string name, studentID, status;
    
    cout << "---------------------------" << endl;
    cout << "Insert New Attendance Row" << endl;
    cout << "---------------------------" << endl;

    cout << "Enter StudentID: " << endl;
    cin >> studentID;

    do {
        cout << "Enter StudentID: ";
        cin >> studentID;
        
        validID = true;
        for (int i = 0; i < studentID.length(); i++) {
            if (studentID[i] < '0' || studentID[i] > '9') {
                validID = false;
                break;
            }
        }
        
        if (!validID) {
            cout << "Error: Invalid INT value. Please enter a number." << endl;
        }
    } while (!validID);

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    do {
        cout << "Enter Status (Present: 1, Absent: 0): ";
        cin >> status;
        
        validstatus = true;
        if (status != "0" && status != "1") {
            cout << "Error: Invalid value. Please enter either '0' or '1'.";
            validstatus = false;
        }
        
        if (!validstatus) {
            cout << "Error: Invalid INT value. Please enter a number." << endl;
        }
    } while (!validstatus);

}

int main() {
    insertRow();
    return 0;
}