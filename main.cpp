#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <random>
#include <unordered_set>
#include <map>

int readFile(vector<string>& names, string file);
void generatePhoneNumbers(unordered_set<unsigned long int>& numbers, int max);

using namespace std::chrono;

class HashTable {
	int size;
public:
	HashTable(int c);
	void insertItem(std::string, int data);
	void deleteItem(std::string);
	void displayTable();
	
private:
	std::list<std::pair<std::string, int>>* items;
	//pointer to a list containing keys
	long long hashFunction(std::string);
};

HashTable::HashTable(int c) {
	this->size = c;
	items = new std::list<std::pair<std::string, int>>[size];
}

void HashTable::insertItem(std::string key, int data) {
	int index = hashFunction(key);
	items[index].push_back(std::pair<std::string, int>(key, data));
	std::cout << "Inserting " << key << " at index " << index << std::endl;
}

void HashTable::deleteItem(std::string key) {
	int index = hashFunction(key);
	auto it = items[index].begin();
	for (it = items[index].begin(); it != items[index].end(); it++) {
		if (it->first == key) {
			break;
		}
	}

	if (it != items[index].end()) {
		items[index].erase(it);
		std::cout << "Deleting " << key << " at index " << index << std::endl;
	}

}

long long HashTable::hashFunction(std::string name) {
	//implement polynomial rolling function
	//TODO - math overflow
	//FIX - decreased size of m
	int p = 31;
	long long m = 12289; //1e9 + 9;
	long long hash = 0;
	long long power = 1;
	for (char c : name) {
		hash = (hash + (c - 'a' + 1) * power) % m;
		power = (power * p) % m;
	}
	std::cout << "hash = " << hash << std::endl;
	return hash;
	/*
	long hash = 0;
	for (char c : name) {
		hash += c;
	}
	return hash;*/
}

void HashTable::displayTable() {
	std::cout << "Hash Table Data:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (items[i].size() != 0) {
			std::cout << "items[" << i << "]";
			for (auto x : items[i])
				std::cout << " --> " << x.first << " " << x.second;
			std::cout << std::endl;
		}
		
	}
}

void hashData() {
	//import data from main 
	std::vector<std::string> data; //placeholder
	//call insert function of HashTable object for each data pair
	//TODO: create HashTable object in main
	for (std::string n : data) {
		//TODO: insert pair item for each line of data
	}

}

using namespace std;
int main()
{
	//generate and import data
	
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


	//testing
	/*myTable.insertItem("blue", 35);
	myTable.insertItem("dogs", 18);
	myTable.insertItem("apple", 20);
	myTable.displayTable();
	myTable.deleteItem("apple");
	myTable.displayTable();
	
	//testing chaining
	myTable.insertItem("hello", 300);
	myTable.insertItem("hello", 900);
	myTable.displayTable();*/


	//user interface
	std::cout << "Welcome to the Hash Table vs. Map Comparison" << std::endl;
	std::cout << "The purpose of this program is to compare the time complexity for various operations of these two data structures, specifically for storing user data" << std::endl;
	std::cout << endl;

	int option = 0;
	std::cout << "Select an option below" << std::endl;
	std::cout << "Press 1 to import all data into both structures" << std::endl;
	std::cout << "Press 2 to import your own data into a Hash Table" << std::endl;
	std::cout << "Press 3 to import your own data into a Map" << std::endl;
	std::cout << "Press 4 to delete data from a Hash Table" << std::endl;
	std::cout << "Press 5 to delete data from a Map" << std::endl;
	std::cout << "Press 6 to print time copmlexity anslysis of data structure operations" << std::endl;
	std::cout << "Press 7 to display the Hash Table" << std::endl;
	std::cout << "Press 8 to display the Map" << std::endl;
	std::cout << "Press 9 to redisplay options" << std::endl;
	std::cout << "Press 0 to quit" << std::endl;
	cin >> option;

	//FIX - IF SPACE IN INSERTED NAME, GIVES ERROR

	//handle user input
	int ht_insert_all = 0;
	int map_insert_all = 0;
	while (option != 0) {
		if (option > 9) {
			std::cout << "Invalid option, please try again" << std::endl;
			
		}
		else if (option == 1) {
			//import all data 
			//and record time it takes

			auto exeBegin = high_resolution_clock::now(); 
			//INSERT ALL DATA INTO HASH TABLE HERE
			auto exeEnd = high_resolution_clock::now(); 
			auto executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin); 
			ht_insert_all = executionTime.count();

			exeBegin = high_resolution_clock::now();
			//INSERT ALL DATA INTO MAP HERE
			exeEnd = high_resolution_clock::now();
			executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin);
			map_insert_all = executionTime.count();


		}
		else if (option == 2) {
			//import own data into hash table 
			std::string userName;
			int userNumber;
			std::cout << "Enter the name to be added" << std::endl;
			cin >> userName;			
			std::cout << "Enter the number to be added" << std::endl;
			cin >> userNumber;
			//call insert function
			myTable.insertItem(userName, userNumber);

		}
		else if (option == 3) {
			//import own data into Map
			std::string userName;
			int userNumber;
			std::cout << "Enter the name to be added" << std::endl;
			std::getline(std::cin, userName);
			//cin >> userName;
			std::cout << "Enter the number to be added" << std::endl;
			cin >> userNumber;
			//call insert function
		}
		else if (option == 4) {
			//delete own from hash table
			std::string userName;
			std::cout << "Enter the name to be deleted" << std::endl;
			cin >> userName;
			//call delete function
			myTable.deleteItem(userName);
		}
		else if (option == 5) {
			//delete from map
			std::string userName;
			std::cout << "Enter the name to be deleted" << std::endl;
			cin >> userName;
			//call delete function
		}
		else if (option == 6) {
			//print from time complexity analysis

			//TODO - decide exactly which operations to test

			//insert
				//i'm thinking we record how long it takes for when we insert ALL data, and then
				//calculate here for one piece of data

			int ht_insert_time = 0;
			int map_insert_time = 0;

			auto exeBegin = high_resolution_clock::now(); //place before function execution
			myTable.insertItem("John", 899220000);
			auto exeEnd = high_resolution_clock::now(); //place after function execution
			auto executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin); // place after exeEnd
			ht_insert_time = executionTime.count();

			exeBegin = high_resolution_clock::now();
			//INSERT DATA ITEM INTO MAP
			exeEnd = high_resolution_clock::now();
			executionTime = duration_cast<nanoseconds>(exeEnd - exeBegin);
			map_insert_time = executionTime.count();

			std::cout << executionTime.count() << " nanoseconds" << endl; //Output

			//delete
				//need to search for something we know is in data structures to delete 
				//or multiple items to show a difference in time complexity

			//find? need to write hash table function for this if so

			//print all findings

		}
		else if (option == 7) {
			//display hash table
			myTable.displayTable();
		}
		else if (option == 8) {
			//display map
		}
		else if (option == 9) {
			//reprint options	
			std::cout << "Select an option below" << std::endl;
			std::cout << "Press 1 to import all data into both structures" << std::endl;
			std::cout << "Press 2 to import your own data into a Hash Table" << std::endl;
			std::cout << "Press 3 to import your own data into a Map" << std::endl;
			std::cout << "Press 4 to delete data from a Hash Table" << std::endl;
			std::cout << "Press 5 to delete data from a Map" << std::endl;
			std::cout << "Press 6 to print time copmlexity anslysis of data structure operations" << std::endl;
			std::cout << "Press 7 to display the Hash Table" << std::endl;
			std::cout << "Press 8 to display the Map" << std::endl;
			std::cout << "Press 9 to redisplay options" << std::endl;
			std::cout << "Press 0 to quit" << std::endl;
		}
		std::cout << "Enter another option or press 0 to quit: " << std::endl;
		cin >> option;
	}



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
