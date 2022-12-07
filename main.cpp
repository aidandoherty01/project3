#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <chrono>
#include <map>
#include "hash.h"
using namespace std;
using namespace std::chrono;

int readFile(vector<string>& names, string file);
void generatePhoneNumbers(unordered_set<unsigned long int>& numbers, int max);
unsigned long int createMap(vector<pair<string, unsigned long int>>& phoneBook, map<string, unsigned long int>& newMap);
void menu();

int main()
{
	cout << "Please wait while data is being generated.\n" << endl;

    int i;
    //reading files
    vector<string> firstNames, lastNames;
    string fileName1 = "first-names.csv";
    string fileName2 = "last-names.csv";
    //if either file fails to read, throw an error and stop the program
    if (!readFile(firstNames, fileName1) || !readFile(lastNames, fileName2))
    {
        cout << "Error: File could not be opened" << endl;
        return -1;
    }

    //generating random unique phonenumbers (10 digit integers)
    int max = (firstNames.size() < lastNames.size()) ? firstNames.size() : lastNames.size();
    unordered_set<unsigned long int> numbers;
    generatePhoneNumbers(numbers, max);

    //creating phone book
    vector<pair<string, unsigned long int>> phoneBook;
    string fullName;
    auto iter = numbers.begin();
    //creates an entry for each name and phonenumber pairing
    for (i = 0; i < max; i++)
    {
        //concatenates the first and last names together
        fullName = firstNames[i] + " " + lastNames[i];
        //stores our new contact in the phoneBook vector
        phoneBook.push_back(make_pair(fullName, *iter++));
        //cout << phoneBook[i].first << ": " << phoneBook[i].second << endl;
    }

	//END GENERATION OF DATA

	//create HashTable object to import data and perform operations
	HashTable myTable = HashTable(1000000);

	//create Map object
	map<string, unsigned long int> myMap;

	//variable initialization
	int option;
	string userName;
	unsigned long int userNumber;
	unsigned long long int ht_insert_all = 0;
	unsigned long long int map_insert_all = 0;

	//user interface
	cout << "*Welcome to the Hash Table vs. Map Comparison*\n"
		"- The purpose of this program is to compare the time complexity for various operations of these two data structures, specifically for storing user data\n"
		<< endl;
	menu();
	cout << "Option: ";
	cin >> option;
	cout << endl;

	//handle user input

	while (option != 0) {
		cin.ignore();
		switch (option)
		{
			case 1:
			{
				//import all data and record time it takes

				//insert data into hash table
				auto exeBegin = high_resolution_clock::now();
				for (int i = 0; i < max; i++) {
					myTable.insertItem(phoneBook.at(i).first, phoneBook.at(i).second);
				}
				auto exeEnd = high_resolution_clock::now();
				auto executionTime = duration_cast<milliseconds>(exeEnd - exeBegin);
				ht_insert_all = executionTime.count();
				cout << "Hash Table Insertion Complete" << endl;

				//insert data into map
				exeBegin = high_resolution_clock::now();
				for (auto x : phoneBook) {
					myMap.insert(x);
				}
				exeEnd = high_resolution_clock::now();
				executionTime = duration_cast<milliseconds>(exeEnd - exeBegin);
				map_insert_all = executionTime.count();
				cout << "Map Insertion Complete" << endl;

				break;
			}
			case 2:
			{
				//import user data into hash table 
				cout << "Enter the name to be added" << endl;
				getline(cin, userName);
				cin.ignore();
				cout << "Enter the number to be added" << endl;
				cin >> userNumber;
				//call insert function
				myTable.insertItem(userName, userNumber);
				cout << "Succesfully inserted data into Hash Table" << endl;

				break;
			}
			case 3:
			{
				//import user data into Map
				cout << "Enter the name to be added" << std::endl;
				getline(cin, userName);
				cin.ignore();
				cout << "Enter the number to be added" << std::endl;
				cin >> userNumber;
				//call insert function
				myMap.insert(make_pair(userName, userNumber));
				cout << "Succesfully inserted data into Hash Table" << endl;

				break;
			}
			case 4:
			{
				//delete user data from hash table
				cout << "Enter the name to be deleted" << endl;
				getline(cin, userName);
				cin.ignore();
				//call delete function
				myTable.deleteItem(userName);

				break;
			}
			case 5:
			{
				//delete user data from map
				cout << "Enter the name to be deleted" << endl;
				getline(cin, userName);
				cin.ignore();
				//error handling
				if (myMap.find(userName) == myMap.end())
				{
					cout << "Error: " << userName << " not found in Map" << endl;
				}
				//call delete function
				else
				{
					myMap.erase(userName);
					cout << "Succesfully deleted data from Map" << endl;
				}

				break;
			}
			case 6:
			{
				//print from time complexity analysis

				//INSERTION
				unsigned long int ht_insert_time = 0;
				unsigned long int map_insert_time = 0;

				//Inserting item into hash table
				auto exeBegin = high_resolution_clock::now();
				myTable.insertItem("John", 899220000);
				auto exeEnd = high_resolution_clock::now();
				auto executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin);
				ht_insert_time = executionTime.count();

				//Inserting item into map
				exeBegin = high_resolution_clock::now();
				myMap.insert(make_pair("John", 899220000));
				exeEnd = high_resolution_clock::now();
				executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin);
				map_insert_time = executionTime.count();

				//DELETION
				unsigned long int ht_delete_time = 0;
				unsigned long int map_delete_time = 0;

				//Deleting item from the hash table
				exeBegin = high_resolution_clock::now();
				myTable.deleteItem("John");
				exeEnd = high_resolution_clock::now();
				executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin);
				ht_delete_time = executionTime.count();

				//Deleting item from the map
				exeBegin = high_resolution_clock::now();
				myMap.erase("John");
				exeEnd = high_resolution_clock::now();
				executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin);
				map_delete_time = executionTime.count();

				//print all findings
				cout << "Time Complexity of Hash Table and Map Operations:\n\n"
				"================Insertion================\n\n"
				"Hash Table:\n"
				"\t- Inserting one item: " << ht_insert_time << " nanoseconds\n"
				"\t- Inserting all items: " << ht_insert_all << " milliseconds\n"
				"Map:\n"
				"\t- Inserting one item: " << map_insert_time << " nanoseconds\n"
				"\t- Inserting all items: " << map_insert_all << " milliseconds\n\n"
				"================Deletion================\n\n"
				"Hash Table:\n"
				"\t- Deleting one item: " << ht_delete_time << " nanoseconds\n"
				"Map:\n"
				"\t- Deleting one item: " << map_delete_time << " nanoseconds" << endl;


				break;
			}
			case 7:
			{
				//display hash table
				myTable.displayTable(max);

				break;
			}
			case 8:
			{
				//display map
				cout << "Ordered Map Data:" << endl;
				for (auto iter = myMap.begin(); iter != myMap.end(); iter++) {
					cout << iter->first << " " << iter->second << endl;
				}

				break;
			}
			case 9:
			{
				//reprint options	
				menu();

				break;
			}
			default:
			{
				//invalid input
				cout << "Error: Invalid Input" << endl;
				menu();
			}
		}
		cin.ignore();
		cout << "\nEnter another option or press 0 to quit (9 to redisplay options)\n\n";
		cout << "Option: ";
		cin >> option;
		cout << endl;
	}

	return 0;
}

int readFile(vector<string>& names, string file)
{
    //takes in a csv file and parses through, storing names in a string vector
    ifstream fileNames(file);
    string inputName;
    //if the file fails to open, throw a flag
    if (!fileNames.is_open())
        return 0;
    getline(fileNames, inputName);
    //read through the file, line by line, storing names until the end is reached
    while (!fileNames.eof())
    {
        names.push_back(inputName);
        //cout << inputName << endl;
        getline(fileNames, inputName);
    }
    fileNames.close();
    return 1;
}

void generatePhoneNumbers(unordered_set<unsigned long int>& numbers, int max)
{
	/* unsigned long is used because :
	* - the phone number 999-999-9999 wouldn't fit in a 4 byte data type
	* - phone numbers can't be negative */

	//arbitrary numbers based off florida area codes
	long long int phoneMin = 2490000000;
	long long int phoneMax = 9590000000;
	//random generation setup
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<long long int> distr(llround(phoneMin), llround(phoneMax));
	unsigned long int temp;
	//generates a unique random phone number each time 
	for (int i = 0; i < max; i++)
	{
		temp = distr(gen);
		//if the number already exists in our set, generate a new one until a unique number is generated
		while (numbers.find(temp) != numbers.end())
		{
			temp = distr(gen);
		}
		numbers.insert(temp);
		//cout << temp << endl;
	}
}

unsigned long int createMap(vector<pair<string, unsigned long int>>& phoneBook, map<string, unsigned long int>& newMap)
{
	auto exeBegin = chrono::high_resolution_clock::now();
    for (int i = 0; i < phoneBook.size(); i++)
    {
        newMap[phoneBook[i].first] = phoneBook[i].second;
    }
    auto exeEnd = chrono::high_resolution_clock::now();
    auto executionTime = chrono::duration_cast<chrono::nanoseconds>(exeEnd - exeBegin);
    cout << executionTime.count() << " nanoseconds" << endl;
    return executionTime.count();
}

void menu()
{
	cout << "Select an option below\n"
		"Press 1 to import all data into both structures\n"
		"Press 2 to import your own data into a Hash Table\n"
		"Press 3 to import your own data into a Map\n"
		"Press 4 to delete data from a Hash Table\n"
		"Press 5 to delete data from a Map\n"
		"Press 6 to print time copmlexity anslysis of data structure operations\n"
		"Press 7 to display the Hash Table\n"
		"Press 8 to display the Map\n"
		"Press 9 to redisplay options\n"
		"Press 0 to quit\n" << endl;
}
