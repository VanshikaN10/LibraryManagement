# Library Management System 

A console-based Library Management System built in **C++** with separate portals for Librarians and Students. All records are persistently stored using **file handling**.

# Features

**Librarian Portal** (Password protected)
- Add and delete books
- Search books by title or author
- View all books with availability status

**Student Portal**
- View all available books
- Search books
- Borrow and return books

**File Handling**
- `books.txt` — stores all book records permanently
- `borrowed.txt` — logs every borrow/return transaction

# Tech Stack
C++ • STL • File I/O • OOP

## Run Locally
```bash
g++ file.cpp -o library
./library.exe
```
Librarian password: `admin123`

## Concepts Used
- Object Oriented Programming
- File handling (fstream)
- STL — vectors, algorithms, iterators
- Case-insensitive search
- Structured console UI

## Author
**Vanshika Nautiyal** • [GitHub](https://github.com/VanshikaN10)
```

---

**GitHub repo description:**
```
Console-based Library Management System in C++ with librarian and student portals, file handling for persistent storage, and STL-based search.
```

**Topics/tags to add:**
```
cpp  cplusplus  library-management  file-handling  oop  stl  console-app
