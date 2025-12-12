

#include <iostream>

using namespace std;

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
   getline(cin, sheet_name) ;

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
   
   ///set default Column 1 
   column_name[0] = "StudentID" ;
   column_type[0] =  "INT" ;  

   cout << "\nColumn 1 name :" << column_name[0] << " (" << column_type[0] << ")" << endl << endl;

   int i = 1; 
   int colNum = 2;

  
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

int main()
{
   cout << "============================" << endl;
   cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
   cout << "============================" << endl  << endl;

   createSheet();


   return 0;
}

