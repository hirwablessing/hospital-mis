#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Location
{
public:
    string name;
};

class Disease
{
public:
    string name;
    string location;
    int cases;
};

inline bool fileExists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void createLocation()
{
    Location location;
    // create a file
    ofstream locations;
    locations.open("locations.txt", ios::app);

    cout << "Enter the name of the location: ";
    cin >> location.name;
    locations << location.name << endl;
    locations.close();
    cout << "\n\n***Location created successfully***\n\n"
         << endl;
}

string searchLocation(string location)
{
    ifstream file;
    file.open("locations.txt");
    string line;
    string result = "";
    while (getline(file, line))
    {
        if (line.find(location) != string::npos)
        {
            result = line;
        }
    }
    file.close();

    if (result == "")
    {
        cout << "\n\nLocation not found, try another one!\n\n";
    }

    return result;
}

void deleteLocation()
{

    string locationToDelete;
    cout << "Enter location name: ";
    cin >> locationToDelete;

    string foundLocation = searchLocation(locationToDelete);

    if (foundLocation != "")
    {
        ifstream file;
        ofstream newfile;
        file.open("locations.txt");
        newfile.open("newlocations.txt");
        string line;

        while (getline(file, line))
        {
            if (foundLocation != line)
            {
                newfile << line << endl;
            }
        }
        cout << endl;
        file.close();
        newfile.close();
        remove("locations.txt");
        rename("newlocations.txt", "locations.txt");
        cout << "\n\n**Location deleted successfully**\n\n"
             << endl;
    }
}

void createDisease()
{
    Disease disease;
    ofstream diseases;
    diseases.open("diseases.txt", ios::app);

create_disease:
    cout << "Enter the name of the disease: ";
    cin >> disease.name;
    cout << "Enter the name of the location: ";
    cin >> disease.location;
    string loc = searchLocation(disease.location);
    if (loc == "")
    {
        cout << "\n\nLocation not found, try another one!\n\n";
        goto create_disease;
    }
    cout << "Enter the number of cases: ";
    cin >> disease.cases;

    if (fileExists("diseases.txt") == 0)
    {
        diseases << "Disease Name"
                 << "\t"
                 << "Location"
                 << "\t"
                 << "Cases" << endl;
    }

    diseases << disease.name << "\t\t" << disease.location << "\t\t" << disease.cases << endl;
    diseases.close();
    cout << "\n\n***Disease created successfully***\n\n"
         << endl;
}

void listLocations()
{
    system("clear");
    ifstream file;
    int counter;
    file.open("locations.txt");
    string line;
    while (getline(file, line))
    {
        cout << "\n\n"
             << counter + 1 << " " << line << "\n";
        counter++;
    }
    file.close();
}

void tokenizestring(string const &str, const char delim, vector<string> &out)
{
    // split the string into an array of strings
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim))
    {
        out.push_back(token);
    }
}

void listDiseasesInAlocation()
{
    // read diseases from file
    ifstream file;
    file.open("diseases.txt");
    string line;
    while (getline(file, line))
    {
        vector<string> words;
        tokenizestring(line, '\t', words);
        cout << "\n\n"
             << words[0];
    }
    cout << "\n\n";
    file.close();
}

void menuDisplay()
{
    int option;

    do
    {
        cout << "======================================================================\n"
             << endl;
        cout << "*\t\t Welcome to Disease Cases Reporting system!\t\t*\n"
             << endl;
        cout << "*  ********************************************************************   *\n"
             << endl;
        cout << "*\n"
             << endl;
        cout << "* It is developed by Blessing Hirwa as practical *\n";
        cout << "* evaluatin for end of Year 3 *" << endl;
        cout << "====================================================\n"
             << endl;
        cout << "Starting time: Thu Apr 05 23:59:08 CAT 2022  " << endl;
        cout << "Need a help? Type help then press Enter key.  " << endl;

        cout << "===============================================================================" << endl;
        cout << "\t\t\t\t\tHELP MENU\t\t\t" << endl;
        cout << "================================================================================\n\n"
             << endl;
        cout << "1. add<Location> \t\t\t\t\t: Add location" << endl;
        cout << "2. delete<Location> \t\t\t\t: Delete an existing location" << endl;
        cout << "3. record<Location> <disease> <cases> \t\t: Record a disease and its cases" << endl;
        cout << "4. list locations \t\t\t\t: List all existing locations" << endl;
        cout << "5. list diseases \t\t\t\t: List all existing Diseases in locations" << endl;
        cout << "6. where <disease> \t\t\t\t: Find where disease exists" << endl;
        cout << "7. cases <location><disease> \t\t\t: Find cases of a disease in a location" << endl;
        cout << "8. cases <disease> \t\t\t\t: Find total cases of a given disease" << endl;
        cout << "9. help \t\t\t\t: Prints user manual" << endl;
        cout << "10. Exit \t\t\t\t: Exits the program" << endl;

        cout << "\t\tConsole > (1-9): ";
        cin >> option;

        system("clear");

        switch (option)
        {
        case 1:
            createLocation();
            break;
        case 2:
            deleteLocation();
            break;
        case 3:
            createDisease();
            break;
        case 4:
            listLocations();
            break;
        case 5:
            listDiseasesInAlocation();
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }

    } while (option != 10);
}

int main()
{
    menuDisplay();
    return 0;
}