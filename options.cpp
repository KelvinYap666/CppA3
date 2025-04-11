#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <set>

#include "options.h"
#include "Point2D.cpp"
#include "Point2D.h"
#include "Point3D.cpp"
#include "Point3D.h"
#include "Line2D.cpp"
#include "Line2D.h"
#include "Line3D.cpp"
#include "Line3D.h"

using namespace std;

//global var
string currentFilename = "";
vector<Point2D> points2D;
vector<Point3D> points3D;
vector<Line2D> lines2D;
vector<Line3D> lines3D;

//file function
bool processConfigFile() {
    string cfgfile;
    ifstream file;

    while (true) {  
        cout << "Please enter filename: ";
        cin >> cfgfile;

        file.open(cfgfile);
        if (file.is_open()) {
            currentFilename = cfgfile;
            break;  
        }

        cout << "File not found. Please check the filename and try again.\n\n";
        cout << "Returning to menu..." << endl;
        return false;
    }

    cout << "Reading file: " << cfgfile << endl;
    int recordcount = 0;
    string line;

    // Clear existing data
    points2D.clear();
    points3D.clear();
    lines2D.clear();
    lines3D.clear();

    while (getline(file, line)) {
        if (!line.empty()) {
            recordcount++;

            // Parse Point2D
            if (line.find("Point2D") != string::npos) {
                stringstream ss(line);
                string label, coords;
                int x, y;
                getline(ss, label, ',');
                getline(ss, coords, ']');
                stringstream coordStream(coords);
                char bracket;
                coordStream >> bracket >> x >> bracket >> y;
                Point2D p(x, y);
                points2D.push_back(p);  // Use push_back for vector
            }

            // Parse Line2D
            if (line.find("Line2D") != string::npos) {
                stringstream ss(line);
                string label;
                int x1, y1, x2, y2;
                char discard;

                regex pattern(R"(\[(-?\d+), (-?\d+)\], \[(-?\d+), (-?\d+)\])");
                smatch matches;
                if (regex_search(line, matches, pattern)) {
                    x1 = stoi(matches[1].str());
                    y1 = stoi(matches[2].str());
                    x2 = stoi(matches[3].str());
                    y2 = stoi(matches[4].str());
                    Line2D lineObj(Point2D(x1, y1), Point2D(x2, y2));
                    lines2D.push_back(lineObj);
                }
            }

            // Parse Point3D
            if (line.find("Point3D") != string::npos) {
                stringstream ss(line);
                string label, coords;
                int x, y, z;
                getline(ss, label, ',');
                getline(ss, coords, ']');
                stringstream coordStream(coords);
                char bracket;
                coordStream >> bracket >> x >> bracket >> y >> bracket >> z;
                Point3D p(x, y, z);
                points3D.push_back(p);
            }

            // Parse Line3D
            if (line.find("Line3D") != string::npos) {
                stringstream ss(line);
                string label;
                char discard;
                int x1, y1, z1, x2, y2, z2;
                ss >> label >> discard >> x1 >> discard >> y1 >> discard >> z1 >> discard >> discard
                   >> discard >> x2 >> discard >> y2 >> discard >> z2 >> discard;
                lines3D.push_back(Line3D(Point3D(x1, y1, z1), Point3D(x2, y2, z2)));
            }
        }
    }

    file.close();
    cout << recordcount << " records read in successfully!" << endl;

    return true;
}

//filter criteria function
void filterCrit() {
    cout << "[Specifying filtering criteria (current: " << filterCriteria << ")]" << endl;
    cout << endl;
    char selected;
    cout << "\ta)\tPoint2D records" << endl;
    cout << "\tb)\tPoint3D records" << endl;
    cout << "\tc)\tLine2D records" << endl;
    cout << "\td)\tLine3D records" << endl; 

    // User input
    cout << endl;
    cout << "Please enter your criteria (a - d): ";
    cin >> selected;

    switch (selected) {
        case 'a': 
            filterCriteria = "Point2D";
            sortCriteria = "x-ordinate";  // Default sorting for Point2D
            cout << "Filter criteria successfully set to " << filterCriteria << "!" << endl;
            break;
        case 'b': 
            filterCriteria = "Point3D";
            sortCriteria = "x-ordinate";  // Default sorting for Point3D
            cout << "Filter criteria successfully set to " << filterCriteria << "!" << endl;
            break;
        case 'c': 
            filterCriteria = "Line2D";
            sortCriteria = "X and Y coordinate values of Pt. 1";  // Default sorting for Line2D
            cout << "Filter criteria successfully set to " << filterCriteria << "!" << endl;
            break;
        case 'd': 
            filterCriteria = "Line3D";
            sortCriteria = "X and Y coordinate values of Pt. 1";  // Default sorting for Line3D
            cout << "Filter criteria successfully set to " << filterCriteria << "!" << endl;
            break;
        default:
            cout << "Invalid selection. Keeping previous filter: " << filterCriteria << endl;
            return;
    }
}
// sort criteria function
void sortCrit() {
    cout << "[Specifying sorting criteria (current: " << sortCriteria << ")]" << endl;
    char selected;
    // Check the filtering criteria to display appropriate sorting options
    if (filterCriteria == "Point2D") {
        cout << "\ta)\tx-ordinate" << endl;
        cout << "\tb)\ty-ordinate" << endl;
        cout << "\tc)\tDist. fr Origin value" << endl;
    } 
    else if (filterCriteria == "Point3D") {
        cout << "\ta)\tx-ordinate" << endl;
        cout << "\tb)\ty-ordinate" << endl;
        cout << "\tc)\tz-ordinate" << endl;
        cout << "\td)\tDist. fr Origin value" << endl;
    } 
    else if (filterCriteria == "Line2D" || filterCriteria == "Line3D") {
        cout << "\ta)\tX and Y coordinate values of Pt. 1" << endl;
        cout << "\tb)\tX and Y coordinate values of Pt. 2" << endl;
        cout << "\tc)\tLength" << endl;
    }
    else {
        cout << "Invalid filter criteria!" << endl;
        return;
    }

    // User input
    cout << "Please enter your criteria: ";
    cin >> selected;
    if (filterCriteria == "Point2D") {
        switch (selected) {
            case 'a': sortCriteria = "x-ordinate"; break;
            case 'b': sortCriteria = "y-ordinate"; break;
            case 'c': sortCriteria = "Dist. Fr. Origin value";break;
            default:
                cout << "Invalid selection. Keeping previous sort: " << sortCriteria << endl;
                return;
        }
    } 
    else if (filterCriteria == "Point3D") {
        switch (selected) {
            case 'a': sortCriteria = "x-ordinate"; break;
            case 'b': sortCriteria = "y-ordinate"; break;
            case 'c': sortCriteria = "z-ordinate"; break;
            case 'd': sortCriteria = "Dist. fr Origin value"; break;
            default:
                cout << "Invalid selection. Keeping previous sort: " << sortCriteria << endl;
                return;
        }
    } 
    else if (filterCriteria == "Line2D" || filterCriteria == "Line3D") {
        switch (selected) {
            case 'a': sortCriteria = "X and Y coordinate values of Pt. 1"; break;
            case 'b': sortCriteria = "X and Y coordinate values of Pt. 2"; break;
            case 'c': sortCriteria = "Length"; break;
            default:
                cout << "Invalid selection. Keeping previous sort: " << sortCriteria << endl;
                return;
        }
    } 
    cout << "Filter criteria successfully set to " << sortCriteria << endl;
}    

//sort order function
void sortOrdering() {
    cout << "[Specifying sorting order (current: " << sortOrder << ")]" << endl;

    char selected;
    cout << "\ta)\tASC (Ascending order)" << endl;
    cout << "\tb)\tDSC (Desceding order)" << endl;

    // User input
    cout << "Please enter your criteria (a or b): ";
    cin >> selected;

    switch (selected) {
        case 'a': sortOrder = "ASC"; break;
        case 'b': sortOrder = "DSC"; break;
        default:
            cout << "Invalid selection. Keeping previous filter: " << sortOrder << endl;
            return;
    }

    cout << "Filter criteria successfully set to " << sortOrder<< endl;
}    

// Comparator for sorting Point2D
bool compare2dPoints(const Point2D& p1, const Point2D& p2) {
    if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
            return p1.getX() < p2.getX();
        } else {
            return p1.getX() > p2.getX();
        }
    } 
    else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
            return p1.getY() < p2.getY();
        } else {
            return p1.getY() > p2.getY();
        }
    }
    else if (sortCriteria == "Dist. Fr. Origin value") {
        if (sortOrder == "ASC") {
            return p1.getScalarValue() < p2.getScalarValue();
        } else {
            return p1.getScalarValue() > p2.getScalarValue();
        }
    }
    return false;
}

// Comparator for sorting Point3D
bool compare3dPoints(const Point3D& p1, const Point3D& p2){
    if (sortCriteria == "x-ordinate") {
        if (sortOrder == "ASC") {
            return p1.getX() < p2.getX();
        } else {
            return p1.getX() > p2.getX();
        }
    }
    else if (sortCriteria == "y-ordinate") {
        if (sortOrder == "ASC") {
            return p1.getY() < p2.getY();
        } else {
            return p1.getY() > p2.getY();
        }
    }
    else if (sortCriteria == "z-ordinate") {
        if (sortOrder == "ASC") {
            return p1.getZ() < p2.getZ();
        } else {
            return p1.getZ() > p2.getZ();
        }
    }
    else if (sortCriteria == "Dist. fr Origin value") {
        if (sortOrder == "ASC") {
            return p1.getScalarValue() < p2.getScalarValue();
        } else {
            return p1.getScalarValue() > p2.getScalarValue();
        }
    }
    return false;
}

// Comparator for sorting Line2D
bool compare2dLine(const Line2D& l1, const Line2D& l2) {
    // Sort by "X and Y coordinate values of Pt. 1"
    if (sortCriteria == "X and Y coordinate values of Pt. 1") {
        if (sortOrder == "ASC") {
            return l1.getPt1() < l2.getPt1(); // Sort by pt1's (X, Y) in ascending order
        } else {
            return l1.getPt1() > l2.getPt1(); // Sort by pt1's (X, Y) in descending order
        }
    }
    // Sort by "X and Y coordinate values of Pt. 2"
    else if (sortCriteria == "X and Y coordinate values of Pt. 2") {
        if (sortOrder == "ASC") {
            return l1.getPt2() < l2.getPt2(); // Sort by pt2's (X, Y) in ascending order
        } else {
            return l1.getPt2() > l2.getPt2(); // Sort by pt2's (X, Y) in descending order
        }
    }
    // Sort by "Length"
    else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
            return l1.getScalarValue() < l2.getScalarValue(); // Sort by length in ascending order
        } else {
            return l1.getScalarValue() > l2.getScalarValue(); // Sort by length in descending order
        }
    }
    return false; 
}

// Comparator for sorting Line3D
bool compare3dLine(const Line3D& l1, const Line3D& l2) {
    if (sortCriteria == "X and Y coordinate values of Pt. 1") {
        if (sortOrder == "ASC") {
            return l1.getPt1() < l2.getPt1();
        } else {
            return l1.getPt1() > l2.getPt1();
        }
    }
    else if (sortCriteria == "X and Y coordinate values of Pt. 2") {
        if (sortOrder == "ASC") {
            return l1.getPt2() < l2.getPt2();
        } else {
            return l1.getPt2() > l2.getPt2();
        }
    }
    else if (sortCriteria == "Length") {
        if (sortOrder == "ASC") {
            return l1.getScalarValue() < l2.getScalarValue();
        } else {
            return l1.getScalarValue() > l2.getScalarValue();
        }
    }
    return false;
}

//view the data
void viewData(const string& currentFilename) {
    // Check if the file is loaded
    if (currentFilename.empty()) {
        cout << "Error: No file has been loaded yet. Please load a file first.\n";
        return;
    }

    // Open the file
    ifstream file(currentFilename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file '" << currentFilename << "'\n";
        return;
    }

    cout << endl;
    cout << "[View Data ... ]" << endl;
    cout << "filtering criteria: " << filterCriteria << endl;
    cout << "sorting criteria: " << sortCriteria << endl;
    cout << "sorting order: " << sortOrder << endl;
    cout << endl;
    
    //set for each option
    set<Point2D> points2D;
    set<Point3D> points3D;
    set<Line2D> lines2D;
    set<Line3D> lines3D;

    // Read through the file line by line
    string line;
    while (getline(file, line)) {
        // Check for "Point2D" in line and parse it
        if (line.find("Point2D") != string::npos) {
            stringstream ss(line);
            string label, coords;
            int x, y;
            getline(ss, label, ',');
            getline(ss, coords, ']');
            stringstream coordStream(coords);
            char bracket;
            coordStream >> bracket >> x >> bracket >> y;
            Point2D p(x, y);
            points2D.insert(p);  // Add to set to avoid duplicates
        }

        //line2D
        if (line.find("Line2D") != string::npos) {
            stringstream ss(line);
            string label;
            int x1, y1, x2, y2;
            char discard;

            // Regular expression to match the coordinates in the brackets
            regex pattern(R"(\[(-?\d+), (-?\d+)\], \[(-?\d+), (-?\d+)\])");

            smatch matches;
            if (regex_search(line, matches, pattern)) {
                // Extract values from the matched groups
                x1 = stoi(matches[1].str());
                y1 = stoi(matches[2].str());
                x2 = stoi(matches[3].str());
                y2 = stoi(matches[4].str());

                // Construct the Line2D object with both points
                Line2D lineObj(Point2D(x1, y1), Point2D(x2, y2));
                lines2D.insert(lineObj);  // Insert into the set
            } else {
                cout << "Error parsing line: " << line << endl;
            }
        }

        // Check for "Point3D" in line and parse it
        if (line.find("Point3D") != string::npos) {
            stringstream ss(line);
            string label, coords;
            int x, y, z;
            getline(ss, label, ',');
            getline(ss, coords, ']');
            stringstream coordStream(coords);
            char bracket;
            coordStream >> bracket >> x >> bracket >> y >> bracket >> z;
            Point3D p(x, y, z);
            points3D.insert(p);  // Add to set to avoid duplicates
        }
        if (line.find("Line3D") != string::npos) {
            stringstream ss(line);
            string label;
            char discard;
            int x1, y1, z1, x2, y2, z2;
        
            // Read the label and properly extract values
            ss >> label >> discard >> x1 >> discard >> y1 >> discard >> z1 >> discard >> discard
               >> discard >> x2 >> discard >> y2 >> discard >> z2 >> discard;
            // Create and insert Line3D object
            lines3D.insert(Line3D(Point3D(x1, y1, z1), Point3D(x2, y2, z2)));
        }
           
    }

    // Display data based on the filter criteria
    if (filterCriteria == "Point2D") {
        if (points2D.empty()) {
            cout << "No Point2D data found in the file.\n";
        } else {
            vector<Point2D> pointVector(points2D.begin(), points2D.end());
            sort(pointVector.begin(), pointVector.end(), compare2dPoints);
            cout << setw(7) << "X" << setw(6) << "Y" << "    Dist. Fr Origin" << endl;
            cout << "  --------------------------------" << endl;
            for (const auto &p : pointVector) {
                cout << p << endl;
            }
        }
    } else if (filterCriteria == "Point3D") {
        if (points3D.empty()) {
            cout << "No Point3D data found in the file.\n";
        } else {
            vector<Point3D> pointVector(points3D.begin(), points3D.end());
            sort(pointVector.begin(), pointVector.end(), compare3dPoints);
            cout << setw(7) << "X" << setw(6) << "Y" << setw(6) << "Z" << "    Dist. Fr Origin" << endl;
            cout << "  --------------------------------" << endl;
            for (const auto &p : pointVector) {
                cout << p << endl;
            }
        }
    }else if (filterCriteria == "Line2D") {
    if (lines2D.empty()) {  
        cout << "No Line2D data found in the file.\n";
    } else {
        vector<Line2D> lineVector(lines2D.begin(), lines2D.end());
        // Sort lines2d
        sort(lineVector.begin(), lineVector.end(), 
            [](const Line2D &a, const Line2D &b) { 
                return compare2dLine(a, b);
            });

        // Table Header
        cout << setw(7) << " P1-X" << setw(6) << " P1-Y"
             << setw(9) << " P2-X" << setw(6) << " P2-Y"
             << "    Length" << endl;
        cout << "  ----------------------------------------" << endl;

        for (const auto &line : lineVector) {
            cout << line << endl;
        }
    }
    }else if(filterCriteria == "Line3D") {
        if (lines3D.empty()) {  
            cout << "No Line3D data found in the file.\n";
        } else {
            vector<Line3D> lineVector(lines3D.begin(), lines3D.end());
    
            // Sorting using compare3dLine function
            sort(lineVector.begin(), lineVector.end(), compare3dLine);
    
            // Print Header
            cout << setw(6) << " P1-X" 
                 << setw(6) << " P1-Y" 
                 << setw(6) << " P1-Z"
                 << setw(9) << " P2-X" 
                 << setw(6) << " P2-Y" 
                 << setw(6) << " P2-Z"
                 << "    Length" << endl;
            cout << " -------------------------------------------------------" << endl;
    
            // Print Sorted 3D Lines
            for (const auto &line : lineVector) {
                cout << line << endl;
            }
        }
    }
    else {
        cout << "Invalid filter criteria!" << endl;
    }
    // Close the file
    file.close();
}

//store data
void storeData() {
    // Check if there is any data to store
    if (filterCriteria == "Point2D" && points2D.empty()) {
        cout << "No Point2D data" << endl;
        return;
    } else if (filterCriteria == "Point3D" && points3D.empty()) {
        cout << "No Point3D data" << endl;
        return;
    } else if (filterCriteria == "Line2D" && lines2D.empty()) {
        cout << "No Line2D data" << endl;
        return;
    } else if (filterCriteria == "Line3D" && lines3D.empty()) {
        cout << "No Line3D data" << endl;
        return;
    }

    // Get the filename from the user
    string storeFile;
    cout << endl;
    cout << "Please enter file name: ";
    cin >> storeFile;

    // Open the file for writing
    ofstream outFile(storeFile);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Write header information
    outFile << "Filtering criteria: " << filterCriteria << endl;
    outFile << "Sorting criteria: " << sortCriteria << endl;
    outFile << "Sorting order: " << sortOrder << endl;
    outFile << endl;

    // Store data based on the filter criteria
    int count = 0;
    if (filterCriteria == "Point2D") {
        // Use a set to remove duplicates
        set<Point2D> uniquePoints(points2D.begin(), points2D.end());
        vector<Point2D> pointVector(uniquePoints.begin(), uniquePoints.end());
        sort(pointVector.begin(), pointVector.end(), compare2dPoints);

        outFile << setw(7) << "X" << setw(6) << "Y" << "    Dist. Fr Origin" << endl;
        outFile << "--------------------------------" << endl;
        for (const auto& point : pointVector) {
            outFile << point << endl;
            count++;
        }
        
    } else if (filterCriteria == "Point3D") {
        // Use a set to remove duplicates
        set<Point3D> uniquePoints(points3D.begin(), points3D.end());
        vector<Point3D> pointVector(uniquePoints.begin(), uniquePoints.end());
        sort(pointVector.begin(), pointVector.end(), compare3dPoints);

        outFile << setw(7) << "X" << setw(6) << "Y" << setw(6) << "Z" << "    Dist. Fr Origin" << endl;
        outFile << "  --------------------------------" << endl;
        for (const auto& point : pointVector) {
            outFile << point << endl;
            count++;
        }
    } else if (filterCriteria == "Line2D") {
        // Use a set to remove duplicates
        set<Line2D> uniqueLines(lines2D.begin(), lines2D.end());
        vector<Line2D> lineVector(uniqueLines.begin(), uniqueLines.end());
        sort(lineVector.begin(), lineVector.end(), compare2dLine);

        outFile << setw(7) << " P1-X" << setw(6) << " P1-Y"
                << setw(9) << " P2-X" << setw(6) << " P2-Y"
                << "    Length" << endl;
        outFile << "  ----------------------------------------" << endl;
        for (const auto& line : lineVector) {
            outFile << line << endl;
            count++;
        }
    } else if (filterCriteria == "Line3D") {
        // Use a set to remove duplicates
        set<Line3D> uniqueLines(lines3D.begin(), lines3D.end());
        vector<Line3D> lineVector(uniqueLines.begin(), uniqueLines.end());
        sort(lineVector.begin(), lineVector.end(), compare3dLine);

        outFile << setw(6) << " P1-X" 
                << setw(6) << " P1-Y" 
                << setw(6) << " P1-Z"
                << setw(9) << " P2-X" 
                << setw(6) << " P2-Y" 
                << setw(6) << " P2-Z"
                << "    Length" << endl;
        outFile << " -------------------------------------------------------" << endl;
        for (const auto& line : lineVector) {
            outFile << line << endl;
            count++;
        }
    }

    // Close the file
    outFile.close();

    // Print success message
    cout << endl;
    cout << "File is saved as: " << storeFile << endl; 
    cout << count << " records output successfully!" << endl;
    cout << endl;
}