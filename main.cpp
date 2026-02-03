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
// Member_1: Main menu, count rows function
// Member_2: Reading from file, writing to file, screen output
// Member_3: Update attendance rows, delete attendance rows & view updated sheet		
// Member_4: Create school term (database) & view term name
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
bool isSheetCreated = false;

//-------------------------
//Support Functions
//--------------------------

//for insertRow - check if the input only contains numbers
bool isNumber(const string& s) {
    if (s.empty()) return false; //prevent empty input
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

// to convert string to lowercase
string toLowercase(const string& str)
{
    string lowerStr = str;
    for (char &c : lowerStr)
    {
        c = tolower(c);
    }
    return lowerStr;
}

string normalize(const string& s) {
    string result;
    for (char c : s) {
        if (c != ' ' && c != '_') {
            result += tolower(c);
        }
    }
    return result;
}

int findColumnByName(string search) {
    search = normalize(search);

    for (int i = 0; i < numcolumn; i++) {
        if (normalize(column_name[i]) == search) {
            return i;
        }
    }
    return -1;
}

bool isDuplicateStudentID(int col, const string& input) {
    int nameCol = findColumnByName("name");

    for (int row = 0; row < nextRow; row++) {
        if (attendanceSheet[row][col] == input) {
            cout << "Error: StudentID " << input << " already exists for student: ";
            if (nameCol != -1) {
                cout << attendanceSheet[row][nameCol];
            }
            cout << endl;
            return true;
        }
    }
    return false;
}

bool assignIfNotDuplicate(int col, const string& input, int studentIDColumn, int nextRow) {
    if (col == studentIDColumn && isDuplicateStudentID(col, input)) {
        cout << "Please enter a different StudentID" << endl;
        return false; // don’t assign, duplicate
    }
    attendanceSheet[nextRow][col] = input;
    return true;
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
            
           string lowerCol = toLowercase(col);

if (lowerCol == "status") {
    column_type[numcolumn] = "INT";   // Status must be 0 or 1
}
else if (lowerCol == "name") {
    column_type[numcolumn] = "TEXT";  // Name is text (validated later)
}
else if (lowerCol == "studentid" || lowerCol == "id") {
    column_type[numcolumn] = "TEXT";  // StudentID treated as string
}
else {
    column_type[numcolumn] = "TEXT";  // Default
}

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
    isSheetCreated = true;
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

    ifstream checkFile("file_list.txt");
    string existingName;
    bool alreadyExists = false;

    while(getline(checkFile,existingName))
      {
        if (existingName == filename)
        {
          alreadyExists = true;
          break;
        }
      }
    checkFile.close();

    if (!alreadyExists)
    {
      ofstream list("file_list.txt",ios :: app);
      list << filename << endl;
      list.close();
    }

    cout << "File saved." << endl;
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

   cout << "Enter attendence sheet name to save as file (use _ to represent space):" << endl;
   getline(cin >> ws, sheet_name) ;

   while(sheet_name.empty()) ///user just enter and doesn't input anything
   {
      cout << "Sheet name cannot be empty! Please enter again." << endl;
      cout << "Enter attendence sheet name to save as file (use _ to represent space):" << endl;
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
   currentFileName = sheet_name + ".csv";
   isSheetCreated = true;
   writeToFile(currentFileName);

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
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "---------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "---------------------------\n";

    string input;

    // Find the StudentID column
    int studentIDColumn = findColumnByName("studentid");
    if (studentIDColumn == -1) {
        studentIDColumn = findColumnByName("id"); // fallback
    }

    for (int col = 0; col < numcolumn; col++) {
        bool validInput = false;

        while (!validInput) {
            string colNameLower = toLowercase(column_name[col]);
            if (colNameLower == "status") {
                cout << "Enter Status (Present: 1, Absent: 0): ";
            } else {
                cout << "Enter " << column_name[col] << ": ";
            }

            getline(cin, input);

            // Handle Status column
            if (colNameLower == "status") {
                if (input == "0" || input == "1") {
                    attendanceSheet[nextRow][col] = input;
                    validInput = true;
                } else {
                    cout << "Error: Please enter 0 (Absent) or 1 (Present) only." << endl;
                }
                continue;
            }

            // Handle StudentID column as string
            if (col == studentIDColumn) {
                if (input.empty()) {
                    cout << "Error: StudentID cannot be empty." << endl;
                    continue;
                }

                // Check for duplicates
                bool isDuplicate = false;
                int nameCol = findColumnByName("name");
                for (int row = 0; row < nextRow; row++) {
                    if (attendanceSheet[row][col] == input) {
                        isDuplicate = true;
                        cout << "Error: StudentID " << input << " already exists for student: ";
                        if (nameCol != -1) cout << attendanceSheet[row][nameCol];
                        cout << endl;
                        break;
                    }
                }

                if (isDuplicate) {
                    cout << "Please enter a different StudentID" << endl;
                } else {
                    attendanceSheet[nextRow][col] = input;
                    validInput = true;
                }
                continue;
            }

            // INT column (not StudentID)
            if (column_type[col] == "INT") {
                if (isNumber(input)) {
                    attendanceSheet[nextRow][col] = input;
                    validInput = true;
                } else {
                    cout << "Error: Must be a number. Please enter again." << endl;
                }
            }
            // TEXT column (not StudentID)
            else if (column_type[col] == "TEXT") {
                if (input.empty()) {
                    cout << "Error: Cannot be empty. Please enter again." << endl;
                    continue;
                }
                if (colNameLower == "name" && !onlyLetters(input)) {
                    cout << "Error: Name must contain only letters and spaces." << endl;
                    continue;
                }
                attendanceSheet[nextRow][col] = input;
                validInput = true;
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
    if (numcolumn == 0 || nextRow == 0) {
        cout << "Error: No data available to update!" << endl;
        return;
    }

    viewCSV();

    cout << "--------------------------------" << endl;
    cout << "Update Attendance Row" << endl;
    cout << "--------------------------------" << endl;

    string studentIDStr;
    cout << "Enter StudentID to update: ";
    cin >> studentIDStr;

    int studentIDColumn = findColumnByName("studentid");
    if (studentIDColumn == -1) studentIDColumn = findColumnByName("id");
    if (studentIDColumn == -1) {
        cout << "Error: StudentID column not found!" << endl;
        return;
    }

    int targetRow = -1;
    for (int row = 0; row < nextRow; row++) {
        if (attendanceSheet[row][studentIDColumn] == studentIDStr) {
            targetRow = row;
            break;
        }
    }

    if (targetRow == -1) {
        cout << "Error: StudentID " << studentIDStr << " not found!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // Let user choose what to update
    cout << "Choose one to update" << endl;
    cout << "1. Name" << endl;
    cout << "2. Status" << endl;
    cout << "-1. Exit" << endl;

    int choice = 0;
    while (choice != 1 && choice != 2 && choice != -1) {
        cout << "Enter choice (1, 2, -1): ";
        if (!(cin >> choice)) {
            cout << "Error: Please enter a valid number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
    }

    if (choice == -1) {
        cout << "Update cancelled" << endl;
        return;
    }

    if (choice == 1) {
        int nameColumn = findColumnByName("name");
        if (nameColumn == -1) {
            cout << "Error: Name column not found!" << endl;
            return;
        }

        cin.ignore();
        string newName;
        cout << "Current Name: " << attendanceSheet[targetRow][nameColumn] << endl;
        cout << "Enter new name: ";
        getline(cin, newName);

        while (newName.empty() || !onlyLetters(newName)) {
            cout << "Error: Name must contain only letters and spaces." << endl;
            cout << "Enter new name: ";
            getline(cin, newName);
        }

        string oldName = attendanceSheet[targetRow][nameColumn];
        attendanceSheet[targetRow][nameColumn] = newName;
        cout << "Name updated successfully from '" << oldName << "' to '" << newName << "'" << endl;
    }
    else if (choice == 2) {
        int statusColumn = findColumnByName("status");
        if (statusColumn == -1) {
            cout << "Error: Status column not found!" << endl;
            return;
        }

        string currentStatus = attendanceSheet[targetRow][statusColumn];
        string currentStatusText = (currentStatus == "1") ? "Present" :
                                   (currentStatus == "0") ? "Absent" :
                                   currentStatus;

        string newStatus;
        cout << "Current Status: " << currentStatusText << " (" << currentStatus << ")" << endl;
        cout << "Enter new Status (0=Absent, 1=Present): ";
        cin >> newStatus;

        while (newStatus != "0" && newStatus != "1") {
            cout << "Error: Please enter 0 (Absent) or 1 (Present) only." << endl;
            cout << "Enter new Status: ";
            cin >> newStatus;
        }

        string newStatusText = (newStatus == "1") ? "Present" : "Absent";
        attendanceSheet[targetRow][statusColumn] = newStatus;
        cout << "Status updated successfully from '" << currentStatusText << "' (" << currentStatus
             << ") to '" << newStatusText << "' (" << newStatus << ")" << endl;
    }

    cout << "\nUpdated sheet: " << endl;
    viewCSV();
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void deleteRow()
{
    if (numcolumn == 0 || nextRow == 0)
    {
        cout << "Error: No data available to delete!" << endl;
        cin.get();
        return;
    }

    viewCSV();

    cout << "--------------------------------" << endl;
    cout << "Delete Attendance Row" << endl;
    cout << "--------------------------------" << endl;

    // Find StudentID column
    int studentIDColumn = findColumnByName("studentid");
    if (studentIDColumn == -1) studentIDColumn = findColumnByName("id");
    if (studentIDColumn == -1) {
        cout << "Error: Could not find StudentID column!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cin.ignore();
    string studentID;
    cout << "Enter StudentID to delete (or -1 to cancel): ";
    getline(cin, studentID);

    if (studentID == "-1") {
        cout << "Deletion cancelled." << endl;
        return;
    }

    int targetRow = -1;
    for (int row = 0; row < nextRow; row++) {
        if (attendanceSheet[row][studentIDColumn] == studentID) {
            targetRow = row;
            break;
        }
    }

    if (targetRow == -1) {
        cout << "Error: StudentID " << studentID << " not found!" << endl;
        char tryAgain;
        do {
            cout << "Do you want to try another StudentID? (y/n): ";
            cin >> tryAgain;
            cin.ignore();
        } while (tryAgain != 'y' && tryAgain != 'Y' && tryAgain != 'n' && tryAgain != 'N');

        if (tryAgain == 'y' || tryAgain == 'Y') {
            deleteRow();
        } else {
            cout << "Deletion cancelled." << endl;
        }
        return;
    }

    // Shift rows up
    for (int row = targetRow; row < nextRow - 1; row++) {
        for (int col = 0; col < numcolumn; col++) {
            attendanceSheet[row][col] = attendanceSheet[row + 1][col];
        }
    }

    nextRow--;
    cout << "\nRow deleted successfully!" << endl;
    cout << "Updated sheet: " << endl;
    viewCSV();
    cout << "Press Enter to continue...";
    cin.get();
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
    getline(cin, schoolTermName);
    while(schoolTermName.empty())
    {
      cout << "Invalid term name. Please enter again: ";
      getline(cin, schoolTermName);
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
  cout << endl << "Enter filename to load (add .csv when enter filename)/(or -1 to skip to Menu):" << endl;
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
      cout <<"Please enter again (add .csv when enter filename) (or -1 to skip to Menu):" << endl;
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
        cout << "1. Update School Term" << endl;
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
            cout << "Current School Term: " << schoolTermName << endl;
            cout << "Enter NEW School Term Name (Press Enter to cancel): ";
    
            string newTerm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            getline(cin, newTerm);

            if (!newTerm.empty()) {
                schoolTermName = newTerm;
                saveTerm(schoolTermName); 
                cout << "Database updated successfully!" << endl;
                } 
            else {
                cout << "Update cancelled." << endl;
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
            if(isSheetCreated) {
               if (currentFileName.empty()) {
                    cout << "File name missing. Enter filename to save: ";
                    cin >> currentFileName;
                    currentFileName = currentFileName + ".csv";
                }

                writeToFile(currentFileName);
                cout << "File name: " << currentFileName << endl;
            }
            cout << "Exiting program..." << endl;
            cout << "Press Enter to close this window..." << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cin.get();

            break;
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
