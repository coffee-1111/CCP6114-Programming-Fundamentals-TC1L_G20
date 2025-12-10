

#include <iostream>

using namespace std;

int main()
{   
    string sheet_name;
    int numcolumn ; 

    cout << "============================" << endl;
    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "============================" << endl  << endl;

    cout << "Enter attendence sheet name:" << endl;
    cin >> sheet_name ;
    cout << "\nAttendance sheet " << sheet_name << " created successfully" << endl << endl;

    cout << "Define number of columns (max 10) : " << endl;
    cin  >> numcolumn;


    while (numcolumn < 1 || numcolumn > 10)
     {
      cout << "\nNumber of columns is invalid. Please enter again.(1-10) " << endl;
      cout << "Define number of columns (max 10) : " << endl;
      cin  >> numcolumn ;

     }
    

    string column_name[10] ;
    string column_type[10] ;

    column_name[0] = "StudentID" ;
    column_type[0] =  "INT" ;  
    
    cout << "\nColumn 1 name :" << column_name[0] << " (" << column_type[0] << ")" << endl << endl;

    int i = 1; 
    int colNum = 2;

    

    while( i < numcolumn)
     {
        cout << "Enter column " << colNum << " name: " << endl ;
        cin >> column_name[i] ;

        // For column type （ INT/ TEXT）
        //
        //

        cout << "\nColumn "<< colNum << " name :" << column_name[i] << endl << endl;
        
        i = i + 1 ;
        colNum = colNum + 1;
     }
     







     cout << "Sheet Structure created successfully" << endl << endl ;






     return 0;
}

