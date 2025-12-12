#include <iostream>
#include <string>
using namespace std;

// goes through the input to make sure it's purely integers, no mixture of anything 
bool isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void insertRow()
{
    string idInput;
    int studentID;
    int status;
    string name;

    cout << "---------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "---------------------------\n";

    while (true) {
        cout << "Enter StudentID: ";
        cin >> idInput;

        //using isNumber to check if idInput has only digits
        if (isNumber(idInput)) {
            studentID = stoi(idInput); //converts string to int
            break;
        }

        cout << "Error: Invalid INT value. Please enter a number." << endl;
    }

    cin.ignore(10000, '\n'); // clear leftover newline

    //gets input for name
    cout << "Enter name: ";
    getline(cin, name);

    //check if status input is 0 or 1 only
    while (true) {
        cout << "Enter Status (Present: 1, Absent: 0): ";
        cin >> idInput;

        if (idInput == "0" || idInput == "1") {
            status = stoi(idInput);
            break;
        }

        cout << "Error: Invalid value. Please enter either 0 or 1." << endl;
    }
}

int main() {
    insertRow();
    return 0;
}
