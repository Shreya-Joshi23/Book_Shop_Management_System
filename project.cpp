#include <bits/stdc++.h>
using namespace std;

int ascii = 178;
char ch = ascii;

// This is main menu of my Book management system.
class menu
{
public:
    void mainmenu();
    void bookmenu();
    void issuebook();
};

// MAIN MENU
void menu::mainmenu()
{
    for (int i = 0; i < 26; i++)
    {
        cout << ch;
    }
    cout << " Main menu ";
    for (int i = 0; i < 26; i++)
    {
        cout << ch;
    }
    cout << endl
         << endl;
    cout << "1.Book menu\n"
         << "2.Buy book\n"
         << "3.Exit" << endl;
}

// BOOKMENU
void menu::bookmenu()
{
    for (int i = 0; i < 26; i++)
    {
        cout << ch;
    }
    cout << " Book menu ";
    for (int i = 0; i < 26; i++)
    {
        cout << ch;
    }
    cout << endl;
    cout << "1.New entry\n"
         << "2.Search entry\n"
         << "3.Update entry\n"
         << "4.Delete entry\n"
         << "5.View all books\n"
         << "6.Go back to previous menu" << endl;
}

// BOOK DATA STRUCTURE
class Bookdata
{
public:
    int bookid;
    char title[30];
    char author[30];
    float price;
    int copies;
};

class book
{
public:
    void inputdetails();
    void updatedetails();
    void searchdetails();
    void deletedetails();
    void viewallbookdetails();
};

void book::inputdetails()
{
    fstream ofp;
    ofp.open("bookdatabase.bin", ios::out | ios::binary | ios::app);
    if (!ofp)
    {
        cout << "Unable to open the file";
        return;
    }
    else
    {
        Bookdata book;
        cout << "Enter book id";
        cin >> book.bookid;
        cout << "Enter book title";
        cin >> book.title;
        cout << "Enter author's name";
        cin >> book.author;
        cout << "Enter book price";
        cin >> book.price;
        cout << "Enter the number of copies";
        cin >> book.copies;

        ofp.write((char *)&book, sizeof(Bookdata));
        cout << "Book added to bookstore.....";
        cin.get();
        cin.get();
        ofp.close();
    }
}

void book::searchdetails()
{
    system("cls");
    fstream file;
    file.open("bookdatabase.bin", ios::in | ios::binary);

    if (!file)
    {
        cout << "Unable to open the file";
        cin.get();
        cin.get();
        return;
    }

    Bookdata book;
    char title[30];

    cout << "Enter the title of the book you want to search";
    cin >> title;

    while (file.read((char *)&book, sizeof(Bookdata)))
    {
        if (strcmp(book.title, title) == 0)
        {
            cout << "Book found in the bookshop" << endl;
            cout << "Book title:" << book.title << endl;
            cout << "Book author:" << book.author << endl;
            cout << "Book price:" << book.price << endl;
            cout << "Book copies" << book.copies << endl;
            cin.get();
            cin.get();
            return;
        }
    }
    cout << "Book not present in the bookshop";
    file.close();
    cin.get();
    cin.get();
    return;
}

void book::updatedetails()
{
    system("cls");
    fstream file;
    Bookdata book;
    bool flag = 0;

    file.open("bookdatabase.bin", ios::in | ios::binary | ios::out | ios::ate);
    file.seekg(0, ios::beg);

    if (!file)
    {
        cout << "Unable to open the file";
    }
    else
    {
        cout << "Enter the title of the book you want to update";
        char title[25];
        cin >> title;
        while (file.read((char *)&book, sizeof(Bookdata)))
        {
            if (strcmp(book.title, title) == 0)
            {
                int position = (-1) * sizeof(Bookdata);
                file.seekp(position, ios::cur);
                cout << "Enter new book id" << endl;
                cin >> book.bookid;
                cout << "Enter new book title" << endl;
                cin >> book.title;
                cout << "Enter new book author" << endl;
                cin >> book.author;
                cout << "Enter new book price" << endl;
                cin >> book.price;
                cout << "Enter new number of copies" << endl;
                cin >> book.copies;
                flag = 1;
                file.write((char *)&book, sizeof(Bookdata));
            }
        }

        if (flag == 1)
        {
            cout << "Record successfully updated";
            cin.get();
            cin.get();
        }
        else
        {
            cout << "Record not found";
            cin.get();
            cin.get();
        }
    }
    return;
}

void book::deletedetails()
{
    fstream file, temp;
    file.open("bookdatabase.bin", ios::in | ios::binary);
    temp.open("temp.bin", ios::out | ios::binary);

    char title[25];
    Bookdata book;
    int flag = 0;
    cout << "Enter the title of the book you want to delete";
    cin >> title;

    while (file.read((char *)&book, sizeof(Bookdata)))
    {
        if (strcmp(book.title, title) == 0)
        {
            flag++;
            continue;
        }
        else
        {
            temp.write((char *)&book, sizeof(Bookdata));
        }
    }
    file.close();
    temp.close();
    remove("bookdatabase.bin");
    rename("temp.bin", "bookdatabase.bin");

    if (flag == 1)
    {
        cout << "Record successfully deleted";
    }
    else
    {
        cout << "Record not found";
    }

    cin.get();
    cin.get();
    return;
}

void book::viewallbookdetails()
{
    fstream file;
    file.open("bookdatabase.bin", ios::in | ios::binary);
    Bookdata book;
    int choice = 1;

    while (file.read((char *)&book, sizeof(Bookdata)) && choice)
    {
        system("cls");
        cout << "Book id:" << book.bookid << endl;
        cout << "Book title:" << book.title << endl;
        cout << "Book author name:" << book.author << endl;
        cout << "Book price:" << book.price << endl;
        cout << "Book copies present:" << book.copies << endl;

        cout << "Press 1 to view next book else press 0";
        cin >> choice;
    }
    cin.get();
    cin.get();
    return;
}

void menu::issuebook()
{

    Bookdata book;
    fstream file;
    bool flag = 0;
    file.open("bookdatabase.bin", ios::in | ios::out | ios::binary | ios::ate);
    file.seekg(0, ios::beg);

    char title[25];
    int copies;
    int price;
    cout << "Enter the title of the book you want to buy";
    cin >> title;
    cout << "Enter the number of book you want to buy";
    cin >> copies;

    while (file.read((char *)&book, sizeof(Bookdata)))
    {
        if (strcmp(book.title, title) == 0)
        {

            int position = (-1) * sizeof(Bookdata);
            file.seekp(position, ios::cur);

            if (book.copies >= copies)
            {
                book.copies -= copies;
                price = book.price * copies;
                file.write((char *)&book, sizeof(Bookdata));
                return;
            }
            else if (book.copies < copies || book.copies == 0)
            {
                cout << "Do not have sufficient copies of book";
                cin.get();
                cin.get();
                return;
            }
            flag = 1;
        }
    }

    if (flag == 1)
    {
        cout << "Book bought at price:" << price;
        cin.get();
        cin.get();
    }
    else
    {
        cout << "Book not found in the bookstore...";
        cin.get();
        cin.get();
    }

    return;
}

int main()
{
    menu m;
    int quit = 0;
    int choice;
    int c1;

    while (!quit)
    {
        system("cls");
        m.mainmenu();
        cout << "Enter your choice";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            m.bookmenu();
            cout << "Enter your choice";
            cin >> c1;
            book b;
            switch (c1)
            {
            case 1:
                b.inputdetails();
                break;

            case 2:
                b.searchdetails();
                break;

            case 3:
                b.updatedetails();
                break;

            case 4:
                b.deletedetails();
                break;

            case 5:
                b.viewallbookdetails();
                break;

            case 6:
                break;

            default:
                cout << "Wrong input received!" << endl;
            }
            break;

        case 2:
            m.issuebook();
            break;

        case 3:
            quit++;
            break;

        default:
            cout << "Please enter correct input!";
            cin >> choice;
        }
    }
    return 0;
}
