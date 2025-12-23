#include <iostream>
using namespace std;

//this one for now just for display testing, can remove later 
int columnNum = 3;
int rowNum =2;

string columnName [3] = {"StudentID", "Name", "Status"};
string attendance[50][3] =
{
{"1001", "John Tan", "1"},
{"1002", "Mei Ling", "0"}  
};
void viewCSV()
{
  cout << "-------------------------------------------" <<endl;
  cout << "View Attendance Sheet (CSV Mode)" << endl;
  cout << "-------------------------------------------" <<endl;
    if (columnNum == 0)
    {
        cout << "No sheet created." << endl;
        return;
    }

    if (rowNum == 0)
    {
        cout << "Sheet is empty." << endl;
        return;
    }
  //printing column
    for (int i = 0; i < columnNum; i++)
    {
        cout << columnName[i];
        if (i < columnNum - 1)
            cout << ", ";
    }
    cout << endl;
  //printing rows
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
int main()
{
    viewCSV();
    return 0;
}
