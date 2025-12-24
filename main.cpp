#include <iostream>
#include <string>
#include <limits>

using namespace std;

//------------------------
//Global Variables
//-------------------------

//1.for createSheet
int numcolumn = 0;
string column_name[10];
string column_type[10];

//2.for insertRow
string attendanceSheet[50][10];   
int nextRow = 0;


//-------------------------
//Support Functions
//--------------------------

//for insertRow
bool isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

//for Sheet_create
int getValidColumn()
{
   int numcolumn ; 
   cout << "Define number of columns (max 10) : " << endl;
   cin  >> numcolumn;


   while (cin.fail() || numcolumn < 1 || numcolumn > 10 )  /// cin.fail() become true when enter letters as the input is invalid
     {
      cin.clear();  /// reset fail state so cin can read again
      cin.ignore(1000, '\n');   /// ignore up to 1000 character n stop ignore when newline is found

      cout << "\nNumber of columns is invalid. Please enter again.(1-10) " << endl;
      cout << "Define number of columns (max 10) : " << endl;
      cin  >> numcolumn ;

     }
   
     cin.ignore(1000, '\n'); 
     return numcolumn;
}

//------------------------
//Core Functions
//------------------------

void createSheet()
{
   string sheet_name;

   cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ensures that 'getline' does not skip the input for the sheet name

   cout << "Enter attendence sheet name:" << endl;
   getline(cin, sheet_name) ;

   while(sheet_name.empty()) ///user just enter and doesn't input anything
   {
      cout << "Sheet name cannot be empty! Please enter again." << endl;
      cout << "Enter attendence sheet name:" << endl;
      getline(cin, sheet_name) ;
   }

   cout << "\nAttendance sheet " << sheet_name << " created successfully" << endl << endl;

   numcolumn = getValidColumn(); ///get column from function

   column_name[10] ;
   column_type[10] ;
  

   int i = 0; 
   int colNum = 1;

  
   while(i < numcolumn)
     {
        cout << "Enter column " << colNum << " name: " << endl ;
        getline(cin, column_name[i]);

        while(column_name[i].empty())
        {
         cout << "Column name connot be empty! Please enter again. " << endl;
         cout << "Enter column " << colNum << " name: " << endl ;
         getline(cin, column_name[i]);
         
        }

        // For column type （ INT/ TEXT）
        //
        //

        cout << "Column "<< colNum << " name :" << column_name[i] << endl << endl;
        
        i = i + 1 ;
        colNum = colNum + 1;
     }
     

   cout << "Sheet Structure created successfully" << endl << endl ;

   cout << "============= Summary Columns ===============" << endl;
   int j = 0;

   while(j < numcolumn)
        {
          cout << " Column " << (j + 1) << " name: " << column_name[j] << endl; /// column type also use this one to display
              
          j = j + 1;
        }

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

    attendanceSheet[nextRow][0] = studentID;
    attendanceSheet[nextRow][1] = name;
    attendanceSheet[nextRow][2] = status;
    nextRow++;

    cout << "Row inserted successfully!" << endl;
}

void viewCSV()
{
  cout << "-------------------------------------------" <<endl;
  cout << "View Attendance Sheet (CSV Mode)" << endl;
  cout << "-------------------------------------------" <<endl;
    if (numcolumn == 0)
    {
        cout << "No sheet created." << endl;
        return;
    }

    if (nextRow == 0)
    {
        cout << "Sheet is empty." << endl;
        return;
    }
  //printing column
    for (int i = 0; i < numcolumn; i++)
    {
        cout << column_name[i];
        if (i < numcolumn - 1)
            cout << ", ";
    }
    cout << endl;
  //printing rows
    for (int i = 0; i < nextRow; i++)
    {
        for (int j = 0; j < numcolumn; j++)
        {
            cout << attendanceSheet[i][j];
            if (j < numcolumn - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

//------------------------
//Main Menu
//------------------------
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
        }
        
        else if (choice == 2) {
            if (isSheetCreated == true) {
                char continueInput = 'y';
                
                while (continueInput == 'y' || continueInput == 'Y') {
                    
                    insertRow(); 
                    
                    cout << "\nDo you want to add another row? (y/n): ";
                    cin >> continueInput;
                    
                    cout << endl; 
                }
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