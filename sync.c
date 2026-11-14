#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LMS.h"
int load_books(void)
{
        FILE *fp;
        char line[100];
        struct BOOK new_book;
        struct BOOK *temp;
        fp=fopen("book.data","r");
        if(fp==NULL)
        {
                printf("no previous records found\n");
                return 1;
        }
        while(fgets(line,sizeof(line),fp)!=NULL)
        {
                //reading book id
                if(fgets(line,sizeof(line),fp)==NULL)
                {
                        printf("Invalid book data file\n");
                        fclose(fp);
                        return 0;
                }
                if(sscanf(line,"Book id      :%d",&new_book.book_id)!=1)
                if(sscanf(line,"Book id      :%d",&new_book.book_id)!=1)
                {
                        printf("Invalid book data file\n");
                        fclose(fp);
                        return 0;
                }

                //reading book name
                if(fgets(line,sizeof(line),fp)==NULL)
                break;
                line[strcspn(line,"\n")]='\0';
                if(strncmp(line,"Book name    :",14)!= 0)
                break;
                if(strlen(line + 14) >= sizeof(new_book.book_name))
                {
                        printf("Book name is too long\n");
                        break;
                }
                strcpy(new_book.book_name, line + 14);

                // Read book author
                if(fgets(line, sizeof(line), fp) == NULL)
                break;
                line[strcspn(line, "\n")] = '\0';
                if(strncmp(line,"Book author  :", 14) != 0)
                break;
                if(strlen(line + 14) >= sizeof(new_book.book_author))
                {
                        printf("Book author name is too long\n");
                        break;
                }
                strcpy(new_book.book_author, line + 14);

                // Read quantity
                if(fgets(line, sizeof(line), fp) == NULL)
                break;
                if(sscanf(line,"Book quantity:%d", &new_book.quantity) != 1)
                break;
                temp=realloc(book,(book_count+1)*sizeof(struct BOOK));
                if(temp==NULL)
                {
                        printf("memory allocation failed\n");
                        fclose(fp);
                        return 0;
                }
                book=temp;
                book[book_count]=new_book;
                book_count++;
        }
        fclose(fp);
        return 1;
}

int load_issue_books(void)
{
    FILE *fp;
    char line[200];
    int record;
    struct ISSUE_BOOK new_issue;
    struct ISSUE_BOOK *temp;

    fp = fopen("issue.data", "r");

    if(fp == NULL)
    {
        printf("No previous issue records found\n");
        return 1;
    }

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        /* Read record number */
        if(sscanf(line, "Record       :%d", &record) != 1)
            break;

        /* Read Book ID */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        if(sscanf(line, "Book id      :%d", &new_issue.Book_id) != 1)
            break;

        /* Read User ID */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        if(sscanf(line, "User id      :%d", &new_issue.user_id) != 1)
            break;

        /* Read User name */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        line[strcspn(line, "\n")] = '\0';
        if(strncmp(line, "User name    :", 14) != 0)
            break;
        if(strlen(line + 14) >= sizeof(new_issue.name))
        {
                printf("user name is too long\n");
                break;
        }
        strcpy(new_issue.name, line + 14);

        /* Read Issue date */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        line[strcspn(line, "\n")] = '\0';
        if(strncmp(line, "Issue date   :", 14) != 0)
            break;
        if(strlen(line + 14) >= sizeof(new_issue.issue_date))
        {
                printf("Issue date is too long\n");
                break;
        }
        strcpy(new_issue.issue_date, line + 14);

        /* Read Due date */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        line[strcspn(line, "\n")] = '\0';
        if(strncmp(line, "Due date     :", 14) != 0)
            break;
        if(strlen(line + 14) >= sizeof(new_issue.Due_date))
        {
                printf("Due date is too long\n");
                break;
        }
        strcpy(new_issue.Due_date, line + 14);

        /* Read Return date */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        line[strcspn(line, "\n")] = '\0';
        if(strncmp(line, "Return date  :", 14) != 0)
            break;
        if(strlen(line + 14) >= sizeof(new_issue.return_date))
        {
                printf("Return date is too long\n");
                break;
        }
        strcpy(new_issue.return_date, line + 14);

        /* Read Fine */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        if(sscanf(line, "Fine         :%d", &new_issue.fine) != 1)
            break;

        /* Read Status */
        if(fgets(line, sizeof(line), fp) == NULL)
            break;
        line[strcspn(line, "\n")] = '\0';
        if(strncmp(line, "Status       :", 14) != 0)
            break;
        if(strlen(line + 14) >= sizeof(new_issue.status))
        {
                printf("Status is too long\n");
                break;
        }
        strcpy(new_issue.status, line + 14);

        /* Allocate memory */
        temp = realloc(issue_book,(issue_book_count + 1) * sizeof(struct ISSUE_BOOK));

        if(temp == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(fp);
            return 0;
        }

        issue_book = temp;
        issue_book[issue_book_count] = new_issue;
        issue_book_count++;

    }

    fclose(fp);
    return 1;
}