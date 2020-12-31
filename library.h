#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>



class Lib
{
    public:
	std::vector<std::string> input_table_name();
	void create_new_file(std::ofstream& dbwrite, std::string fileName);
        std::unordered_map<std::string,std::vector<std::string>> read_DBFiles();
	void write_DBFiles(std::unordered_map<std::string,std::vector<std::string>>& dbmap);
	std::unordered_map<std::string,std::vector<std::string>> createTable(std::unordered_map<std::string,std::vector<std::string>>& dbmap);
	std::unordered_map<std::string,std::vector<std::string>> dropTable(std::unordered_map<std::string,std::vector<std::string>>& dbmap);
        std::unordered_map<std::string,std::vector<std::string>> insertRecords(std::unordered_map<std::string,std::vector<std::string>>& dbmap);
	std::unordered_map<std::string,std::vector<int>> removeRecords(std::unordered_map<std::string,std::vector<std::string>>& dbmap);
	void displayTable(std::unordered_map<std::string,std::vector<std::string>>& dbmap);
	void showSchema(std::unordered_map<std::string,std::vector<std::string>>& dbmap);
	std::string clean_colname(std::string astr);
	bool check_table_existence(std::string filename);
	void create_legal_colname(std::string& colname_row, std::string& col_name);
	char one_more(std::string act, std::string name);
	std::string create_header(std::vector<std::string> col_names, std::vector<int> col_lens);
	void append_table(std::ofstream& myfile, std::string file_name, std::string& colname_row);
        std::vector<int> get_header_colens(std::unordered_map<std::string,std::vector<std::string>>& dbmap,std::string& table_name);
	std::vector<std::string> get_table_colname(std::string& file_name);
	std::vector<std::string> keep_input_records(std::vector<std::string>& colnames, std::vector<int>& header_lens, bool insert);
	int get_col_lens(std::string col_name);
	std::vector<std::string> read_table_records(std::string file_name);
	void write_to_table(std::string file_name, std::vector<std::string>& table_records);
	void remove_tombstone(std::unordered_map<std::string, std::vector<int>> dbremove);

};

#endif
