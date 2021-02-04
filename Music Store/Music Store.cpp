// Music Store.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <mysql.h>
#include <string>
#include <iostream>
#include <sstream>
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
void ShowInStock();
void AddItem();

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
    std::cout << "1. See Inventory." << std::endl;
    std::cout << "2. Currently Stocked Items." << std::endl;
    std::cout << "3. Add Item to Inventory" << std::endl;
    std::cout << "4. Exit." << std::endl;
    std::cin >> menuChoice;


    //switch case for choice
    switch (menuChoice)
    {
    case 1:
        ShowAllItems();
        break;
    case 2:
        ShowInStock();
        break;
    case 3:
        AddItem();
        break;
    case 4:
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

    std::cout << "Welcome To Music Store" << std::endl;
    std::cout << "Here's our inventory." << std::endl;

    //set query string 
    std::string query = "SELECT * FROM music_store_table";
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

//show only items in stocks
void ShowInStock()
{
    system("CLS");

    char choice;

    std::cout << "Welcome To Music Store" << std::endl;
    std::cout << "Here's what's in stock." << std::endl;

    //set query string 
    std::string query = "SELECT * FROM music_store_table";
    const char* q = query.c_str();
    querystate = mysql_query(connection, q);
    if (!querystate)
    {
        res = mysql_store_result(connection);
        while (row = mysql_fetch_row(res))
        {
            if (atoi(row[5]) > 0)
            {
                printf("id: %s, artist: %s, album: %s\n", row[0], row[1], row[2]);
            }
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

void AddItem() 
{
    system("CLS");
    //set variables for artist, album, genre, price, quantity
    std::string artist = "";
    std::string album = "";
    std::string genre = "";
    float price = 0.0;
    int quantity = 0;
    char choice;



    std::cout << "Welcome To Music Store" << std::endl;
    std::cout << "Here's what's in stock." << std::endl;
    
    //get inputs
    std::cin.ignore(1, '\n');
    std::cout << "Enter Artist:" << std::endl;
    std::getline(std::cin, artist);
    std::cout << "Enter Album:" << std::endl;
    std::getline(std::cin, album);
    std::cout << "Enter Genre:" << std::endl;
    std::getline(std::cin, genre);
    std::cout << "Price:" << std::endl;
    std::cin >> price;
    std::cout << "Quantity:" << std::endl;
    std::cin >> quantity;

 

    //query string
    std::stringstream ss;
       ss << "INSERT INTO * music_store_inventory(artist, ablum, genre, price, category) VALUES (" << artist << "," << album << "," << genre << "," << price << "," << quantity << ")";

    std::string add_query = ss.str();
    const char* q = add_query.c_str();
    querystate = mysql_query(connection, q);
    if (!querystate)
    {
        std::cout << "Successfully added item in to database" << std::endl;
    }
    else
    {
        std::cout << add_query << std::endl;
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
//Add new item
//Remove item
//edit item
//show items sold
//search catalog
//create customer order


