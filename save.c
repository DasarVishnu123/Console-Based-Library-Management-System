#include <stdio.h>
#include "LMS.h"
int save_books()
{
        FILE *fp;
        fp = fopen("book.data", "w");
        if(fp == NULL)
        {
                printf("Unable to open file\n");
                return 0;
        }
        if(book_count==0)
        {
                printf("No Books available.Empty book file saved.\n");
                fclose(fp);
                return 1;
        }
        for(int i=0;i<book_count;i++)
        {
       //       fprintf(fp, "%d\n%s\n%s\n%d\n",
         //             book[i].book_id,
           //           book[i].book_name,
              //        book[i].book_author,
             //         book[i].quantity);

                fprintf(fp,"%d======================\n",i);
                fprintf(fp,"Book id      :%d\n",book[i].book_id);
                fprintf(fp,"Book name    :%s\n",book[i].book_name);
                fprintf(fp,"Book author  :%s\n",book[i].book_author);
                fprintf(fp,"Book quantity:%d\n",book[i].quantity);
        }
        printf("saved successfully\n");
        fclose(fp);
        return 1;
}
int save_issue_books()
{
    FILE *fp;
    fp = fopen("issue.data", "w");
    if(fp == NULL)
    {
        printf("Unable to open issue file.\n");
        return 0;
    }
    if(issue_book_count == 0)
    {
        printf("No issue records available. Empty issu file save.\n");
        fclose(fp);
        return 1;
    }
    for(int i = 0; i < issue_book_count; i++)
    {
        fprintf(fp, "Record       :%d\n", i);
        fprintf(fp, "Book id      :%d\n", issue_book[i].Book_id);
        fprintf(fp, "User id      :%d\n", issue_book[i].user_id);
        fprintf(fp, "User name    :%s\n", issue_book[i].name);
        fprintf(fp, "Issue date   :%s\n", issue_book[i].issue_date);
        fprintf(fp, "Due date     :%s\n", issue_book[i].Due_date);
        fprintf(fp, "Return date  :%s\n", issue_book[i].return_date);
        fprintf(fp, "Fine         :%d\n", issue_book[i].fine);
        fprintf(fp, "Status       :%s\n", issue_book[i].status);
    }
    fclose(fp);
    printf("Issue records saved successfully.\n");
    return 1;
}