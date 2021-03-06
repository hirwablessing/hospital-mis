#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <ctime>
#include <regex>

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
    //check if a file exists in the file system
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

string toLowercase(string input)
{
    string str = input;
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    return str;
}

string searchFile(string location, string filename, bool showNotFoundMessage = false)
{
    //a function that searches through a file and return the found result
    ifstream file;
    file.open(filename);
    string line;
    string result = "";
    while (getline(file, line))
    {
        string temp = toLowercase(line);
        if (temp.find(toLowercase(location)) != string::npos)
        {
            result = temp;
        }
    }
    file.close();

    if (result == "" && showNotFoundMessage)
    {
        cout << "\n\nRecord not found, try again!\n\n";
    }

    return result;
}

void createLocation(string locationName)
{
    // create a location
    Location location;
    ofstream locations;
    locations.open("locations.txt", ios::app);
    string duplicateLocation = searchFile(toLowercase(locationName), "locations.txt");

    if (duplicateLocation == "")
    {
        location.name = locationName;
        locations << location.name << endl;
        locations.close();
        cout << "\n\n***Location created successfully***\n\n"
             << endl;
    }
    else
    {
        cout << "Location already exists!" << endl;
    }
}

void deleteLocation(string locationToDelete)
{
    //delete a location
    string foundLocation = searchFile(locationToDelete, "locations.txt", true);
    string diseaseFromLocation = searchFile(toLowercase(locationToDelete), "diseases.txt");

    if (foundLocation != "")
    {
        ifstream file;
        ofstream newfile;
        ifstream diseasesFile;
        ofstream newDiseasesFile;

        file.open("locations.txt");
        newfile.open("newlocations.txt");
        diseasesFile.open("diseases.txt");
        newDiseasesFile.open("newdiseases.txt");
        string line;

        while (getline(file, line))
        {
            if (toLowercase(foundLocation) != toLowercase(line))
            {
                newfile << line << endl;
            }
        }

        //delete cases associated with this location
        while (getline(diseasesFile, line))
        {
            if (toLowercase(diseaseFromLocation) != toLowercase(line))
            {
                newDiseasesFile << line << endl;
            }
        }

        cout << endl;
        file.close();
        newfile.close();
        diseasesFile.close();
        newDiseasesFile.close();
        remove("diseases.txt");
        rename("newdiseases.txt", "diseases.txt");
        remove("locations.txt");
        rename("newlocations.txt", "locations.txt");
        cout << "\n\n**Location deleted successfully**\n\n"
             << endl;
    }
}

void createDisease(string diseaseName, string diseaseLocation, int diseaseCases)
{
    //record a disease
    Disease disease;
    ofstream diseases;
    diseases.open("diseases.txt", ios::app);

    disease.name = diseaseName;
    disease.location = diseaseLocation;
    string loc = searchFile(diseaseLocation, "locations.txt");

    if (loc == "")
    {
        cout << "\n\nLocation not found, try another one!\n\n";
    }
    else
    {

        disease.cases = diseaseCases;

        if (fileExists("diseases.txt") == 0)
        {
            diseases << "Disease Name"
                     << "\t"
                     << "Location"
                     << "\t"
                     << "Cases" << endl;
        }

        diseases << disease.name << "\t" << disease.location << "\t" << disease.cases << endl;
        diseases.close();
        cout << "\n\n***Disease created successfully***\n\n"
             << endl;
    }
}

bool compareFunction(string a, string b) { return a < b; }

void listLocations()
{
    //list all locations stored in a file
    system("clear");
    ifstream file;
    vector<string> foundLocations{};
    file.open("locations.txt");
    string line;

    while (getline(file, line))
    {
        if (!(find(foundLocations.begin(), foundLocations.end(), (line)) != foundLocations.end()))
            foundLocations.push_back(line);
    }
    file.close();

    sort(foundLocations.begin(), foundLocations.end(), compareFunction);
    for (int i = 0; i < foundLocations.size(); i++)
    {

        cout << "\n\n"
             << i + 1 << ". " << foundLocations[i] << endl;
    }

    cout << "\n\n";
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

void listDiseasesInExistinglocation()
{
    // read diseases from file
    ifstream file;
    file.open("diseases.txt");
    string line;
    vector<string> sortedDiseases;

    while (getline(file, line))
    {
        vector<string> words;
        tokenizestring(line, '\t', words);
        if (!(find(sortedDiseases.begin(), sortedDiseases.end(), (words[0])) != sortedDiseases.end()))
            sortedDiseases.push_back(words[0]);
    }

    file.close();
    sort(sortedDiseases.begin(), sortedDiseases.end(), compareFunction);
    cout << "\n\n";

    for (int i = 0; i < sortedDiseases.size(); i++)
    {

        cout << i + 1 << ". " << sortedDiseases[i] << endl;
    }
    cout << "\n\n";
}

void locationWithDisease(string disease)
{
    //get a location that has a certain disease
    ifstream file;
    file.open("diseases.txt");
    string line;
    string key = "";
    bool found = false;
    vector<string> foundLocations;

    while (getline(file, line))
    {
        vector<string> words;
        tokenizestring(line, '\t', words);

        cout << "\n";

        if (toLowercase(words[0]) == disease)
        {
            found = true;
            if (!(find(foundLocations.begin(), foundLocations.end(), (words[1])) != foundLocations.end()))
                foundLocations.push_back(words[1]);
        }
    }

    if (found == false)
    {
        cout << "No location with this disease!";
    }
    else
    {
        sort(foundLocations.begin(), foundLocations.end(), compareFunction);
        for (int i = 0; i < foundLocations.size(); i++)
        {

            cout << i + 1 << ". " << foundLocations[i] << endl;
        }
    }

    cout << "\n\n";
    file.close();
}

void totalCasesOfDisease(string disease)
{
    //total cases of a disease in all districts
    ifstream file;
    file.open("diseases.txt");
    string line;
    int total = 0;
    while (getline(file, line))
    {
        vector<string> words;
        tokenizestring(line, '\t', words);

        if (toLowercase(words[0]) == disease)
        {
            total += stoi(words[2]);
        }
    }
    cout << "Total cases of '" << disease << "'= " << total << endl;
    file.close();
}

void casesOfDiseaseInLocaion(string disease, string location)
{
    //get all cases of a disease in a certain location
    ifstream file;
    file.open("diseases.txt");
    string line;

    int total = 0;

    while (getline(file, line))
    {
        vector<string> words;
        tokenizestring(line, '\t', words);
        cout << "\n";

        if (toLowercase(words[0]) == disease && toLowercase(words[1]) == location)
        {
            total += stoi(words[2]);
        }
    }
    cout << "Cases of " << disease << " in " << location << " are :" << total << endl;

    cout << "\n\n";
    file.close();
}

void helpMenu()
{

    cout << "===============================================================================" << endl;
    cout << "\t\t\t\t\tHELP MENU\t\t\t" << endl;
    cout << "================================================================================\n\n"
         << endl;
    cout << "add <Location> \t\t\t\t\t: Add location" << endl;
    cout << "delete <Location> \t\t\t\t: Delete an existing location" << endl;
    cout << "record <Location> <disease> <cases> \t\t: Record a disease and its cases" << endl;
    cout << "list locations \t\t\t\t\t: List all existing locations" << endl;
    cout << "list diseases \t\t\t\t\t: List all existing Diseases in locations" << endl;
    cout << "where <disease> \t\t\t\t: Find where disease exists" << endl;
    cout << "cases <location> <disease> \t\t\t: Find cases of a disease in a location" << endl;
    cout << "cases <disease> \t\t\t\t: Find total cases of a given disease" << endl;
    cout << "help \t\t\t\t\t\t: Prints user manual" << endl;
    cout << "Exit \t\t\t\t\t\t: Exits the program" << endl;
    cout << "\n\n";
}

bool isNumber(std::string x){
    //a method to check if input is a number
    std::regex e ("^-?\\d+");
    if (std::regex_match (x,e)) return true;
    else return false;
}

void processCommand(string cmd)
{
    //a function that processes user command and act accordingly
    system("clear");
    vector<string> command;
    tokenizestring(cmd, ' ', command);
    command[0] = toLowercase(command[0]);

    if (command[0] == "add"){
        if(isNumber(command[1]))
        cout<<"Input must be a string"<<endl;

        else{
        createLocation(command[1]);
        }
    }

    else if (command[0] == "delete")
        deleteLocation(command[1]);
    else if (command[0] == "record"){
        if(!isNumber(command[3])){
            cout<<"Input must be a number"<<endl;
        }else{
            createDisease(command[2], command[1], stoi(command[3]));
        }
    }
        
    else if (toLowercase(cmd) == "list locations")
        listLocations();
    else if (toLowercase(cmd) == "list diseases")
        listDiseasesInExistinglocation();
    else if (command[0] == "where")
        locationWithDisease(toLowercase(command[1]));
    else if (command.size() == 3 && command[0] == "cases")
        casesOfDiseaseInLocaion(toLowercase(command[2]), toLowercase(command[1]));
    else if (command[0] == "cases" && command.size() == 2)
        totalCasesOfDisease(toLowercase(command[1]));
    else if (cmd == "help")
        helpMenu();
    else if (cmd == "exit")
    {
        cout << "Thank you for using the program.\n";
        exit(0);
    }
    else
        cout << "Invalid command!\n\n";
}

int main()
{
    string option;
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    cout << "======================================================================\n"
            << endl;
    cout << "*\t\t Welcome to Disease Cases Reporting system!\t\t*\n"
            << endl;
    cout << "*  ******************************************************************** *\n"
            << endl;
    cout << "*\n"
            << endl;
    cout << "* It is developed by Blessing Hirwa as practical *\n\n";
    cout << "* evaluatin for end of Year 3 *" << endl;
    cout << "====================================================\n\n"
            << endl;
    cout << "Starting time: " << ctime(&end_time) << endl;
    cout
        << "Need a help? Type help then press Enter key.  " << endl;

    do
    {
        cout << "\n\n";

        cout << "Console >: ";
        getline(cin, option);

        if(cin.fail()){
            cout<<"Invalid input detected, use correct inputs only!";
        }else{

        processCommand(option);
        }


    } while (option != "exit");
    ;
    return 0;
}