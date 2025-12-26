// *********************************************************
// Program: TC1L_Group20_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT2L + TT3L
// Trimester: 2530
// Member_1: 252UC2439Z | Gan Kai Li Kelly | gan.kai.li1@student.mmu.edu.my | 0168229518
// Member_2: 252UC2457P | Ashton Shino Lim | ashton.shino.lim1@student.mmu.edu.my | 01110138115
// Member_3: 252UC2432F | Eryne Chuah Ee Wen | ERYNE.CHUAH.EE1@student.mmu.edu.my | 0163591686
// Member_4: 252UC242S4 | Lai Jia Han | lai.jia.han1@student.mmu.edu.my | 01110900316
// *********************************************************
// Task Distribution
// Member_1: main menu function
// Member_2: view csv function
// Member_3: insertRow function
// Member_4: create column function
// *********************************************************


#include <iostream>
#include <string>
#include <limits>
#include <cctype>

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

//for insertRow - check if the input only contains numbers
bool isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool onlyLetters(const string& s) {
    if (s.empty()) return false;
    for (char c : s){
        if (!isalpha(c) && c!= ' '){
            return false;
        }
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
        cout << "Enter column " << colNum << " type( INT or TEXT ): " << endl ;
        getline(cin, column_type[i]);

        for (int k = 0; k < column_type[i].length(); k++)  // let int / text become INT /TEXT
         {
           column_type[i][k] = toupper(column_type[i][k]);
         }


        while(column_type[i].empty() || (column_type[i] != "INT" && column_type[i] != "TEXT"))
        {
         cout << "Invalid column type! Please enter INT or TEXT only. " << endl;
         cout << "Enter column " << colNum << " type( INT or TEXT ): " << endl ;
         getline(cin, column_type[i]);


         for (int k = 0; k < column_type[i].length(); k++)
         {
           column_type[i][k] = toupper(column_type[i][k]);
         }
         
        }

        cout << "Column "<< colNum << " name :" << column_name[i] <<" (" << column_type[i]<< ") " << endl << endl;
        
        i = i + 1 ;
        colNum = colNum + 1;
     }
     

   cout << "Sheet Structure created successfully" << endl << endl ;

   cout << "============= Summary Columns ===============" << endl;
   int j = 0;

   while(j < numcolumn)
        {
          cout << " Column " << (j + 1) << " name: " << column_name[j] <<" (" << column_type[j]<< ") " << endl; /// column type also use this one to display
              
          j = j + 1;
        }

}

void insertRow()
{
    if (numcolumn == 0) {
        cout << "Error: Please create a sheet first!" << endl;
        return;
    }
    
    cout << "---------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "---------------------------\n";

    string input;
    
    
    for (int col = 0; col < numcolumn; col++) {
        bool validInput = false;
        
        while (!validInput) {
            // Check if column name is "Status" to show special prompt
            if (column_name[col] == "Status" || column_name[col] == "status") {
                cout << "Enter Status (Present: 1, Absent: 0): ";
            } else {
                cout << "Enter " << column_name[col] << ": ";
            }
            
            if (column_type[col] == "INT") {
                // For INT columns - read the whole line then validate
                getline(cin, input);
                
                // Special validation for Status column
                if (column_name[col] == "Status" || column_name[col] == "status") {
                    if (isNumber(input) && (input == "0" || input == "1")) {
                        attendanceSheet[nextRow][col] = input;
                        validInput = true;
                    } else {
                        cout << "Error: Please enter 0 (Absent) or 1 (Present) only." << endl;
                    }
                } 
                else {
                    // Normal INT validation for other columns
                    if (isNumber(input)) {
                        attendanceSheet[nextRow][col] = input;
                        validInput = true;
                    } else {
                        cout << "Error: Must be a number. Please enter again." << endl;
                    }
                }
            } 
            else if (column_type[col] == "TEXT") {
                getline(cin, input);
                
                // Special validation for TEXT Status column
                if (column_name[col] == "Status" || column_name[col] == "status") {
                    if (input == "0" || input == "1") {
                        attendanceSheet[nextRow][col] = input;
                        validInput = true;
                    } else {
                        cout << "Error: Please enter 0 (Absent) or 1 (Present) only." << endl;
                    }
                }
                else {
                    // Normal TEXT validation for other columns
                    if (input.empty()) {
                        cout << "Error: Cannot be empty. Please enter again." << endl;
                    } else if (!onlyLetters(input)) {
                        cout << "Error: Must contain only letters (a-z, A-Z) and spaces. Please enter again." << endl;
                    } else {
                        attendanceSheet[nextRow][col] = input;
                        validInput = true;
                    }
                }
            }
        }
    }
    
    nextRow++;
    cout << "\nRow inserted successfully!" << endl;
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

                // clear input '2' after enter
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                string continueStr = "y"; 
                
                while (continueStr == "y" || continueStr == "Y") {
                    
                    insertRow(); 
                    
                    while (true) {
                        cout << "\nDo you want to add another row? (y/n): ";
                        getline(cin, continueStr); // 使用 getline 读取整行输入

                        // only pass when 'y','Y','n' or 'N'
                        if (continueStr.length() == 1 && 
                           (continueStr[0] == 'y' || continueStr[0] == 'Y' || 
                            continueStr[0] == 'n' || continueStr[0] == 'N')) {
                            break; 
                        } 
                        else {
                            cout << "Invalid input. Please enter exactly 'y' or 'n'." << endl;
                        }
                    }
                    
                    // convert all user input to lowercase for easier processing in the outer while loop
                    if (continueStr.length() == 1) continueStr[0] = tolower(continueStr[0]);
                    
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