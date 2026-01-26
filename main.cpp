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
    cout << "View Attendance Sheet (CSV Mode)" << endl;
    cout << "-------------------------------------------" << endl;

    if (rowNum == 0)
    {
        cout << "Sheet is empty." << endl;
        return;
    }

    // Print column headers
    for (int i = 0; i < columnNum; i++)
    {
        cout << columnName[i];
        if (i < columnNum - 1)
            cout << ", ";
    }
    cout << endl;

    // print tthe rows
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
        cout << "Error: Unable to open file." << endl;
        return false;
    }

    string line;
    rowNum = 0;

    // Skip the header line
    getline(file, line);

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
  cout << "---------------------------------" << endl;

  //loading Term 
  string saved_term = loadTerm();
  if (saved_term != "" && saved_term !=" ")
  {
    term_name = saved_term;
    cout << "Welcome back! Database" << term_name << "loaded automatically" << endl;
  }
  else
  {
    cout << "No saved database found. Initializing..." << endl;
    cout << "Enter school term name:" << endl;
    getline(cin >> ws,term_name);
    while(term_name.empty())
    {
      cout << "Invalid term name. Please enter again." << endl;
      cout << "Enter school term name:" << endl;
      getline(cin >> ws,term_name);
    }
  saveTerm(term_name);
  cout << "Database " << term_name <<" created." << endl << endl;
  }
}

void fileLoadDatabase()
{
  
  //display exist files
  cout <<"Available Attendance Sheets"<< endl;
  cout << "----------------------------"<< endl;
  bool hasFiles = displayExistingFiles();
  if (!hasFiles)
  {
    cout << "(No previoud records found)"<< endl;
    cout << "Please enter -1 to go to menu to create new sheet"<< endl<< endl;
  }

  // load filename
  string filename;
  cout << "Enter filename to load(or -1 to skip to Menu):" << endl;
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
      cout << "Reading Attendance data from file..." << endl;
      cout <<"Error: File not found " << endl;
      cout <<"Please enter again (or -1 to skip):" << endl;
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
      cout << "Reading Attendance data from file..." << endl;
      cout << "Successfully loaded: " << filename << endl;
      cout << "---------------------------------------"<< endl;
      cout << "Current Attendance Sheet - "<< term_name << endl;
      cout << "---------------------------------------" << endl;
      viewCSV();
      cout << " Going to Main Menu..." << endl;
    }
  }


}

void MainMenu()
{
  cout << "main menu" << endl;
}








int main()
{
  setupDatabse();

  fileLoadDatabase();

  MainMenu();

  return 0 ;

}