#include "library.h"



std::vector<std::string> Lib::input_table_name()
{
    std::vector<std::string> file;
    std::string table_name;
    std::cout << "enter table name: " << std::endl;
    std::cin >> table_name;
    std::string foldername = "DBtables/", filename = foldername + table_name + ".txt";
    file.push_back(filename);
    file.push_back(table_name);
    return file;
}


bool Lib::check_table_existence(std::string filename)
{
    //check if table is already exist, return true or false
    if(std::ifstream(filename))
	return true;
    else return false;
}

void Lib::create_new_file(std::ofstream& dbwrite, std::string fileName)
{
    dbwrite.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
    dbwrite.close();
}


std::string Lib::clean_colname(std::string astr)
{
    //input a string, output a string without puncutation but keep underscore _
    astr.erase(std::remove(astr.begin(), astr.end(),' '), astr.end());
    for(int i=0; i<astr.size(); i++)
    {
	if(ispunct(astr[i]) && astr[i] != '_')
	{
	    astr.erase(i,1);
	    i -= 1;
	}
    }
    return astr;
}


int Lib::get_col_lens(std::string col_name)
{
    //input is column name, output is an int variable: column length
    int col_length;
    do
    {
        std::cout << "enter column " << col_name << " length: " << std::endl;
        std::cin >> col_length;
        if (std::cin.fail())
        {
           std::cin.clear();
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
           std::cout << "Error: not a valid integer, enter length again: " << std::endl;
        }
	else
	{
	    break;
	}
    }while(true);
    return col_length;
}

std::unordered_map<std::string,std::vector<std::string>> Lib::read_DBFiles()
{
        //no input, output is dbmap variable contains table_name, header, # of rows for each table as a dictionary
        std::string fileName = "DBtables/DBFiles.txt";
        std::ifstream dbread(fileName);
        std::ofstream dbwrite;
        std::string table_name, header,num_of_rows;
	//std::vector<std::string> dbcontent;
        std::unordered_map<std::string, std::vector<std::string>> dbmap;
        if (check_table_existence(fileName))
        {
                while (dbread >> table_name >> header >> num_of_rows)
                {
			
                       dbmap[table_name].push_back(header);
		       dbmap[table_name].push_back(num_of_rows);	
                }
        }
        else
        {
                dbwrite.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
                dbwrite.close();
        }
        return dbmap;
}

void Lib::write_DBFiles(std::unordered_map<std::string,std::vector<std::string>>& dbmap)
{
	//input is the dbmap, output will write into the file
        std::ofstream writeDB("DBtables/DBFiles.txt");
        std::string db_meta;
	for (const auto& m : dbmap)
        {
                db_meta = m.first + " " + m.second[0] + " " + m.second[1];
                writeDB << db_meta << "\n";
        }

        writeDB.close();
}


void Lib::create_legal_colname(std::string& colname_row, std::string& col_name)
{
    //input a row of colname_row and col_name
    std::cout << "enter column name: " << std::endl;
    std::cin >> std::ws;
    std::getline(std::cin, col_name);
    int col_len1 = col_name.length();
    col_name = clean_colname(col_name);
    int col_len2 = col_name.length();
    if (col_len1 != col_len2)
       std::cout << "Warning: space or punctuation are not allowed in column names! automatically removed!" << std::endl;
    colname_row += col_name + " ";
}


char Lib::one_more(std::string act, std::string name)
{
    //input a string indicate the add item, output a char indicate yes or no
    char ch;
    std::cout << act + " one more " + name +  " ?(y/n)" << std::endl;
    std::cin >> ch;
    return ch;
}

std::string Lib::create_header(std::vector<std::string> col_names,std::vector<int> col_lens)
{
    //create a header in the format: colname1-len1-colname2-len2...
    std::string headerStr;
    for(int i=0; i<col_names.size(); i++)
    {
	headerStr += col_names[i] + "-" + std::to_string(col_lens[i]) + "-";
    }
    return headerStr;
}

void Lib::append_table(std::ofstream& myfile, std::string file_name, std::string& colname_row)
{
    //append data records into table
    myfile.open(file_name, std::ios_base::app);
    myfile << colname_row;
    myfile << "\n";
    myfile.close();
}

std::vector<int> Lib::get_header_colens(std::unordered_map<std::string,std::vector<std::string>>& dbmap,std::string& table_name)
{
	//extract column length from header information, output into a vector
	std::string header = dbmap[table_name][0];
	std::string buf;
        std::stringstream ss(header);
        std::vector<int> token;
        while(std::getline(ss,buf,'-'))
        {
            char *end;
            int i = strtol(buf.c_str(),&end,10); //convert string to long int: strtol,buf.c_str is a constant char pointer, &end is end ptr, 10 is int base
            if(*end == '\0')
            {
                token.push_back(std::stoi(buf));
            }
        }
        return token;
}

std::vector<std::string> Lib::get_table_colname(std::string& file_name)
{
    //input a file_path, output a vector contains all column names of this table
    std::string firstline, token;
    std::ifstream inputRecord;
    inputRecord.open(file_name);
    std::getline(inputRecord, firstline);
    std::istringstream ss(firstline);
    std::vector<std::string> colname;
    while (std::getline(ss, token, ' '))
    {
        colname.push_back(token);
    }
    inputRecord.close();
    return colname;
}

std::vector<std::string> Lib::keep_input_records(std::vector<std::string>& colnames, std::vector<int>& header_lens, bool iord)
{
    //input record one by one and save it as a string, output all saved records
    std::vector<std::string> all_records;
    char ch;
    do
    {
	std::string one_record;
	for (int i = 0; i < colnames.size(); i++)
        {
            std::string intoken;
            std::cout << "enter " << colnames[i] << ": " << std::endl;
            std::cin >> std::ws;
            std::getline(std::cin, intoken);
	    int col_len1 = intoken.length();
            if(col_len1 > header_lens[i])
                intoken = intoken.substr(0,header_lens[i]);
            intoken.erase(intoken.find_last_not_of(" \n\r\t") + 1);
            one_record += intoken + ",";
        }
        all_records.push_back(one_record);
	if(iord)
            ch = one_more("add","record");
	else
            ch = one_more("delete","record");
    }while(ch == 'y' || ch == 'Y');
    return all_records;
}





std::vector<std::string> Lib::read_table_records(std::string file_name)
{
    //input a file_path, output a vector contains all records of this table
    std::vector<std::string> table_records;
    std::ifstream inputRecord;
    inputRecord.open(file_name);
    int i = 0;
    for (std::string tLines; std::getline(inputRecord, tLines);)
    {
	if(i>=1)
            table_records.push_back(tLines);
	i++;
    }
    inputRecord.close();
    return table_records;
}

void Lib::write_to_table(std::string file_name, std::vector<std::string>& table_records)
{
        //input is the dbmap, output will write into the file
        std::ofstream writeDB(file_name);
        std::string db_meta;
        for (auto v: table_records)
        {
            writeDB << v << "\n";
        }

        writeDB.close();
}


void Lib::remove_tombstone(std::unordered_map<std::string, std::vector<int>> dbremove)
{
    std::vector<std::string> keys;
    std::string folder_name = "DBtables/";
    for(auto& k: dbremove)
        keys.push_back(k.first);
    for(int i=0; i<keys.size(); i++)
    {
        std::string file_name = folder_name + keys[i] + ".txt";
	std::string colname_row;
        std::vector<std::string> table_records = read_table_records(file_name);
	std::vector<std::string> colnames = get_table_colname(file_name);
	for(auto c:colnames)
	    colname_row += c + " ";
	std::vector<std::string> new_records;
	new_records.push_back(colname_row);
	int k=0;
        for(int j=0; j<table_records.size(); j++)
	{
	    if(j == dbremove[keys[i]][k])
	    {
		k++;
	    }
	    else
	    {
		new_records.push_back(table_records[j]);
	    }
	}
        write_to_table(file_name, new_records);
    }

}


std::unordered_map<std::string,std::vector<std::string>> Lib::createTable(std::unordered_map<std::string,std::vector<std::string>>& dbmap)
{
    //create a table if not exist, save the meta-data information into a global variable dbmap
    std::vector<std::string> file = input_table_name();
    std::string file_name = file[0], table_name = file[1];
    std::vector<int> col_lens;
    std::vector<std::string> col_names;
    std::ofstream myfile;
    std::string colname_row, col_name;
    char yesorno;
    if(check_table_existence(file_name))
    {
        std::cout << "Err:table already exists!" << std::endl;
    }
    else
    {
	create_new_file(myfile, file_name);
	std::cout << "table " << table_name << " is created successfully!" << std::endl;
	do
	{
	    create_legal_colname(colname_row,col_name);
	    col_names.push_back(col_name);
            col_lens.push_back(get_col_lens(col_name));
            yesorno = one_more("add","column");
	}while(yesorno == 'y' || yesorno == 'Y');
	std::string header = create_header(col_names,col_lens);
	dbmap[table_name].push_back(header);
	dbmap[table_name].push_back("0");
	append_table(myfile,file_name,colname_row);
    }
    return dbmap;
}

std::unordered_map<std::string,std::vector<std::string>> Lib::dropTable(std::unordered_map<std::string,std::vector<std::string>>& dbmap)
{
    //drop a table
    std::vector<std::string> file = input_table_name();
    std::string file_name = file[0], table_name = file[1];
    std::ofstream dropfile;
    if(check_table_existence(file_name))
    {
	std::cout << "are you sure to drop this table? (y/n)" << std::endl;
        std::string affirm;
        std::cin >> affirm;
        if (affirm == "y" || affirm == "Y")
        {
            dropfile.open(file_name);
            dropfile.close();
            if (remove(file_name.c_str()) != 0)
                std::perror("Table deletion failed!");
            else
	    {
                std::cout << "Table deleted successfully" << std::endl;
                dbmap.erase(table_name);
	    }
         }

    }
    else
    {
        std::cout << "Table not exists!" << std::endl;
    }
    return dbmap;
}


std::unordered_map<std::string,std::vector<std::string>> Lib::insertRecords(std::unordered_map<std::string,std::vector<std::string>>& dbmap)
{
    //insert records into a table, output the updated meta-data information
    std::vector<std::string> file = input_table_name();
    std::string file_name = file[0], table_name = file[1];
    std::ofstream myfile;
    if(check_table_existence(file_name))
    {
	std::vector<int> header_lens = get_header_colens(dbmap,table_name);
	std::vector<std::string> colnames = get_table_colname(file_name);
	bool insert=true;
	std::vector<std::string> all_records = keep_input_records(colnames,header_lens,insert);
	for(int i=0; i<all_records.size(); i++)
	{
	    append_table(myfile, file_name,all_records[i]);
	}
        dbmap[table_name][1] = std::to_string(std::stoi(dbmap[table_name][1]) + all_records.size());
    }
    else
    {
        std::cout << "No such table!" << std::endl;
    }
    return dbmap;
}

std::unordered_map<std::string,std::vector<int>> Lib::removeRecords(std::unordered_map<std::string,std::vector<std::string>>& dbmap)
{
    std::vector<std::string> file = input_table_name();
    std::unordered_map<std::string,std::vector<int>> dbremove;
    std::string file_name = file[0], table_name = file[1];
    if(check_table_existence(file_name))
    {
      std::vector<int> header_lens = get_header_colens(dbmap,table_name);
      std::vector<std::string> colnames = get_table_colname(file_name);
      bool insert=false;
      std::vector<std::string> all_records = keep_input_records(colnames,header_lens,insert);
      std::vector<std::string> table_records = read_table_records(file_name);
      for(int i=0; i<all_records.size(); i++)
      {   
	  if(std::stoi(dbmap[table_name][1]) > 0)
          {
          for(int j=0; j<table_records.size();j++)
	  {
	      if(all_records[i] == table_records[j])
	      {
		 dbremove[table_name].push_back(j);
		 dbmap[table_name][1] = std::to_string(std::stoi(dbmap[table_name][1])-1);
              }
	  }
          }
	  else
	  {
              break;
	  }
      }
     
    }
    else
    {
        std::cout << "table not exists!" << std::endl;
    }
    remove_tombstone(dbremove);
    return dbremove;
}

void Lib::displayTable(std::unordered_map<std::string,std::vector<std::string>>& dbmap)
{
    std::vector<std::string> file = input_table_name();
    std::unordered_map<std::string, std::vector<int>> dbremove;
    std::string file_name = file[0], table_name = file[1];
    if(check_table_existence(file_name))
    {
	std::vector<int> header_lens = get_header_colens(dbmap,table_name);
        std::vector<std::string> colnames = get_table_colname(file_name);
	int space=0;
	for(int k=0; k<colnames.size(); k++)
	{
	    if(header_lens[k] < colnames[k].size())
	        space += colnames[k].size();
	    else space += header_lens[k];
	}
        std::vector<std::string> table_records = read_table_records(file_name);
	std::cout << "+" << std::string(space+header_lens.size(), '-') << "--+" << std::endl;
        for (int i = 0; i < colnames.size(); i++)
        {
	    int space_len = ((header_lens[i] - int(colnames[i].length())>=0)?(header_lens[i]-int(colnames[i].length())+1):1);
            std::cout << "|" << colnames[i] << std::string(space_len,' ');
        }
        std::cout << "|" << std::endl;
        std::cout << "+" << std::string(space + header_lens.size(), '-') << "--+" << std::endl;
	
	std::vector<std::string> row_record;
        std::ifstream inputRecord;
        inputRecord.open(file_name);
        int i = 0;
        for (std::string tLines; std::getline(inputRecord, tLines);)
        {
            if(i>=1)
            {
		int m=0;
                std::istringstream ss(tLines);
		std::string token;
                while (std::getline(ss, token, ','))
                {
		    int space_len = header_lens[m]-int(colnames[m].size())>=0?header_lens[m] - int(token.size()) + 1:int(colnames[m].size())-int(token.size())+1;
                    std::cout << "|" << token << std::string(space_len,' ');
		    m++;  
                }
		std::cout << "|" << std::endl;
	    }
            i++;
        }
	std::cout << "+" << std::string(space + header_lens.size(), '-') << "--+" << std::endl;
        inputRecord.close();
    }
    else
    {
	std::cout << "No such table!" << std::endl;
    }

}


void Lib::showSchema(std::unordered_map<std::string,std::vector<std::string>>& dbmap)
{
    int space = 35;
    std::cout << "+" << std::string(space, '-') << "-+" << std::endl;
    std::cout << "|" << "table name" << std::string(5,' ') << "|" << "number of records" << std::string(3,' ') << "|" << std::endl;
    std::cout << "+" << std::string(space, '-') << "-+" << std::endl;
    for(auto k:dbmap)
    {
        std::cout << "|" << k.first << std::string(15-k.first.length(),' ') << "|" <<  k.second[1] << std::string(20-k.second[1].length(),' ') << "|" << std::endl;
    }
    std::cout << "+" << std::string(space, '-') << "-+" << std::endl;
}

