/*
* Group 73 - Project 3	//Nothing here is final, please feel free to suggest any changes or improvements
* Goal: Compare the Performance of Hash Tables and Maps
* 
* Questions to Answer:	//these are more general questions, we can brainstorm some common real world challenges
* - Time Complexity of Basic Operations
* - How does performance change based on specific data types as well as size of the sample
* - Which data structure is best applied to certain scenarios
*		- Is one better at handling more complex data types, like structs/classes
* 
* Basic Implementation:	//rough draft
* 
* main()
* - menu based system that generates our random set of data based on user input,
*   which could include the size of our data set and the data types to be used
*		- Templates could be useful here?
* - after user input, the we could time the storage/filling of each container and compare the times
*		- We should be wary of space and memory consumption
			(as well as how intense the operations are on the computer?)
*			(((hard to mesure due to differing computer hardware??)))
*		- potentially write helper functions for the creation of our storage containers
*				- especially for the hash function
* - after storage, we can compare functionalities like searching and deletion
* 
* helper functions:
* - createMap()?
*		- should we just stick with STL map for consistency
*		- it's a red-black tree which shouldn't violate the project restrictions
* - createHashTable()
*		- we should settle on what implementation of a hash table we'll use
* - hashFunction()
*		- noted below, there could be interesting challenges with this function
* 
* //NOTE: should we test multiple hash functions/table sizes/load factors?
* //could be interseting to see how certains hashing functions handle various data types
*/