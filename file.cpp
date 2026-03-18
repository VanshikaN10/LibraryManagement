#include <bits/stdc++.h>
using namespace std;

// ── Book Structure ────────────────────────────────────────────────────────
struct Book {
    int    id;
    string title;
    string author;
    bool   isAvailable;
};

// ── File Names ────────────────────────────────────────────────────────────
const string BOOKS_FILE    = "books.txt";
const string BORROWED_FILE = "borrowed.txt";

// ══════════════════════════════════════════════════════════════════════════
//  FILE HANDLING
// ══════════════════════════════════════════════════════════════════════════

void saveBooksToFile(const vector<Book>& books) {
    ofstream file(BOOKS_FILE);
    for (const auto& b : books)
        file << b.id << "|" << b.title << "|" << b.author << "|" << b.isAvailable << "\n";
    file.close();
}

vector<Book> loadBooksFromFile() {
    vector<Book> books;
    ifstream file(BOOKS_FILE);
    if (!file.is_open()) return books;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Book b;
        getline(ss, token, '|'); b.id          = stoi(token);
        getline(ss, token, '|'); b.title        = token;
        getline(ss, token, '|'); b.author       = token;
        getline(ss, token, '|'); b.isAvailable  = stoi(token);
        books.push_back(b);
    }
    file.close();
    return books;
}

void logBorrowedRecord(const string& studentName, const Book& book, const string& action) {
    ofstream file(BORROWED_FILE, ios::app);
    file << action << " | Student: " << studentName
         << " | Book ID: " << book.id
         << " | Title: "   << book.title << "\n";
    file.close();
}

// ══════════════════════════════════════════════════════════════════════════
//  LIBRARIAN FUNCTIONS
// ══════════════════════════════════════════════════════════════════════════

void addBook(vector<Book>& books) {
    Book b;
    b.id          = books.empty() ? 1 : books.back().id + 1;
    b.isAvailable = true;

    cin.ignore();
    cout << "Enter book title  : "; getline(cin, b.title);
    cout << "Enter author name : "; getline(cin, b.author);

    books.push_back(b);
    saveBooksToFile(books);
    cout << "\n✅ Book added successfully! (ID: " << b.id << ")\n";
}

void deleteBook(vector<Book>& books) {
    int id;
    cout << "Enter Book ID to delete: "; cin >> id;

    auto it = find_if(books.begin(), books.end(),
                      [id](const Book& b){ return b.id == id; });

    if (it == books.end()) {
        cout << "\n❌ Book not found.\n";
        return;
    }
    if (!it->isAvailable) {
        cout << "\n❌ Cannot delete — book is currently borrowed.\n";
        return;
    }
    books.erase(it);
    saveBooksToFile(books);
    cout << "\n✅ Book deleted successfully!\n";
}

void searchBook(const vector<Book>& books) {
    cin.ignore();
    string keyword;
    cout << "Enter title or author to search: "; getline(cin, keyword);

    // case-insensitive search
    string kw = keyword;
    transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

    bool found = false;
    cout << "\n" << string(60, '-') << "\n";
    cout << left << setw(5) << "ID"
         << setw(30) << "Title"
         << setw(20) << "Author"
         << "Status\n";
    cout << string(60, '-') << "\n";

    for (const auto& b : books) {
        string t = b.title, a = b.author;
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        if (t.find(kw) != string::npos || a.find(kw) != string::npos) {
            cout << left << setw(5) << b.id
                 << setw(30) << b.title
                 << setw(20) << b.author
                 << (b.isAvailable ? "Available" : "Borrowed") << "\n";
            found = true;
        }
    }
    if (!found) cout << "No books found matching \"" << keyword << "\"\n";
    cout << string(60, '-') << "\n";
}

void viewAllBooks(const vector<Book>& books) {
    if (books.empty()) { cout << "\n📭 No books in library.\n"; return; }

    cout << "\n" << string(60, '-') << "\n";
    cout << left << setw(5) << "ID"
         << setw(30) << "Title"
         << setw(20) << "Author"
         << "Status\n";
    cout << string(60, '-') << "\n";
    for (const auto& b : books) {
        cout << left << setw(5) << b.id
             << setw(30) << b.title
             << setw(20) << b.author
             << (b.isAvailable ? "Available" : "Borrowed") << "\n";
    }
    cout << string(60, '-') << "\n";
    cout << "Total books: " << books.size() << "\n";
}

// ══════════════════════════════════════════════════════════════════════════
//  STUDENT FUNCTIONS
// ══════════════════════════════════════════════════════════════════════════

void borrowBook(vector<Book>& books) {
    int id;
    string studentName;
    cin.ignore();
    cout << "Enter your name  : "; getline(cin, studentName);
    cout << "Enter Book ID    : "; cin >> id;

    auto it = find_if(books.begin(), books.end(),
                      [id](const Book& b){ return b.id == id; });

    if (it == books.end()) {
        cout << "\n❌ Book not found.\n"; return;
    }
    if (!it->isAvailable) {
        cout << "\n❌ Sorry, this book is already borrowed.\n"; return;
    }

    it->isAvailable = false;
    saveBooksToFile(books);
    logBorrowedRecord(studentName, *it, "BORROWED");
    cout << "\n✅ You have successfully borrowed \"" << it->title << "\"!\n";
}

void returnBook(vector<Book>& books) {
    int id;
    string studentName;
    cin.ignore();
    cout << "Enter your name  : "; getline(cin, studentName);
    cout << "Enter Book ID    : "; cin >> id;

    auto it = find_if(books.begin(), books.end(),
                      [id](const Book& b){ return b.id == id; });

    if (it == books.end()) {
        cout << "\n❌ Book not found.\n"; return;
    }
    if (it->isAvailable) {
        cout << "\n❌ This book was not borrowed.\n"; return;
    }

    it->isAvailable = true;
    saveBooksToFile(books);
    logBorrowedRecord(studentName, *it, "RETURNED");
    cout << "\n✅ Book \"" << it->title << "\" returned successfully!\n";
}

// ══════════════════════════════════════════════════════════════════════════
//  MENUS
// ══════════════════════════════════════════════════════════════════════════

void librarianMenu(vector<Book>& books) {
    string password;
    cout << "Enter librarian password: "; cin >> password;
    if (password != "admin123") {
        cout << "\n❌ Wrong password!\n"; return;
    }

    int choice;
    do {
        cout << "\n╔══════════════════════════╗\n";
        cout << "║    LIBRARIAN MENU        ║\n";
        cout << "╠══════════════════════════╣\n";
        cout << "║ 1. Add Book              ║\n";
        cout << "║ 2. Delete Book           ║\n";
        cout << "║ 3. Search Book           ║\n";
        cout << "║ 4. View All Books        ║\n";
        cout << "║ 0. Back                  ║\n";
        cout << "╚══════════════════════════╝\n";
        cout << "Choice: "; cin >> choice;

        switch (choice) {
            case 1: addBook(books);        break;
            case 2: deleteBook(books);     break;
            case 3: searchBook(books);     break;
            case 4: viewAllBooks(books);   break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void studentMenu(vector<Book>& books) {
    int choice;
    do {
        cout << "\n╔══════════════════════════╗\n";
        cout << "║     STUDENT MENU         ║\n";
        cout << "╠══════════════════════════╣\n";
        cout << "║ 1. View All Books        ║\n";
        cout << "║ 2. Search Book           ║\n";
        cout << "║ 3. Borrow Book           ║\n";
        cout << "║ 4. Return Book           ║\n";
        cout << "║ 0. Back                  ║\n";
        cout << "╚══════════════════════════╝\n";
        cout << "Choice: "; cin >> choice;

        switch (choice) {
            case 1: viewAllBooks(books);   break;
            case 2: searchBook(books);     break;
            case 3: borrowBook(books);     break;
            case 4: returnBook(books);     break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

// ══════════════════════════════════════════════════════════════════════════
//  MAIN
// ══════════════════════════════════════════════════════════════════════════

int main() {
    vector<Book> books = loadBooksFromFile();

    int choice;
    do {
        cout << "\n╔══════════════════════════╗\n";
        cout << "║  LIBRARY MANAGEMENT SYS  ║\n";
        cout << "╠══════════════════════════╣\n";
        cout << "║ 1. Librarian Login       ║\n";
        cout << "║ 2. Student Portal        ║\n";
        cout << "║ 0. Exit                  ║\n";
        cout << "╚══════════════════════════╝\n";
        cout << "Choice: "; cin >> choice;

        switch (choice) {
            case 1: librarianMenu(books); break;
            case 2: studentMenu(books);   break;
            case 0: cout << "\nGoodbye! 👋\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}