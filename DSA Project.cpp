// DSA Project.cpp : This file contains the 'main' function.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
int go = 0;
void welcome();
void userchoose(int& user);
void admins();
void student();
void sDashboard();
void aDashboard();
void findMostBorrowedBook(const char* filename);
struct Node
{
    std::string bookName;
    int count;
    Node* next;

    Node(const std::string& name) : bookName(name), count(1), next(NULL) {}
};
class BookList
{
private:
    Node* head;

public:
    BookList() : head(NULL) {}
    ~BookList()
    {
        Node* current = head;
        while (current != NULL)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    void addOrUpdateBook(const std::string& name)
    {
        Node* current = head;
        Node* previous = NULL;
        // Search for the book in the list
        while (current != NULL && current->bookName != name)
        {
            previous = current;
            current = current->next;
        }
        if (current != NULL)
        {
            // Book found, update count
            current->count++;
        }
        else
        {
            // Book not found, create new node
            Node* newNode = new Node(name);
            if (previous == NULL)
            {
                // Insert at head
                head = newNode;
            }
            else
            {
                // Insert after previous node
                previous->next = newNode;
            }
        }
    }
    string findMostBorrowedBook() const
    {
        Node* current = head;
        string mostBorrowed;
        int maxCount = 0;
        while (current != NULL)
        {
            if (current->count > maxCount)
            {
                maxCount = current->count;
                mostBorrowed = current->bookName;
            }
            current = current->next;
        }
        return mostBorrowed;
    }
};
struct TreeNode
{
    string name;
    int id;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string n, int i) : name(n), id(i), left(NULL), right(NULL) {}
};
class BinarySearchTree
{
private:
    TreeNode* root;

    void insert(TreeNode*& node, const string& name, int id)
    {
        if (node == NULL)
        {
            node = new TreeNode(name, id);
        }
        else if (name < node->name)
        {
            insert(node->left, name, id);
        }
        else
        {
            insert(node->right, name, id);
        }
    }

    TreeNode* search(TreeNode* node, const string& name) const
    {
        if (node == NULL)
        {
            return NULL;
        }

        // Increment global variable go for each node visited
        go++;

        if (node->name == name)
        {
            return node;
        }
        else if (name < node->name)
        {
            return search(node->left, name);
        }
        else
        {
            return search(node->right, name);
        }
    }

    void deleteTree(TreeNode* node)
    {
        if (node != NULL)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(NULL) {}

    ~BinarySearchTree()
    {
        deleteTree(root);
    }

    void insert(const string& name, int id)
    {
        insert(root, name, id);
    }

    TreeNode* search(const string& name) const
    {
        go = 0; // Reset go before starting search
        return search(root, name);
    }
};
void admin(const string& adminname, bool& usernameFound, int& correctId)
{
    BinarySearchTree bst;
    ifstream inFile("admin.txt");
    if (!inFile)
    {
        cerr << "Unable to open file Test.txt";
        exit(1);
    }
    string name;
    int id;
    while (inFile >> name >> id)
    {
        bst.insert(name, id);
    }
    inFile.close();
    TreeNode* foundNode = bst.search(adminname);
    if (foundNode != NULL)
    {
        usernameFound = true;
        correctId = foundNode->id;
    }
}
void student(const string& studname, bool& usernameFound, int& correctId)
{
    BinarySearchTree bst;
    ifstream inFile("student.txt");
    if (!inFile)
    {
        cerr << "Unable to open file Test2.txt";
        exit(1);
    }
    string name;
    int id;
    while (inFile >> name >> id)
    {
        bst.insert(name, id);
    }
    inFile.close();
    TreeNode* foundNode = bst.search(studname);
    if (foundNode != NULL)
    {
        usernameFound = true;
        correctId = foundNode->id;
    }
}
void findMostBorrowedBook(const char* filename)
{
    BookList bookList;
    ifstream file(filename);
    if (!file)
    {
        cerr << "Unable to open file." << endl;
        return;
    }
    string book;
    while (getline(file, book))
    {
        bookList.addOrUpdateBook(book);
    }
    file.close();
    string mostBorrowedBook = bookList.findMostBorrowedBook();
    if (!mostBorrowedBook.empty())
    {
        cout << "Most borrowed book: " << mostBorrowedBook << endl;
    }
    else
    {
        cout << "No books found." << endl;
    }
}
int main()
{
    welcome();
    int duration = 5; // duration in seconds
    bool usernameFound = false;
    int choice = 0;
    userchoose(choice);
    if (choice == 1)
    {
        string adminname;
        int correctId;
        cout << "Enter admin name: ";
        cin >> adminname;
        admin(adminname, usernameFound, correctId);
        while (!usernameFound)
        {
            cout << "Username not found. Try again." << endl;
            cout << "Enter admin name: ";
            cin >> adminname;
            admin(adminname, usernameFound, correctId);
        }
        int enteredId;
        cout << "Enter admin password: ";
        cin >> enteredId;
        while (enteredId != correctId)
        {
            cout << "Incorrect password. Try again." << endl;
            cout << "Enter admin password: ";
            cin >> enteredId;
        }
        cout << "Login successful." << endl;
        aDashboard();
    }
    else if (choice == 2)
    {
        string studname;
        int correctId;
        cout << "Enter student name: ";
        cin >> studname;
        student(studname, usernameFound, correctId);
        while (!usernameFound)
        {
            cout << "Username not found. Try again." << endl;
            cout << "Enter student name: ";
            cin >> studname;
            student(studname, usernameFound, correctId);
        }
        int enteredId;
        cout << "Enter student password: ";
        cin >> enteredId;
        while (enteredId != correctId)
        {
            cout << "Incorrect password. Try again." << endl;
            cout << "Enter student password: ";
            cin >> enteredId;
        }
        cout << "Login successful." << endl;
        //cout << "value of go is: " << go << endl;
        sDashboard();
    }
    return 0;
}
void welcome()
{
    cout << setw(65) << "SMART LIBRARY SYSTEM" << '\n'; // Corrected typo "SYSRTEM"
}
void userchoose(int& user)
{
    cout << "Press 1 for admin login." << endl << "Press 2 for student login." << endl;
    cin >> user;
    while (user != 1 && user != 2)
    {
        cout << "Please enter either 1 or 2" << endl;
        cin >> user;
    }
}
void show()
{
    cout << "Your borrowed books are:" << endl;
    ifstream iread("borrowed.txt");
    if (!iread.is_open())
    {
        cerr << "Error opening borrowed.txt for reading." << endl;
        return;
    }
    string line;
    int currentLine = 1;
    while (getline(iread, line))
    {
        cout << "Line " << currentLine << ": " << line << endl; // Debug output
        if (currentLine == go)
        {
            cout << "Borrowed book: " << line << endl;
            break;
        }
        currentLine++;
    }
    if (currentLine != go)
    {
        cout << "No borrowed book found for line number " << go << endl; // Debug output
    }
    iread.close();
}
void update(string& take)
{
    ifstream iread("borrowed.txt");
    ofstream iwrite("temp.txt");
    string line;
    int currentLine = 1;

    if (!iread.is_open())
    {
        cerr << "Error opening borrowed.txt for reading." << endl;
        return;
    }
    if (!iwrite.is_open())
    {
        cerr << "Error opening temp.txt for writing." << endl;
        return;
    }

    while (getline(iread, line))
    {
        if (currentLine == go)
        {
            cout << "Updating line: " << line << " with " << take << endl;
            line += ", " + take;
        }
        iwrite << line << endl;
        currentLine++;
    }

    iread.close();
    iwrite.close();

    if (remove("borrowed.txt") != 0)
    {
        cerr << "Error removing borrowed.txt" << endl;
        return;
    }
    if (rename("temp.txt", "borrowed.txt") != 0)
    {
        cerr << "Error renaming temp.txt to borrowed.txt" << endl;
        return;
    }

    show();
}
void append()
{
    string book;
    cout << "Enter the name of the book you want to append: ";
    cin.ignore(); // Clear any newline characters from the input buffer
    getline(cin, book); // Use getline to allow for spaces in book names

    ofstream iwrite("borrowed.txt", ios::app);
    if (!iwrite.is_open())
    {
        cerr << "Error opening borrowed.txt for appending." << endl;
        return;
    }
    iwrite << book << endl;
    iwrite.close();

    // Output the borrowed book to the console
    cout << "Book Borrowed: " << book << endl;


}
void sDashboard()
{
    cout << "Press 1 to show borrowed books." << endl << "Press 2 to borrow book." << endl << "Press 3 to find the most popular book" << endl;
    int choose = 0;
    cin >> choose;
    if (choose == 1)
    {
        show();
    }
    if (choose == 2)
    {
        cout << "Available Book Genres:";
        string select;
        ifstream file("books.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file: books.txt" << endl;
            return;
        }
        string line;
        vector<string> genres;
        // Read the first line for genres
        if (getline(file, line))
        {
            size_t pos = 0;
            while ((pos = line.find('\t')) != string::npos)
            {
                genres.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            // Add the last genre
            if (!line.empty())
            {
                genres.push_back(line);
            }
        }
        // Display genres
        for (size_t i = 0; i < genres.size(); ++i)
        {
            cout << genres[i] << '\t';
        }
        cout << endl << "Select Book Genre: ";
        cin >> select;
        // Find the index of the selected genre
        int genreIndex = -1;
        for (size_t i = 0; i < genres.size(); ++i)
        {
            if (genres[i] == select)
            {
                genreIndex = i;
                break;
            }
        }
        if (genreIndex == -1)
        {
            cerr << "Genre not found." << endl;
            file.close();
            return;
        }

        cout << "Available Books:" << endl;
        cout << "-----------------------------------" << endl;
        // Read the rest of the file for books
        while (getline(file, line))
        {
            size_t pos = 0;
            for (int i = 0; i <= genreIndex; ++i)
            {
                pos = line.find('\t');
                if (i == genreIndex)
                {
                    string bookTitle = (pos == string::npos) ? line : line.substr(0, pos);
                    cout << "| " << setw(30) << left << bookTitle << " |" << endl;
                }
                if (pos != string::npos)
                {
                    line.erase(0, pos + 1);
                }
            }
        }
        cout << "-----------------------------------" << endl;
        cout << "Which book do you want to borrow: ";
        string take;
        cin >> take;
        update(take);
        cout << "Book Borrowed!" << endl;
        file.close();
        show();
    }
    else if (choose == 3)
    {

        findMostBorrowedBook("borrowed.txt");
    }
}
void aDashboard()
{
    // Admin dashboard for adding new books, updating details, and marking books as lost or damaged
    cout << "Press 1 to add new books." << endl
        << "Press 2 to update details." << endl
        << "Press 3 to view popular books of the week." << endl;
    int choose = 0;
    cin >> choose;

    if (choose == 1)
    {
        // Display available genres
        cout << "Available Book Genres: ";
        ifstream file("books.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file: books.txt" << endl;
            return;
        }

        string line;
        vector<string> genres;
        // Read the first line for genres
        if (getline(file, line))
        {
            size_t pos = 0;
            while ((pos = line.find('\t')) != string::npos)
            {
                genres.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            // Add the last genre
            if (!line.empty())
            {
                genres.push_back(line);
            }
        }

        // Display genres
        for (size_t i = 0; i < genres.size(); ++i)
        {
            cout << genres[i] << '\t';
        }
        cout << "\nEnter the Genre: ";
        string genre;
        cin >> genre;

        // Find the index of the selected genre
        int genreIndex = -1;
        for (size_t i = 0; i < genres.size(); ++i)
        {
            if (genres[i] == genre)
            {
                genreIndex = i;
                break;
            }
        }
        if (genreIndex == -1)
        {
            cerr << "Genre not found." << endl;
            file.close();
            return;
        }

        file.close();

        // Append the new book to the file
        ofstream addBookFile("books.txt", ios::app);
        if (!addBookFile.is_open())
        {
            cerr << "Error opening file for appending." << endl;
            return;
        }

        cout << "Enter book name: ";
        string book;
        cin.ignore(); // Clear any newline characters from the input buffer
        getline(cin, book); // Use getline to allow for spaces in book names

        addBookFile << book << endl;
        addBookFile.close();

        cout << "New book added successfully." << endl;

        // Display updated list of books
        cout << "Updated Book List:" << endl;
        ifstream updatedFile("books.txt");
        if (!updatedFile.is_open())
        {
            cerr << "Error opening file: books.txt" << endl;
            return;
        }

        while (getline(updatedFile, line))
        {
            cout << line << endl;
        }
        updatedFile.close();
    }
    else if (choose == 2)
    {
        cout << "Press 1 to change name of admin" << endl << "Press 2 to change password of admin" << endl;
        int pick = 0;
        cin >> pick;
        if (pick == 1)
        {
            cout << "Enter current admin name to change: ";
            string currentName;
            cin >> currentName;
            cout << "Enter new admin name: ";
            string newName;
            cin >> newName;

            ifstream inFile("admin.txt");
            ofstream outFile("temp.txt");
            string name;
            int id;
            bool nameFound = false;

            if (!inFile.is_open() || !outFile.is_open())
            {
                cerr << "Error opening file." << endl;
                return;
            }

            while (inFile >> name >> id)
            {
                if (name == currentName)
                {
                    name = newName;
                    nameFound = true;
                }
                outFile << name << " " << id << endl;
            }

            inFile.close();
            outFile.close();

            // Copy contents from temp.txt back to admin.txt
            ifstream tempFile("temp.txt");
            ofstream originalFile("admin.txt");

            if (!tempFile.is_open() || !originalFile.is_open())
            {
                cerr << "Error opening file for copying." << endl;
                return;
            }

            string tempLine;
            while (getline(tempFile, tempLine))
            {
                originalFile << tempLine << endl;
            }

            tempFile.close();
            originalFile.close();

            if (nameFound)
            {
                cout << "Admin name changed successfully." << endl;
            }
            else
            {
                cout << "Admin name not found." << endl;
            }
        }
        else if (pick == 2)
        {
            cout << "Enter current admin name: ";
            string adminName;
            cin >> adminName;
            cout << "Enter current admin password to change: ";
            int currentPass;
            cin >> currentPass;
            cout << "Enter new admin password: ";
            int newPass;
            cin >> newPass;

            ifstream inFile("admin.txt");
            ofstream outFile("temp.txt");
            string name;
            int id;
            bool passFound = false;

            if (!inFile.is_open() || !outFile.is_open())
            {
                cerr << "Error opening file." << endl;
                return;
            }

            while (inFile >> name >> id)
            {
                if (name == adminName && id == currentPass)
                {
                    id = newPass;
                    passFound = true;
                }
                outFile << name << " " << id << endl;
            }

            inFile.close();
            outFile.close();

            // Copy contents from temp.txt back to admin.txt
            ifstream tempFile("temp.txt");
            ofstream originalFile("admin.txt");

            if (!tempFile.is_open() || !originalFile.is_open())
            {
                cerr << "Error opening file for copying." << endl;
                return;
            }

            string tempLine;
            while (getline(tempFile, tempLine))
            {
                originalFile << tempLine << endl;
            }

            tempFile.close();
            originalFile.close();

            if (passFound)
            {
                cout << "Admin password changed successfully." << endl;
            }
            else
            {
                cout << "Admin password not found." << endl;
            }
        }
    }
    else if (choose == 3)
    {
        findMostBorrowedBook("borrowed.txt");
    }
}
