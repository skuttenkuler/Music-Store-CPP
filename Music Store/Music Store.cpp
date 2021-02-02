// Music Store.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <mysql.h>
#include <iostream>
//global
int querystate;

MYSQL* connection;
MYSQL_ROW row;
MYSQL_RES* res;

// connect and get db response

class db_connection
{
public:
    static void DBConnect()
    {
        
        connection = mysql_init(0);
        connection = mysql_real_connect(connection, "localhost", "root", "password", "music_store", 3306, NULL, 0);
        //check for connection to server
        if (connection)
        {
            puts("Connection complete");
        }
        else
        {
            puts("Connection to db failed..");
        }
    
    }
};
//functions

void ShowAllItems();

int main()
{
    system("cls");
    system("title Music Store");
    system("color 0f");
   
    //connection method
    db_connection::DBConnect();

    //user variables
    int menuChoice = 0;
    char exitChar;


    std::cout << "Welcome to the Music Store" << std::endl;
    std::cout << "Main Menu" << std::endl;
    std::cout << "1. See All Music." << std::endl;
    std::cout << "2. Exit." << std::endl;
    std::cin >> menuChoice;


    //switch case for choice
    switch (menuChoice)
    {
    case 1:
        ShowAllItems();
        break;
    case 2:
    ExitProgram:
        //check for input
        std::cout << "Quit? (y/N)";
        std::cin >> exitChar;
        if (exitChar == 'y' || exitChar == 'Y')
        {
            return 0;
        }
        //if not clear screen and return to main()
        else if (exitChar == 'n' || exitChar == 'N')
        {
            system("CLS");
            main();
        }
        else
        {
            std::cout << "Please enter valid input" << std::endl;
            goto ExitProgram;
        }
        break;
    default:
        std::cout << "Please Enter Valid Entry." << std::endl;
        system("pause");
        system("CLS");
        main();
        break;

    }
    return 0;



}


//Music Store TO-DO's

//show all items in stock
void ShowAllItems()
{
    system("CLS");

    char choice;

    //set query string 
    std::string query = "SELECT * FROM music_store_inventory";
    const char* q = query.c_str();
    querystate = mysql_query(connection, q);
    if (!querystate)
    {
        res = mysql_store_result(connection);
        while (row = mysql_fetch_row(res))
        {
            printf("id: %s, artist: %s, album: %s\n", row[0], row[1], row[2]);
        }
    }
    else
    {
        std::cout << "Query Issue" << mysql_errno(connection) << std::endl;
    }
    // Exit back to menu
    std::cout << "Press 'm' to return to main menu." << std::endl;
    std::cout << "Press anyother key to exit." << std::endl;
    std::cin >> choice;
    if (choice == 'm' || choice == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }

}
//show only items in stock
//show items sold
//search catalog
//Add new item
//Remove item
//edit item
//create customer order


