// Music Store.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <mysql.h>
#include <string>
#include <iostream>
#include <sstream>
//global
int querystate;

MYSQL mysql, *connection;
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
void RemoveItem();
void EditItem();

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
    std::cout << "3. Add Item to Inventory." << std::endl;
    std::cout << "4. Delete an Item." << std::endl;
    //std::cout << "4. Edit Iventory." << std::endl;
    //std::cout << "5. Display Items Sold." << std::endl;
    //std::cout << "6. Search Catalog." << std::endl;
    //std::cout << "7. Create Customer Order." << std::endl;
    //std::cout << "8. Exit." << std::endl;
    
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
        RemoveItem();
        break;
    case 5:
        EditItem();
        break;
    case 6:
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
            printf("id: %s \t, artist: %s \t, album: %s \t, genre: %s \t, price: %s \t, quantity: %s \t \n", row[0], row[1], row[2], row[3], row[4], row[5]);
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
                printf("id: %s \t, artist: %s \t, album: %s \t, genre: %s \t, price: %s \t, quantity: %s \t \n", row[0], row[1], row[2], row[3], row[4], row[5]);
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
//Add new item
void AddItem() 
{
    //initialize
    mysql_init(&mysql);
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
     //set query string 
    std::string query = "INSERT INTO music_store_table(artist,album,genre,price,quantity) VALUES ('" + artist + "','" + album + "','" + genre + "','price','quantity')";

    const char* q = query.c_str();
    querystate = mysql_query(connection, q);
    if (!querystate)
    {
        std::cout << "Successfully added item in to database" << std::endl;
    }
    else
    {
        std::cout << query << std::endl;
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

//Remove item
void RemoveItem()
{
    ////clear screen
    system("CLS");

    char choice;
    int item_id;
    //set list of strings
    std::string items[2000];
    //id index
    int id_index;
    //boolean check
    bool has_exception = false;
    bool not_in_db = false;

    std::cout << "Welcome To Music Store" << std::endl;
    std::cout << "Remove Item Menu" << std::endl ;
    //set query string
    std::string query = "SELECT id, artist, album FROM music_store_table";
    const char* q = query.c_str();
    querystate = mysql_query(connection, q);
    if (!querystate)
    {
        res = mysql_store_result(connection);
        //display items for user
        std::cout << "ID\tARTIST\tALBUM\n" << std::endl;
        while (row = mysql_fetch_row(res))
        {
            std::cout << row[0] << "\t" << row[1] << "\t" << row[2] << std::endl;
            //assign id index to list with items from id row, then increment
            items[id_index] = row[0];
            id_index++;
        }
    }
    else
    {
        std::cout << "Query Issue" << mysql_errno(connection) << std::endl;
    }
    //try function to select get user input of id, if error catch and throw error
    try
    {
        std::cout << std::endl;
        std::cout << "Enter Item ID:" << std::endl;
        std::cin >> item_id;
        std::cout << std::endl;
    }
    catch(std::exception e)
    {
        std::cout << "Please Enter Valid Selection." << std::endl;
        has_exception = true;
        goto ExitProgram;
    }

    if (has_exception == false)
    {
        std::stringstream stream_id;
        std::string str_id;
        stream_id << item_id;
        stream_id >> str_id;
        //loop through table and find id, if found set true, else break
        for (int i = 0; i < id_index; i++)
        {
            if (str_id != items[i])
            {
                not_in_db = true;
            }
            else
            {
                not_in_db = false;
                break;
            }
        }
        //if id found
        if (not_in_db == false)
        {
            std::string delete_query = "DELETE FROM music_store_table WHERE id = '" + str_id + "'";
            const char* qd = delete_query.c_str();
            querystate = mysql_query(connection, qd);

            if (!querystate)
            {
                std::cout << "Deletion Successful!" << std::endl;

            }
            else
            {
                std::cout << "Deletion Failed." << mysql_errno(connection) << std::endl;
            }
        }
        else
        {
            std::cout << "Item Not Found." << std::endl;
        }
    }
    // Exit back to menu
    ExitProgram:
    std::cout << "Press 'm' to return to main menu." << std::endl;
    std::cout << "Press 'd' to delete another item." << std::endl;
    std::cout << "Press anyother key to exit." << std::endl;
    std::cin >> choice;
    if (choice == 'm' || choice == 'M')
    {
        main();
    }
    else if (choice == 'd' || choice == 'D')
    {
        RemoveItem();
    }
    else
    {
        exit(0);
    }
}
//edit item
void EditItem()
{
    system("cls");

    //variables `artist`,`album`,`genre`,`price`,`quantity`
    std::string artist = "";
    std::string album = "";
    std::string genre = "";
    float price;
    int quantity;
    //music_store_table variables
    std::string ms_id = "";
    std::string ms_artist = "";
    std::string ms_album = "";
    std::string ms_genre = "";
    std::string ms_price = "";
    std::string ms_quantity = "";
    //list, user choice, exceptions, loop vars
    std::string items[2000];
    char choice;
    bool has_exception = false;
    bool not_in_db = false;
    int item_id;
    int id_index = 0;

    std::cout << "Welcome To Music Store" << std::endl;
    std::cout << "Edit Item Menu" << std::endl;

    querystate = mysql_query(connection, "SELECT id, artist, album FROM music_store_table");
    if (!querystate)
    {
        res = mysql_store_result(connection);
        std::cout << "ID\tARTIST\tALBUM\n" << std::endl;
        while (row = mysql_fetch_row(res))
        {
            std::cout << row[0] << "\t" << row[1] << "\t" << row[2] << std::endl;
            //assign id index to list with items from id row, then increment
            items[id_index] = row[0];
            id_index++;
        }
    }
    else 
    {
        std::cout << "Query Error!" << mysql_errno(connection) << std::endl;

    }
    //try function to select get user input of id, if error catch and throw error
    try
    {
        std::cout << std::endl;
        std::cout << "Enter Item ID:" << std::endl;
        std::cin >> item_id;
        std::cout << std::endl;
    }
    catch (std::exception e)
    {
        std::cout << "Please Enter Valid Selection." << std::endl;
        has_exception = true;
        goto ExitProgram;
    }
    if (has_exception == false)
    {
        std::stringstream stream_id;
        std::string str_id;
        stream_id << item_id;
        stream_id >> str_id;

        //loop to find index id
        for (int i = 0; i < id_index; i++)
        {
            if (str_id != items[i])
            {
                not_in_db = true;
            }
            else
            {
                not_in_db = false;
                break;
            }
        }
        //if id found
        if (not_in_db == false)
        {
            std::string find_id_query = "SELECT * FROM music_store_table WHERE id = '" + str_id + "'";
            const char* fq = find_id_query.c_str();
            querystate = mysql_query(connection, fq);

            if (!querystate)
            {
                res = mysql_store_result(connection);
                std::cout << std::endl;
                while (row = mysql_fetch_row(res))
                {
                    std::cout << "ID: " << row[0] << "\nArtist: " << row[1] << "\nAlbum: " << row[2] << "\nGenre: " << row[3] << "\nPrice: " << row[4] << "\nQuantity: " << row[5] << std::endl;
                    ms_id = row[0];
                    ms_artist = row[1];
                    ms_album = row[2];
                    ms_genre = row[3];
                    ms_price = row[4];
                    ms_quantity = row[5];
                }
            }
            else
            {
                std::cout << "Edit Failed.." << mysql_errno(connection) << std::endl;
            }
        }
        std::cin.ignore(1, '\n');
        std::cout << "Enter Artist (x to not change): ";
        std::getline(std::cin, artist);
        if (artist == "x")
        {
            artist = ms_artist;
        }
        std::cout << "Enter Album (x to not change): ";
        std::getline(std::cin, album);
        if (album == "x")
        {
            album = ms_album;
        }
        std::cout << "Enter Genre (x to not change): ";
        std::getline(std::cin, genre);
        if (genre == "x")
        {
            genre = ms_genre;
        }
        std::cout << "Enter Price (x to not change): ";
        std::cin >> price;
  
        if (price_x = x)
        {
            price = ms_price;
        }
        std::cout << "Enter Quantity (x to not change): ";
        std::cin >> quantity;
        
        if (quantity == "x")
        {
            quantity = ms_quantity;
        }

        //update query string
        std::string update_query = "UPDATE music_store_table SET artist = '" + artist + "', album = '" + album + "', genre = '" + genre + "', price = 'price', quantity = 'quantity')";
        const char* uq = update_query.c_str();
        querystate = mysql_query(coneection, uq);

        if (!querystate)
        {
            std::cout << "Update Successful!" std::endl;
        }
        else
        {
            std::cout << "Update Failed.." << mysql_errno(connection) << std::endl;
        }
    }
    // Exit back to menu
    ExitProgram:
    std::cout << "Press 'm' to return to main menu." << std::endl;
    std::cout << "Press 'e' to edit another item." << std::endl;
    std::cout << "Press anyother key to exit." << std::endl;
    std::cin >> choice;
    if (choice == 'm' || choice == 'M')
    {
        main();
    }
    else if (choice == 'e' || choice == 'E')
    {
        EditItem();
    }
    else
    {
        exit(0);
    }

}
//show items sold
//search catalog
//create customer order


