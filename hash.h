#include <iostream>
#include <string>
#include <vector>
#include <list>

//create hash data structure
class HashTable {
	int capacity;
public:
	HashTable(int c);
	void insertItem(std::string key, unsigned long int data);
	void deleteItem(std::string key);
	void displayTable(int size);
	//void clear();
	//~HashTable();

private:
	std::list<std::pair<std::string, unsigned long int>>* items;
	//pointer to a list containing keys
	long long hashFunction(std::string);
};

HashTable::HashTable(int c) {
	this->capacity = c;
	items = new std::list<std::pair<std::string, unsigned long int>>[capacity];
}

void HashTable::insertItem(std::string key, unsigned long int data) {
	int index = hashFunction(key);
	items[index].push_back(make_pair(key, data));
	//std::cout << "Inserting " << key << " at index " << index << std::endl;
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
		//std::cout << "Deleting " << key << " at index " << index << std::endl;
	}
}

long long HashTable::hashFunction(std::string name) {
	int p = 31;
	long long m = 1572869; //1e9 + 9;
	unsigned long long int hash = 0;
	unsigned long long int power = 1;
	for (char c : name) {
		hash = (hash + (c - 'a' + 1) * power) % m;
		power = (power * p) % m;
	}
	while (hash >= capacity)
	{
		hash -= capacity;
	}
	return hash;
}

void HashTable::displayTable(int size) {

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

/*
void HashTable::clear()
{
	auto it = items->begin();
	for (int i = 0; i < items->size(); i++)
	{
		while (!items[i].empty())
		{
			items[i].pop_back();
		}
	}
}
*/