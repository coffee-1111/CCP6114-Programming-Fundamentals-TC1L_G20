#include <iostream>
#include <string>
using namespace std;

// These are the global variables from createSheet()
extern int numcolumn;                    // Number of columns
extern string column_name[10];          // Column names
extern string column_type[10];          // Column types (INT/TEXT)

// These are for storing the attendance data
extern string attendanceSheet[50][10];  // Data storage
extern int nextRow;                     // Current row counter

bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Make sure you have proper buffer clearing:
void insertRow()
{
    if (numcolumn == 0) {
        cout << "Error: Please create a sheet first!" << endl;
        return;
    }
    
    cout << "---------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "---------------------------\n";

    // Clear any leftover newline from previous operations
    cin.ignore(10000, '\n');
    
    string input;
    
    for (int col = 0; col < numcolumn; col++) {
        bool validInput = false;
        
        while (!validInput) {
            cout << "Enter " << column_name[col] << ": ";
            
            if (column_type[col] == "INT") {
                // For INT - use cin >>
                cin >> input;
                
                if (isNumber(input)) {
                    attendanceSheet[nextRow][col] = input;
                    validInput = true;
                } else {
                    cout << "Error: Must be a number. Please enter again." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            } 
            else if (column_type[col] == "TEXT") {
                // For TEXT - use getline
                getline(cin, input);
                
                if (!input.empty()) {
                    attendanceSheet[nextRow][col] = input;
                    validInput = true;
                } else {
                    cout << "Error: Cannot be empty. Please enter again." << endl;
                }
            }
        }
    }
    nextRow++;
    cout << "\nRow inserted successfully!" << endl;
}

int main() 
{
    insertRow();
    return 0;
}