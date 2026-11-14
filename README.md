# 📚 Library Management System

<p align="center">
  <b>A Console-Based Library Management System developed using C Programming</b>
  <br>
  A modular application to manage books, students, book transactions, and overdue fines efficiently.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" />
  <img src="https://img.shields.io/badge/Platform-Linux-orange.svg" />
  <img src="https://img.shields.io/badge/Compiler-GCC-green.svg" />
  <img src="https://img.shields.io/badge/Project-Completed-success.svg" />
</p>

---

## 🚀 Project Overview

The **Library Management System** is a menu-driven application developed in C on Linux. It provides essential library operations, including book management, student records, issuing and returning books, and fine calculation.

The application uses modular programming and file handling to maintain records even after the program is closed.

## ✨ Key Features

| Feature | Description |
|---|---|
| 📖 Book Management | Add, view, search, update, and remove books |
| 👨‍🎓 Student Records | Maintain student information |
| 📤 Issue Books | Issue available books to students |
| 📥 Return Books | Process book returns and update availability |
| 📅 Date Management | Generate issue dates and due dates automatically |
| 💰 Fine Calculation | Calculate overdue fines at ₹5 per day |
| 📊 Quantity Tracking | Maintain available book quantities |
| 💾 Data Persistence | Save and retrieve records using files |

## 🛠️ Technology Stack

- **Language:** C
- **Operating System:** Linux
- **Compiler:** GCC
- **Programming Concepts:**
  - Structures and Pointers
  - Dynamic Memory Allocation (`realloc`)
  - File Handling
  - String Handling
  - Modular Programming
  - Multi-file Compilation

## 📂 Project Structure

```text
Library-Management-System/
│
├── Main.c
├── LMS.h
├── Book_handle.c
├── Issue_book_handle.c
├── save.c
├── sync.c
├── .gitignore
└── README.md
```

## ⚙️ Installation & Execution

**1. Clone the repository**

```bash
git clone https://github.com/DasarVishnu123/Console-Based-Library-Management-System.git
```

**2. Navigate to the project directory**

```bash
cd Console-Based-Library-Management-System
```

**3. Compile the source files**

```bash
gcc Main.c Book_handle.c save.c sync.c Issue_book_handle.c -o LMS
```

**4. Run the application**

```bash
./LMS
```

## 💾 Data Storage

The application uses file handling for persistent storage:

- `book.data` – Stores book details and available quantities.
- `issue.data` – Stores book issue and return transaction records.

These data files are generated when the application runs and saves records.

## 🎯 Project Objectives

- Apply core C programming concepts in a practical application.
- Understand dynamic memory allocation and memory management.
- Implement modular programming using multiple source files.
- Manage records using file handling.
- Develop a real-world, menu-driven management application.

## 👨‍💻 Author

**Dasari Vishnuvardhan Reddy**

*Aspiring Embedded Firmware Engineer*

[GitHub Profile](https://github.com/DasarVishnu123)

---

<p align="center">
  ⭐ If you find this project useful, consider giving it a star!
  <br>
  <b>Thank you for visiting!</b>
</p>
