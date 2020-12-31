#include "library.h"
#include <iostream>

int main()
{
        char choice;
	Lib lib;
	std::unordered_map<std::string, std::vector<std::string>> dbmap;
	dbmap = lib.read_DBFiles();
	while (true)
	{
		std::cout << "+-----------------------------------+" << std::endl;
		std::cout << "|Main menu (enter a number below)   |" << std::endl;
		std::cout << "|-----------------------------------|" << std::endl;
		std::cout << "|0. Exit                            |" << std::endl;
		std::cout << "|1. Create Table                    |" << std::endl;
		std::cout << "|2. Drop Table                      |" << std::endl;
		std::cout << "|3. Insert Records                  |" << std::endl;
		std::cout << "|4. Delete Records                  |" << std::endl;
		std::cout << "|5. Display Records                 |" << std::endl;
		std::cout << "|6. Show All Schema                 |" << std::endl;
		std::cout << "+-----------------------------------+" << std::endl;

		std::cin >> choice;
		switch (choice)
		{
		case '0':
			
			std::cout << "purging begins..." << std::endl;
			lib.write_DBFiles(dbmap);
			std::cout << "purge file is done!" << std::endl;
			return 0;
		case '1':
			dbmap = lib.createTable(dbmap);
			lib.write_DBFiles(dbmap);
			continue;
		case '2':
			dbmap = lib.dropTable(dbmap);
			lib.write_DBFiles(dbmap);
			continue;
		case '3':
			dbmap = lib.insertRecords(dbmap);
			continue;
		case '4':
			lib.removeRecords(dbmap);
			continue;
		case '5':
			lib.displayTable(dbmap);
			continue;
		case '6':
			lib.showSchema(dbmap);
			continue;
		default:
			std::cout << "Error: invalid! please input an integer(0,1,2,3,4,5,6)" << std::endl;
			continue;
		}
	}
	return 0;
}
