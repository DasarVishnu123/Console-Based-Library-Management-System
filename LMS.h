#ifndef LMS_H
#define LMS_H
#include<stdio.h>
struct BOOK
{
        int book_id;
        char book_name[50];
        char book_author[50];
        int quantity;
};
struct ISSUE_BOOK
{
        int Book_id;
        int user_id;
        char name[50];
        char issue_date[50];
        char Due_date[50];
        char return_date[50];
        int fine;
        char status[20];
};
//BOOK
extern struct BOOK *book;
extern int book_count;
//ISSUE BOOK
extern struct ISSUE_BOOK *issue_book;
extern int issue_book_count;
//All function declarations
void view_books();
void Add_new_book(void);
void remove_book();
void search_book();
void update_book_details();
void Issue_book();
void view_issue_books();
void return_book();
//save and sync purpose
int save_books();
int load_books(void);
int save_issue_books(void);
int load_issue_books(void);
#endif