

#include <iostream>
#include <cctype>

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
     

   cout << "Sheet Structure created successfully" << endl << endl ;

   cout << "============= Summary Columns ===============" << endl;
   int j = 0;

   while(j < numcolumn)
        {
          cout << " Column " << (j + 1) << " name: " << column_name[j] << " (" << column_type [j] << ")" <<endl; /// column type also use this one to display
              
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

