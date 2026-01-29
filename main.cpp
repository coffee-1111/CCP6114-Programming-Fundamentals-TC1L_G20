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
// Member_1:
// Member_2:
// Member_3: 
// Member_4: 
// *********************************************************


#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <fstream>
#include <sstream>

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

//3.for database
string schoolTermName = "Not Set";
string currentFileName = ""; // To track the currently open file


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
// File I/O & Database Functions
//------------------------

// function one: read attendance data from csv file
bool readFromFile(string filename)
{
    ifstream file(filename);

    if (!file)
    {   
        cout << "Reading attendance data from file..." << endl;
        cout << "Error: Unable to open file." << endl;
        return false;
    }

    string line;
    nextRow = 0;
    numcolumn = 0;

    // Read header as columns
    if (getline(file, line))
    {
        stringstream header(line);
        string col;

        while (getline(header, col, ',') && numcolumn < 10)
        {
            // Remove leading space/BOM if any
            if (!col.empty() && (col[0] == ' ' || !isalnum(col[0])))
            {
                 // Simple cleanup for spaces, advanced BOM handling omitted for simplicity
                 if(col[0] == ' ') col.erase(0, 1);
            }

            column_name[numcolumn] = col;
            // Default type to TEXT when loading from file (since CSV doesn't store types)
            column_type[numcolumn] = "TEXT"; 
            
            // Auto-detect Status column for validation later
            if(col == "Status" || col == "status") column_type[numcolumn] = "INT"; // Usually status is 0/1

            numcolumn++;
        }
    }

    // Read data rows
    while (getline(file, line) && nextRow < 50)
    {
        stringstream ss(line);
        string value;
        int col = 0;

        while (getline(ss, value, ',') && col < numcolumn)
        {
            if (!value.empty() && value[0] == ' ')
                value.erase(0, 1);

            attendanceSheet[nextRow][col] = value;
            col++;
        }
        nextRow++;
    }

    file.close();
    currentFileName = filename; // Remember which file we are working on
    cout << "Successfully loaded: " << filename << endl;
    return true;
}

// function 2 : write data into the csv file
void writeToFile(string filename)
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Reading attendance data from file..." << endl;
        cout << "Error: Unable to write to file." << endl;
        return;
    }

    // Write column headers
    for (int i = 0; i < numcolumn; i++)
    {
        file << column_name[i];
        if (i < numcolumn - 1)
            file << ", ";
    }
    file << endl;

    // Write rows
    for (int i = 0; i < nextRow; i++)
    {
        for (int j = 0; j < numcolumn; j++)
        {
            file << attendanceSheet[i][j];
            if (j < numcolumn - 1)
                file << ", ";
        }
        file << endl;
    }

    file.close();
    cout << "Output saved as: " << filename << endl;

    ofstream list("file_list.txt",ios::app);
    list << filename << endl;
    list.close();
    cout << "File saved and added to database list." << endl;
}

void saveTerm(string name)
{
  ofstream file("config.txt");
  if (file)
  {
    file << name ;
    file.close();
  }
}

string loadTerm()
{
  ifstream file("config.txt");
  string name = "";
  if (file)
  {
    getline(file,name);
    file.close();
  }
  return name;
}

bool displayExistingFiles()
{
  ifstream file("file_list.txt");
  string fName;
  bool found = false;
  while (getline(file,fName))
  {
    if (!fName.empty())
    {
      cout << "-" <<fName <<endl;
      found = true;
    }
  }
  file.close();
  return found;
}

//------------------------
//Core Functions
//------------------------

void createSheet()
{
   string sheet_name;

   cout << "Enter attendence sheet name:" << endl;
   getline(cin >> ws, sheet_name) ;

   while(sheet_name.empty()) ///user just enter and doesn't input anything
   {
      cout << "Sheet name cannot be empty! Please enter again." << endl;
      cout << "Enter attendence sheet name:" << endl;
      getline(cin, sheet_name) ;
   }

   cout << "\nAttendance sheet " << sheet_name << " created successfully" << endl << endl;

   numcolumn = getValidColumn(); ///get column from function
   
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
        cout << "Enter column  " << colNum << " type( INT or TEXT ): " << endl ;
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
     
   nextRow = 0;

   cout << "Sheet Structure created successfully" << endl << endl ;
   string filename = sheet_name + ".csv";
   writeToFile(filename);

   cout << "============= Summary Columns ===============" << endl;
   int j = 0;

   while(j < numcolumn)
        {
          cout << " Column " << (j + 1) << " name: " << column_name[j] << " (" << column_type [j] << ")" <<endl; /// column type also use this one to display
              
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
        cout << "No sheet created/loaded." << endl;
        return;
    }

    // Printing column headers
    for (int i = 0; i < numcolumn; i++)
    {
        cout << column_name[i];
        if (i < numcolumn - 1)
            cout << ", ";
    }
    cout << endl;

    if (nextRow == 0)
    {
        cout << "(Sheet is empty)" << endl;
        return;
    }

    // Printing rows
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

void count_Rows(){
    if (numcolumn == 0) 
    {
        cout << "Error: Please create a sheet first." << endl;
        return;
    }

    int count = 0;

    for (int i = 0; i < nextRow; i++) 
    {
        if (!attendanceSheet[i][0].empty()) 
        {
            count++;
        }
    }

    cout << "--------------------" << endl;
    cout << "Count Rows" << endl;
    cout << "--------------------" << endl;
    cout << "Number of rows: " << count << endl;

}

void updateRow()
{
    int studentID, targetRow, row, col, nameColumn;

    if (numcolumn == 0 || nextRow == 0)
    {
        cout << "Error: No data available to update!";
        return;
    }
    cout << "--------------------------------" << endl;
    cout << "Update Attendance Row" << endl;
    cout << "--------------------------------" << endl;

    viewCSV();

    cout << "Enter StudentID to update: ";
    cin >> studentID;

    targetRow = -1;
    row = 0;

    while(row < nextRow)
    {
        col = 0;
        while (col < numcolumn)
        {
            if (stoi(attendanceSheet[row][col]) == studentID)
            {
                targetRow = row;
                break;
            }
            col++;
        }
        
        if (targetRow != -1)
        {
            break;
        }
        row++;
    }

    if (targetRow == -1)
    {
        cout << "Error: StudentID not found";
        return;
    }

    cout << "Choose one to update";
    cout << "1. Name";
    cout << "2. Status";
    cout << "-1. Exit";

    int choice = 0;

    while (choice!= 1 && choice != 2 && choice != -1)
    {
        cout << "Enter choice (1, 2, -1): ";
        cin >> choice;

        if (!isNumber(to_string(choice)))
        {
            cout << "Error: Please enter a number";
            choice = 0;
            continue;
        }
    }

    if (choice == -1)
    {
        cout << "Update cancelled";
        return;
    }

    if (choice == 1)
    {
        nameColumn = -1;
        col = 0;

        while (col < numcolumn)
        {
            if (column_name[col] == "Name" || column_name[col] == "name")
            {
                nameColumn = col;
                break;
            }
            col++;
        }

        if (nameColumn == -1)
        {
            cout << "Error: Name column not found";
            return;
        }

        string newname;
        cout << "Enter new name: ";
        cin >> newname;

        while (newname == " " || !onlyLetters(newname))
        {
            if (newname == " "){
                cout << "Error: Name cannot be empty";
            }else{
                cout << "Error: Name must contain only letters and spaces";
            }
            
            cout << "Enter new name: ";
            cin >> newname;
        }

        attendanceSheet[targetRow][nameColumn] = newname;
        cout << "Name updated successfully";
    }else if (choice == 2)
    {
        int statusColumn = -1;
        col = 0;

        while (col < numcolumn)
        {
            if (column_name[col] == "Status" || column_name[col] == "status")
            {
                statusColumn = col;
                break;
            }
            col++;
        }

        if (statusColumn == -1)
        {
            cout << "Error: Status column not found";
            return;
        }

        string newStatus;
        cout << "Enter new Status (0=Absent, 1=Present): ";
        cin >> newStatus;

        while (newStatus != "0" && newStatus != "1")
        {
            cout << "Error: Please enter 0 (Absent) or 1 (Present) only.";
            cout << "Enter new Status: ";
            cin >> newStatus;
        }

        attendanceSheet[targetRow][statusColumn] = newStatus;
        cout << "Status updated successfully";
    }

    cout << "Updated sheet: ";
    viewCSV();
}

void deleteRow()
{
    int studentID, targetRow, row, col, nameColumn;

    if (numcolumn == 0 || nextRow == 0)
    {
        cout << "Error: No data available to delete!";
        return;
    }
    cout << "--------------------------------";
    cout << "Delete Attendance Row";
    cout << "--------------------------------";

    viewCSV();

    cout << "Enter StudentID to delete: ";
    cin >> studentID;

    targetRow = -1;
    row = 0;
    while (row < nextRow)
    {
        col = 0;
        while (col < numcolumn)
        {
            if (stoi(attendanceSheet[row][col]) == studentID)
            {
                targetRow = row;
                break;
            }
            col++;
        }
        if (targetRow != -1)
        {
            break;
        }
        row++;

        if (targetRow == -1)
        {
            cout << "Error: StudentID not found";
            return;
        }

        row = targetRow;
        while (row < nextRow-1)
        {
            col = 0;
            while (col < numcolumn)
            {
                attendanceSheet[row][col] = attendanceSheet[row+1][col];
                col++;
            }
            row++;
        }

        nextRow = -1;

        cout << "Row deleted successfully";
        cout << "Updated sheet: ";
        viewCSV();
    }
}

//------------------------
// Initialization Functions
//------------------------

void setupDatabase()
{
  cout << " Create School Term (Database) " << endl;

  //loading Term 
  string saved_term = loadTerm();
  if (saved_term != "" && saved_term !=" ")
  {
    schoolTermName = saved_term;
    cout << "---------------------------------------------------------------"<< endl;
    cout << "Welcome back! Database " << schoolTermName << " loaded automatically" << endl;
    cout << "---------------------------------------------------------------"<< endl;
  }
  else
  {
    cout << "No saved database found. Initializing..." << endl;
    cout << "Enter School Term Name: ";
    getline(cin >> ws, schoolTermName);
    while(schoolTermName.empty())
    {
      cout << "Invalid term name. Please enter again: ";
      getline(cin >> ws, schoolTermName);
    }
    saveTerm(schoolTermName);
    cout << "Database " << schoolTermName <<" created and loaded." << endl << endl;
  }
}

void fileLoadDatabase()
{
  //display exist files
  cout <<"Current Available Attendance Sheets "<< endl;
  cout << "------------------------------------"<< endl;
  bool hasFiles = displayExistingFiles();
  if (!hasFiles)
  {
    cout << "(No previous sheets found)"<< endl << endl;
    cout << "Please enter -1 to go to menu to create new sheet"<< endl<< endl;
  }

  // load filename
  string filename;
  cout << endl << "Enter filename to load(or -1 to skip to Menu):" << endl;
  cin >> filename;

  if (filename == "-1")
  {
    cout << "Skipping to Main Menu..."<< endl;
  }
  else
  {
    bool file_found = readFromFile(filename);
    while (!file_found)
    {    
      cout <<"Please enter again (or -1 to skip to Menu):" << endl;
      cin >> filename;

      if (filename == "-1")
      {
       cout << "Skipping to Main Menu..." << endl;
       break;
       
      }
      
      file_found = readFromFile(filename);
    
    }

    if (file_found)
    {
      
      cout << "---------------------------------------"<< endl;
      cout << "Current Attendance Sheet - "<< schoolTermName << endl;
      viewCSV();
      cout << "Going to Main Menu..." << endl;
    }
  }

}

void schoolTerm() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter School Term Name: ";
    getline(cin, schoolTermName);
    cout << "Term Name updated to: " << schoolTermName << endl;
}

//------------------------
//Main Menu
//------------------------
void mainMenu() {

    int choice;
    bool isSheetCreated = false;

    // 1. Initial Setup
    setupDatabase();
    
    // 2. Load existing Data
    fileLoadDatabase();

    if (numcolumn > 0) {
        isSheetCreated = true;
    }

    do {
        cout << "==============================================" << endl;
        cout << "      STUDENT ATTENDANCE TRACKER - MILESTONE 2" << endl;
        cout << "      Current Term: " << schoolTermName << endl;
        cout << "==============================================" << endl;
        cout << "1. Create School Term" << endl;
        cout << "2. Create Attendance Sheet" << endl;
        cout << "3. Insert Attendance Row" << endl;
        cout << "4. Update Attendance Row" << endl;
        cout << "5. Delete Attendance Row" << endl;
        cout << "6. View Attendance Sheet (CSV)" << endl;
        cout << "7. Count Rows" << endl;
        cout << "8. Save & Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        //avoid infinite loops when user input char or string 
        if (cin.fail()) {
            cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean cache
            choice = 0; // set choice as invalid option
        }

        if (choice == 1) {
            if (schoolTermName != "Not Set") {
                cout << "Error: School Term has already been created (" << schoolTermName << ")." << endl;
            } 
            else {
                schoolTerm();
            }
        }

        else if (choice == 2) {
            if (isSheetCreated) {
                cout << "Error: Attendance Sheet already exists." << endl;
            } 
            else {
                createSheet();
                if (numcolumn > 0) { 
                    isSheetCreated = true; 
                }
            }
        }
        
        else if (choice == 3) {
            if (isSheetCreated == true) {

                // clear input '2' after enter
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                string continueStr = "y"; 
                
                while (continueStr == "y" || continueStr == "Y") {
                    
                    insertRow(); 
                    
                    while (true) {
                        cout << "\nDo you want to add another row? (y/n): ";
                        getline(cin, continueStr); 

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
                cout << "Error: Please create a sheet first (Option 2)." << endl;
            }
        }

        else if (choice == 4) {
            if (isSheetCreated) {
                updateRow();
            } else {
                cout << "Error: Please create a sheet first." << endl;
            }
        }

        else if (choice == 5) {
            if (isSheetCreated) {
                deleteRow();
            } else {
                cout << "Error: Please create a sheet first." << endl;
            }
        }

        else if (choice == 6) {
            viewCSV();   
        }

        else if (choice == 7) {
            count_Rows();
        }    

        else if (choice == 8) {
            if(isSheetCreated && !currentFileName.empty()) {
                writeToFile(currentFileName);
            } else if (isSheetCreated) {
                // Should not happen if createSheet logic is correct, but fail-safe
                cout << "Enter filename to save: ";
                cin >> currentFileName;
                writeToFile(currentFileName + ".csv");
            }
            cout << "Exiting program..." << endl;
        }

        else {
            cout << "Invalid option. Please enter 1 - 8." << endl;
        }

        cout << endl;

    } while (choice != 8);
}


int main() {
    mainMenu();
    return 0;
}