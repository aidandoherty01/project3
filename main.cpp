#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
using namespace std;

int readFile(vector<string>& names, string file);
void generatePhoneNumbers(unordered_set<unsigned long int>& numbers, int max);

int main()
{
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