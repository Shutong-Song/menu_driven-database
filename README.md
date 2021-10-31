# A menu driven database

1. description: A simple menu driven database written in C++ 11. It support general database functionalities like create and drop tables, insert and delete records, and display records in a table.

2. A quick demo:
![demo](img/db.git)

3. how to run:
    - compile library.cpp and library_main.cpp
    - run the compiled executable

4. desgin structure:
    1. library.cpp and library.h are a library class contains all the functionalities for this database
    2. library_main.cpp is the main file that runs the database
    3. DBtables folder structure:
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/menu_driven-database.png?raw=true" width="500">
  

5. interface:
    - main interface: <br>
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/main.png?raw=true" width="350"> <br>
    - show all schema: <br>
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/showSchema.png?raw=true" width="300"> <br>
    - create table: <br>
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/createTable.png?raw=true" width="300"> <br>
    - insert records to table: <br>
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/insertRecords.png?raw=true" width="300"> <br>
    - delete records: <br>
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/deleteRecords.png?raw=true" width="300"> <br>
    - drop table: <br> 
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/dropTable.png?raw=true" width="300"> <br>
    - display records: <br>
    <img src="https://github.com/Shutong-Song/menu_driven-database/blob/media/displayRecords.png?raw=true" width="300"> <br>
6. functionalities:
    - column length constraint
    - error and exception handling: e.g. column length must be an integer; column variable cannot contain space or punctuation except underscore _
    - optimization: insert and delete are stored in a vector, will operate(write to table or delete from table) only once
