#include<stdio.h>
#include"LMS.h"
#include<stdlib.h>
void display_menu()
{
        printf("---------------------------------\n");
        printf("|1 .add_new_book                |\n");
        printf("|2 .save                        |\n");
        printf("|3 .view all books              |\n");
        printf("|4 .remove book                 |\n");
        printf("|5 .search book                 |\n");
        printf("|6 .update book details         |\n");
        printf("|7 .Isuue Book                  |\n");
        printf("|8 .View Isuue boks             |\n");
        printf("|9 .return book                 |\n");
        printf("|10.exit                        |\n");
        printf("---------------------------------\n");
}
int main()
{
        int n;
        if(load_books()!=1)
        {
                printf("sync not done\n");
                return 1;
        }
        if(load_issue_books()!=1)
        {
                printf("Issue records sync not done\n");
                return 1;
        }
        while(1)
        {
                //system ("clear");
                printf("=================================\n");
                printf("----library manegment system-----\n");
                printf("=================================\n");
                display_menu();
                printf("enter choice\n");
                scanf("%d",&n);
                switch(n)
                {
                        case 1:Add_new_book();
                                break;
                        case 2:save_books();
                                save_issue_books();
                                break;
                        case 3:view_books();
                                break;
                        case 4:remove_book();
                                break;
                        case 5:search_book();
                                break;
                        case 6:update_book_details();
                                break;
                        case 7:Issue_book();
                                break;
                        case 8:view_issue_books();
                                break;
                        case 9:
                                return_book();
                                break;
                        case 10:
                                if(save_books() && save_issue_books())
                                {
                                        free(book);
                                        free(issue_book);
                                        exit(0);
                                }
                                else
                                {
                                        printf("Data saving failed\n");
                                }
                        default :
                        printf("enterd in correct choice\n");
                        break;
                }
        }
}