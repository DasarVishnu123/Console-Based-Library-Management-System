#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include"LMS.h"
struct ISSUE_BOOK *issue_book=NULL;
int issue_book_count=0;

void Generate_dates(char return_date[])
{
        time_t now;
        struct tm Return;
        time(&now);
        Return=*localtime(&now);
        strftime(return_date,50,"%d-%m-%Y",&Return);
}

void generate_dates(char issue_date[], char due_date[])
{
        time_t now;
        struct tm issue, due;
        time(&now);
        issue=*localtime(&now);
        strftime(issue_date,50,"%d-%m-%Y",&issue);
        due=issue;
        due.tm_mday += 7;
        mktime(&due);
        strftime(due_date,50,"%d-%m-%Y",&due);
}

void Issue_book()
{
        int found=0;
        if(book_count==0)
        {
                printf("There is no books to give\n");
                return;
        }
        struct ISSUE_BOOK *temp;
        char s_book[50];
        printf("=======issue book process=======\n");
        printf("=========select book============\n");
        getchar();
        fgets(s_book,sizeof(s_book),stdin);
        s_book[strcspn(s_book,"\n")]='\0';
        for(int i=0;i<book_count;i++)
        {
                if(strcmp(book[i].book_name,s_book)==0)
                {
                                found=1;
                        if(book[i].quantity>0)
                        {
                                temp=realloc(issue_book,(issue_book_count+1)*sizeof(struct ISSUE_BOOK));
                                if(temp==NULL)
                                {
                                        printf("memory allocation failed\n");
                                        return;
                                }
                                issue_book=temp;
                        //      printf("enter book id\n");
                        //      scanf("%d",&issue_book[issue_book_count].Book_id);
                                issue_book[issue_book_count].Book_id = book[i].book_id;
                                printf("enter user id\n");
                                scanf("%d",&issue_book[issue_book_count].user_id);
                                getchar();
                                printf("enter the user name\n");
                                fgets(issue_book[issue_book_count].name,sizeof(issue_book[issue_book_count].name),stdin);
                                issue_book[issue_book_count].name[strcspn(issue_book[issue_book_count].name,"\n")]='\0';
                                /*printf("enter issue date\n");
                                fgets(issue_book[issue_book_count].issue_date,sizeof(issue_book[issue_book_count].issue_date),stdin);
                                issue_book[issue_book_count].issue_date[strcspn(issue_book[issue_book_count].issue_date,"\n")]='\0';
                                printf("enter due date\n");
                                fgets(issue_book[issue_book_count].Due_date,sizeof(issue_book[issue_book_count].Due_date),stdin);
                                issue_book[issue_book_count].Due_date[strcspn(issue_book[issue_book_count].Due_date,"\n")]='\0';*/
                                generate_dates(issue_book[issue_book_count].issue_date,issue_book[issue_book_count].Due_date);
                               // printf("Issue date : %s\n",issue_book[issue_book_count].issue_date);
                               // printf("Due date   : %s\n",issue_book[issue_book_count].Due_date);
                                issue_book[issue_book_count].return_date[0] = '\0';
                                issue_book[issue_book_count].fine = 0;
                                strcpy(issue_book[issue_book_count].status, "Issued");
                                book[i].quantity--;
                                issue_book_count++;
                                save_books();
                                save_issue_books();
                        }
                        else
                        {
                                printf("Book not available\n");
                                return;
                        }
                        break;
                }
        }
        if(!found)
        {
                printf("Book not found\n");
        }
}
void view_issue_books()
{
        if(issue_book_count==0)
        {
                printf("There is no issue books to view\n");
                return;
        }
        printf("=========view issue books========\n");
        for(int i=0;i<issue_book_count;i++)
        {
                printf("Book id     :%d\n",issue_book[i].Book_id);
                printf("user id     :%d\n",issue_book[i].user_id);
                printf("user name   :%s\n",issue_book[i].name);
                printf("Issue date  :%s\n",issue_book[i].issue_date);
                printf("Due date    :%s\n",issue_book[i].Due_date);
                printf("Status      :%s\n",issue_book[i].status);
        printf("---------------------------------\n");
        }
}
void return_book()
{
        int id,user_id,found=0;
        struct tm due={0},ret={0};
        time_t due_time,return_time;
        int late_days;
        if(issue_book_count==0)
        {
                printf("Did not iisued books yet\n");
                return;
        }
        printf("===========Return boook============\n\n");
        printf("******Enter Book_id and  User_id*****\n");
        scanf("%d%d",&id,&user_id);
        for(int i=0;i<issue_book_count;i++)
        {
                if(id==issue_book[i].Book_id && strcmp(issue_book[i].status, "Issued") == 0)
                {
                                if(user_id==issue_book[i].user_id)
                                {
                                found=1;
                                Generate_dates(issue_book[i].return_date);
                                sscanf(issue_book[i].Due_date,"%d-%d-%d",&due.tm_mday, &due.tm_mon, &due.tm_year);
                                sscanf(issue_book[i].return_date,"%d-%d-%d",&ret.tm_mday, &ret.tm_mon, &ret.tm_year);
                                due.tm_year -= 1900;
                                due.tm_mon -= 1;
                                ret.tm_year -= 1900;
                                ret.tm_mon -= 1;
                                due_time = mktime(&due);
                                return_time = mktime(&ret);
                                late_days = (int)(difftime(return_time, due_time) / 86400);
                                if(late_days > 0)
                                {
                                        issue_book[i].fine = late_days * 5;
                                        printf("Late by %d days\n", late_days);
                                        printf("Fine amount: Rs.%d\n", issue_book[i].fine);
                                }
                                else
                                {
                                        issue_book[i].fine = 0;
                                        printf("No fine. Book returned on time.\n");
                                }
                                        /* Increase book quantity */
                                        for(int j = 0; j < book_count; j++)
                                        {
                                                if(book[j].book_id == id)
                                                {
                                                        book[j].quantity++;
                                                        break;
                                                }
                                        }

                                        /* Update issue record */
                                        strcpy(issue_book[i].status, "Returned");
                                        printf("Book returned successfully!\n");
                                        save_books();
                                        save_issue_books();
                                        break;
                                }
                 }
        }
        if(found == 0)
        {
                printf("Invalid Book ID or User ID\n");
        }
}