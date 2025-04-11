#include <iostream>
#include <string>
#include <sstream>


#include "options.cpp"
#include "MyTemplates.h"
using namespace std;

//var
string filterCriteria = "Point2D";  // default
string sortCriteria = "x-ordinate"; // default
string sortOrder = "ASC"; // default


//hold the selected till enter is press
void waitForEnter() {
    cout << endl;
    cout << "Press Enter to return to the selection menu..." << endl;
    cin.ignore(); 
    cin.get();     // Wait for the user to press Enter
}

void selection() {
    int choice;
    while (true) {
        cout << "Student ID: 8750762" << endl;
        cout << "Student Name: Kelvin Yap" << endl;
        cout << "------------------------------------" << endl;
        cout << "Welcome to Assn3 Program!" << endl;
        cout << endl;
        cout << "1) Read in data" << endl;
        cout << "2) Specify filtering criteria" << "(current: " << filterCriteria  << ")"<< endl;
        cout << "3) Specify sorting criteria" << "(current: " << sortCriteria << ")"<< endl;
        cout << "4) Specify sorting order" << "(current: " << sortOrder << ")"<< endl;
        cout << "5) View data" << endl;
        cout << "6) Store data" << endl;
        cout << "7) Exit program" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        // choice 1
        if (choice == 1) {
            processConfigFile();
            waitForEnter();
            }
        //choice 2
        else if (choice == 2) {
            filterCrit();
            waitForEnter();
        } 
        //choice 3
        else if (choice == 3){
            sortCrit();
            waitForEnter();
        }
        //choice 4 
        else if (choice == 4){
            sortOrdering();
            waitForEnter();
        }
        //choice 5
        else if (choice == 5){
            viewData(currentFilename);
            waitForEnter();
        }
        //choice 6
        else if (choice == 6){
            storeData();
            waitForEnter();
        }
        // quit program 
        else if (choice == 7) {
            cout << endl;
            cout << "Exiting program..." << endl;
            break;
        // invalid choice
        } else {
            cout << endl;
            cout << "Invalid choice.\n";
        }
    }
}
// int main
int main() {
        
    selection();    
    return 0;
}