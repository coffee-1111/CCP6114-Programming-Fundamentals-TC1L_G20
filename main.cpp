#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


// global variables
string term_name = "";
int columnNum = 0;
int rowNum = 0;
string columnName[10] ;
string attendance[50][10];

//Function: see the attendance in view csv mode
void viewCSV()
{
    cout << "-------------------------------------------" << endl;
    cout << "Current Attendance Sheet (CSV Mode)" << endl;
    cout << "-------------------------------------------" << endl;

    // Print column headers
    for (int i = 0; i < columnNum; i++)
    {
        cout << columnName[i];
        if (i < columnNum - 1)
            cout << ", ";
    }
    cout << endl;

     if (rowNum == 0)
    {
        cout << "Current sheet row number is empty." << endl << endl;
        
    }

    // print the rows
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < columnNum; j++)
        {
            cout << attendance[i][j];
            if (j < columnNum - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

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
    rowNum = 0;
    columnNum = 0;

    
  // read header as columns
    if (getline(file, line))
    {
        stringstream header(line);
        string col;

        while (getline(header, col, ',') && columnNum < 10)
        {
            if (!col.empty() && col[0] == ' ')
                col.erase(0, 1);

            columnName[columnNum] = col;
            columnNum++;
        }
    }

    while (getline(file, line) && rowNum < 50)
    {
        stringstream ss(line);
        string value;
        int col = 0;

        while (getline(ss, value, ',') && col < columnNum)
        {
            // Remove leading space if any
            if (!value.empty() && value[0] == ' ')
                value.erase(0, 1);

            attendance[rowNum][col] = value;
            col++;
        }
        rowNum++;
    }

    file.close();
    cout << "Successfully loaded: " << filename << endl;
    return true;
}

// function 2 : Wwrite data into the csv file
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
    for (int i = 0; i < columnNum; i++)
    {
        file << columnName[i];
        if (i < columnNum - 1)
            file << ", ";
    }
    file << endl;

    // Write rows
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < columnNum; j++)
        {
            file << attendance[i][j];
            if (j < columnNum - 1)
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

void setupDatabse()
{
  cout << " Create School Term (Database) " << endl;


  //loading Term 
  string saved_term = loadTerm();
  if (saved_term != "" && saved_term !=" ")
  {
    term_name = saved_term;
    cout << "---------------------------------------------------------------"<< endl;
    cout << "Welcome back! Database " << term_name << " loaded automatically" << endl;
    cout << "---------------------------------------------------------------"<< endl;
  }
  else
  {
    cout << "No saved database found. Initializing..." << endl;
    cout << "Enter term name:" << endl;
    getline(cin >> ws,term_name);
    while(term_name.empty())
    {
      cout << "Invalid term name. Please enter again." << endl;
      cout << "Enter term name:" << endl;
      getline(cin >> ws,term_name);
    }
  saveTerm(term_name);
  cout << "Database  " << term_name <<"  created and loaded." << endl << endl;
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
    cout << "(No previoud sheets found)"<< endl << endl;
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
      cout << "Current Attendance Sheet - "<< term_name << endl;
      viewCSV();
      cout << "Going to Main Menu..." << endl;
    }
  }


}

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

   int numcolumn = getValidColumn(); ///get column from function

   string column_name[10] ;
   string column_type[10] ;
   


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
     
   columnNum = numcolumn;
    for (int i = 0; i < columnNum; i++)
    {
       columnName[i] = column_name[i];
    }
rowNum = 0;

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

void MainMenu()
{
  int choice = 0;
    while (choice != 4) {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Create New Sheet" << endl;
        cout << "2. View Current Sheet" << endl;
        cout << "3. Load Existing Sheet" << endl;
        cout << "4. Exit" << endl;
        cout << "Selection: ";
        cin >> choice;

        switch (choice) {
            case 1: createSheet(); break;
            case 2: viewCSV(); break;
            case 3: fileLoadDatabase(); break;
            case 4: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    }
}








int main()
{
  setupDatabse();

  fileLoadDatabase();


  MainMenu();

  return 0 ;

}