#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
#include"LMS.h"
struct BOOK *book = NULL;
int book_count = 0;
void Add_new_book()
{
        struct BOOK *temp;
        temp=realloc(book,(book_count+1)*sizeof(struct BOOK));
        if(temp==NULL)
        {
                printf("memory allocated failed\n");
                return;
        }
        book=temp;
        printf("enter book ID\n");
        scanf("%d",&book[book_count].book_id);
        for(int i = 0; i < book_count; i++)
        {
                if(book[i].book_id == book[book_count].book_id)
                {
                        printf("Book ID already exists\n");
                        return;
                }
        }
        printf("enter book name\n");
        //scanf(" %s",book[book_count].book_name);
        __fpurge(stdin);
        fgets(book[book_count].book_name,sizeof(book[book_count].book_name),stdin);
        book[book_count].book_name[strcspn(book[book_count].book_name,"\n")]='\0';
        printf("enter book author\n");
        __fpurge(stdin);
        //scanf("%s",book[book_count].book_author);
        fgets(book[book_count].book_author,sizeof(book[book_count].book_author),stdin);
        book[book_count].book_author[strcspn(book[book_count].book_author,"\n")]='\0';
        printf("enter books quantity\n");
        scanf("%d",&book[book_count].quantity);
        if(book[book_count].quantity < 0)
        {
                printf("Invalid quantity\n");
                return;
        }
        book_count++;
        if(save_books())
                printf("Book added successfully\n");
        else
                printf("Book added in memory, but file saving failed\n");
}
void view_books()
{
        if(book_count==0)
        {
                printf("there is no books to view\n");
                return;
        }
        printf("===========Book details==========\n");
        for(int i=0;i<book_count;i++)
        {
                printf("Book ID         :");
                printf("%d\n",book[i].book_id);
                printf("Book name       :");
                puts(book[i].book_name);
                printf("Book author name:%s\n",book[i].book_author);
                printf("quantity        :");
                printf("%d\n",book[i].quantity);
        printf("---------------------------------\n");
        }
}
void remove_book()
{
        int n,found=0,id,matched=0;
        char name[50];
        while(1)
        {
        found=0;
        matched=0;
        if(book_count==0)
        {
                printf("there is no books to remove\n");
                return;
        }
        printf("===Remove book=====\n");
        printf("1.By Book id\n");
        printf("2.By Book name\n");
        printf("3.Back to main manu\n");
        printf("enter choice\n");
        scanf("%d",&n);
        switch(n)
        {
                case 1:
                        printf("Enter book ID\n");
                        scanf("%d",&id);
                        for(int i=0;i<book_count;i++)
                        {
                        if(book[i].book_id == id)
                        {
                                matched=1;
                                int issued = 0;
                                for(int j = 0; j < issue_book_count; j++)
                                {
                                        if(issue_book[j].Book_id == book[i].book_id &&
           strcmp(issue_book[j].status, "Issued") == 0)
                                        {
                                                issued = 1;
                                                break;
                                        }
                                }

                                if(issued)
                                {
                                        printf("This book has issued copies. Cannot remove it.\n");
                                        continue;
                                }
                                memmove(&book[i], &book[i+1],(book_count-i-1) * sizeof(struct BOOK));

                                book_count--;
                                found = 1;
                                i--;
                        }
                        }
                        break;
                case 2:
                        printf("Enter book name\n");
                        __fpurge(stdin);
                        fgets(name,sizeof(name),stdin);
                        name[strcspn(name,"\n")]='\0';
                        for(int i=0;i<book_count;i++)
                        {
                                if(strcmp(book[i].book_name, name) == 0)
                                {
                                        matched=1;
                                        int issued = 0;
                                        for(int j = 0; j < issue_book_count; j++)
                                        {
                                                if(issue_book[j].Book_id == book[i].book_id && strcmp(issue_book[j].status, "Issued") == 0)
                                                {
                                                        issued = 1;
                                                        break;
                                                }
                                        }
                                        if(issued)
                                        {
                                                        printf("Book ID %d has issued copies. Cannot remove it.\n",book[i].book_id);
                                                continue;
                                        }

                                        memmove(&book[i], &book[i+1],(book_count-i-1) * sizeof(struct BOOK));
                                        book_count--;
                                        found = 1;
                                        i--;
                                }
                        }
                        break;
                case 3:
                        return;
                default:
                        printf("enter wrong chosen\n");
                        continue;
        }
        if(found)
        {
                printf("Book removed successfully\n");
                save_books();
        }
        else if(!matched)
        {
                printf("Book not found\n");
        }
        }
}
void search_book()
{
        int n,found=0,id;
        char name[50];
        char name1[50];
        while(1)
        {
        found=0;
        if(book_count==0)
        {
                printf("there is no books to search\n");
                return;
        }
        printf("=========search book==========\n");
        printf("1.By Book\n");
        printf("2.By book name\n");
        printf("3.By author name\n");
        printf("4.Back to main menu\n");
        printf("enter choice\n");
        scanf("%d",&n);
        switch(n)
        {
                case 1:
                        printf("enter book id\n");
                        scanf("%d",&id);
                        for(int i=0;i<book_count;i++)
                        {
                                if(book[i].book_id==id)
                                {
                                        found=1;
                                        printf("-------------------------------\n");
                                        printf("Book Id          :%d\n",book[i].book_id);
                                        printf("Book book name   :%s\n",book[i].book_name);
                                        printf("Book author name :%s\n",book[i].book_author);
                                        printf("Books quantity   :%d\n",book[i].quantity);
                                        printf("-------------------------------\n");
                                }
                        }
                        break;
                case 2:
                        printf("enter book name\n");
                        __fpurge(stdin);
                        fgets(name,sizeof(name),stdin);
                        name[strcspn(name,"\n")]='\0';
                        for(int i=0;i<book_count;i++)
                        {
                                if(strcmp(book[i].book_name,name)==0)
                                {
                                        found=1;
                                        printf("-------------------------------\n");
                                        printf("Book Id          :%d\n",book[i].book_id);
                                        printf("Book book name   :%s\n",book[i].book_name);
                                        printf("Book author name :%s\n",book[i].book_author);
                                        printf("Books quantity   :%d\n",book[i].quantity);
                                        printf("-------------------------------\n");
                                }
                        }
                        break;
                case 3:
                        printf("enter book author name\n");
                        __fpurge(stdin);
                        fgets(name1,sizeof(name1),stdin);
                        name1[strcspn(name1,"\n")]='\0';
                        for(int i=0;i<book_count;i++)
                        {
                                if(strcmp(book[i].book_author,name1)==0)
                                {
                                        found=1;
                                        printf("-------------------------------\n");
                                        printf("Book Id          :%d\n",book[i].book_id);
                                        printf("Book book name   :%s\n",book[i].book_name);
                                        printf("Book author name :%s\n",book[i].book_author);
                                        printf("Books quantity   :%d\n",book[i].quantity);
                                        printf("-------------------------------\n");
                                }
                        }
                        break;
                case 4:
                        return;
                default:
                        printf("enter wrong chosen\n");
                }
                if(!found)
                {
                        printf("book not found\n");
                }
        }
}
/*void update_book_details()
{
        int n,found=0,ch,id;
        char name[50];
        while(1)
        {
        found=0;
        if(book_count==0)
        {
                printf("There is no books to update\n");
                return;
        }
        printf("========update book details=======\n");
        printf("1.By book id\n");
        printf("2.By book name\n");
        printf("3.Back to main menu\n");
        printf("enter choice\n");
        scanf("%d",&n);
        switch(n)
        {
                case 1:
                        printf("enter book id\n");
                        scanf("%d",&id);
                        for(int i=0;i<book_count;i++)
                        {
                                if(book[i].book_id==id)
                                {
                                        found=1;
                                        printf("what you want to update\n");
                                        printf("1.update book id\n2.update book name\n3.update book author name\n4.update book quantity\n5.skip\n");
                                        scanf("%d",&ch);
                                        switch(ch)
                                        {
                                                case 1:
                                                        //printf("enter new book id\n");
                                                        //scanf("%d",&book[i].book_id);
                                                //      save_books();
                                                //      break;
                                                                {
                                                                        int new_id, duplicate = 0;

                                                                        printf("enter new book id\n");
                                                                        scanf("%d", &new_id);

                                                                        for(int j = 0; j < book_count; j++)
                                                                        {
                                                                                if(j != i && book[j].book_id == new_id)
                                                                                {
                                                                                        duplicate = 1;
                                                                                        break;
                                                                                }
                                                                        }

                                                                        if(duplicate)
                                                                        {
                                                                                printf("Book ID already exists\n");
                                                                        }
                                                                        else
                                                                        {
                                                                                book[i].book_id = new_id;
                                                                                save_books();
                                                                                printf("Book ID updated successfully\n");
                                                                        }
                                                                                 break;
                                                                }
                                                case 2:
                                                {
                                                        printf("Enter new book name\n");
                                                        __fpurge(stdin);
                                                        fgets(book[i].book_name, sizeof(book[i].book_name), stdin);
                                                        book[i].book_name[strcspn(book[i].book_name, "\n")] = '\0';
                                                        save_books();
                                                        printf("Book name updated successfully\n");
                                                        break;
                                                }
                                                case 3:
                                                        printf("enter new book author name\n");
                                                        __fpurge(stdin);
                                                        fgets(book[i].book_author,sizeof(book[i].book_author),stdin);
                                                        book[i].book_author[strcspn(book[i].book_author,"\n")]='\0';
                                                        save_books();
                                                        break;
                                                case 4:
                                                        printf("enter new books quantity\n");
                                                        scanf("%d",&book[i].quantity);
                                                        if(book[i].quantity < 0)
                                                        {
                                                                printf("Invalid quantity\n");
                                                                book[i].quantity = 0;
                                                        }
                                                        save_books();
                                                        break;
                                                case 5:
                                                        break;//skip
                                                default:
                                                        printf("wrong chosen\n");
                                        }
                                }
                        }
                        break;
                case 2:
                        printf("enter book name\n");
                        __fpurge(stdin);
                        fgets(name,sizeof(name),stdin);
                        name[strcspn(name,"\n")]='\0';
                        for(int i=0;i<book_count;i++)
                        {
                                if(strcmp(book[i].book_name,name)==0)
                                {
                                        found=1;
                                        printf("what you want to update\n");
                                        printf("1.update book id\n2.update book name\n3.update book author name\n4.update book quantity\n5.skip\n");
                                        scanf("%d",&ch);
                                        switch(ch)
                                        {
                                                case 1:
                                                        printf("enter new book id\n");
                                                        scanf("%d",&book[i].book_id);
                                                        save_books();
                                                        break;
                                                case 2:
                                                        printf("enter new book name\n");
                                                        __fpurge(stdin);
                                                        fgets(book[i].book_name,sizeof(book[i].book_name),stdin);
                                                        book[i].book_name[strcspn(book[i].book_name,"\n")]='\0';
                                                        save_books();
                                                        break;
                                                case 3:
                                                        printf("enter new book author name\n");
                                                        __fpurge(stdin);
                                                        fgets(book[i].book_author,sizeof(book[i].book_author),stdin);
                                                        book[i].book_author[strcspn(book[i].book_author,"\n")]='\0';
                                                        save_books();
                                                        break;
                                                case 4:
                                                        printf("enter new books quantity\n");
                                                        scanf("%d",&book[i].quantity);
                                                        if(book[i].quantity < 0)
                                                        {
                                                                printf("Invalid quantity\n");
                                                                book[i].quantity = 0;
                                                        }
                                                        save_books();
                                                        break;
                                                case 5:
                                                        break;//skip
                                                default:
                                                        printf("wrong chosen\n");
                                        }
                                }
                        }
                        break;
                case 3:
                        save_books();
                        return;
                default:
                        printf("wrong choscen\n");
        }
        if(!found)
        {
                printf("book not found\n");
        }
        }
}*/
void update_book_details(void)
{
    int choice, id, found = 0;
    char name[50];

    if(book_count == 0)
    {
        printf("No books available to update\n");
        return;
    }

    printf("======= Update Book Details =======\n");
    printf("1. Search by Book ID\n");
    printf("2. Search by Book Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        printf("Enter Book ID: ");
        scanf("%d", &id);

        for(int i = 0; i < book_count; i++)
        {
            if(book[i].book_id == id)
            {
                found = 1;

                while(1)
                {
                    int option;

                    printf("\n======= Update Menu =======\n");
                    printf("1. Update Book ID\n");
                    printf("2. Update Book Name\n");
                    printf("3. Update Author Name\n");
                    printf("4. Update Quantity\n");
                    printf("5. Exit Update\n");
                    printf("Enter your choice: ");
                    scanf("%d", &option);

                    switch(option)
                    {
                        case 1:
                        {
                            int new_id, duplicate = 0;

                            for(int j = 0; j < issue_book_count; j++)
                            {
                                if(issue_book[j].Book_id == book[i].book_id &&
                                   strcmp(issue_book[j].status, "Issued") == 0)
                                {
                                    duplicate = 2;
                                    break;
                                }
                            }

                            if(duplicate == 2)
                            {
                                printf("Cannot change Book ID. Copies are currently issued.\n");
                                break;
                            }

                            printf("Enter new Book ID: ");
                            scanf("%d", &new_id);

                            for(int j = 0; j < book_count; j++)
                            {
                                if(j != i && book[j].book_id == new_id)
                                {
                                    duplicate = 1;
                                    break;
                                }
                            }

                            if(duplicate == 1)
                                printf("Book ID already exists\n");
                            else
                            {
                                book[i].book_id = new_id;
                                save_books();
                                printf("Book ID updated successfully\n");
                            }
                            break;
                        }

                        case 2:
                            getchar();
                            printf("Enter new Book Name: ");
                            fgets(book[i].book_name,
                                  sizeof(book[i].book_name), stdin);
                            book[i].book_name[strcspn(book[i].book_name, "\n")] = '\0';
                            save_books();
                            printf("Book Name updated successfully\n");
                            break;

                        case 3:
                            getchar();
                            printf("Enter new Author Name: ");
                            fgets(book[i].book_author,
                                  sizeof(book[i].book_author), stdin);
                            book[i].book_author[strcspn(book[i].book_author, "\n")] = '\0';
                            save_books();
                            printf("Author Name updated successfully\n");
                            break;
                        case 4:
                        {
                                int new_quantity;
                                int issued_count = 0;

                                for(int j = 0; j < issue_book_count; j++)
                                {
                                        if(issue_book[j].Book_id == book[i].book_id &&
                                        strcmp(issue_book[j].status, "Issued") == 0)
                                        {
                                                issued_count++;
                                        }
                                }
                                        printf("Enter new total book quantity: ");
                                        scanf("%d", &new_quantity);
                                        if(new_quantity < 0)
                                        {
                                                        printf("Invalid quantity\n");
                                        }
                                        else if(new_quantity < issued_count)
                                        {
                                                printf("Cannot set quantity below issued copies (%d)\n",issued_count);
                                        }
                                        else
                                        {
                                                book[i].quantity = new_quantity - issued_count;
                                                save_books();
                                                printf("Quantity updated successfully\n");
                                                printf("Available copies: %d\n", book[i].quantity);
                                        }
                                        break;
                        }

                        case 5:
                            return;

                        default:
                            printf("Invalid choice\n");
                    }
                }
            }
        }
    }
    else if(choice == 2)
    {
        getchar();
        printf("Enter Book Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        for(int i = 0; i < book_count; i++)
        {
            if(strcmp(book[i].book_name, name) == 0)
            {
                found = 1;

                while(1)
                {
                    int option;

                    printf("\n======= Update Menu =======\n");
                    printf("1. Update Book ID\n");
                    printf("2. Update Book Name\n");
                    printf("3. Update Author Name\n");
                    printf("4. Update Quantity\n");
                    printf("5. Exit Update\n");
                    printf("Enter your choice: ");
                    scanf("%d", &option);

                    switch(option)
                    {
                        case 1:
                        {
                            int new_id, duplicate = 0;

                            for(int j = 0; j < issue_book_count; j++)
                            {
                                if(issue_book[j].Book_id == book[i].book_id &&
                                   strcmp(issue_book[j].status, "Issued") == 0)
                                {
                                    duplicate = 2;
                                    break;
                                }
                            }

                            if(duplicate == 2)
                            {
                                printf("Cannot change Book ID. Copies are currently issued.\n");
                                break;
                            }

                            printf("Enter new Book ID: ");
                            scanf("%d", &new_id);

                            for(int j = 0; j < book_count; j++)
                            {
                                if(j != i && book[j].book_id == new_id)
                                {
                                    duplicate = 1;
                                    break;
                                }
                            }

                            if(duplicate == 1)
                                printf("Book ID already exists\n");
                            else
                            {
                                book[i].book_id = new_id;
                                save_books();
                                printf("Book ID updated successfully\n");
                            }
                            break;
                        }

                        case 2:
                            getchar();
                            printf("Enter new Book Name: ");
                            fgets(book[i].book_name,
                                  sizeof(book[i].book_name), stdin);
                            book[i].book_name[strcspn(book[i].book_name, "\n")] = '\0';
                            save_books();
                            printf("Book Name updated successfully\n");
                            break;

                        case 3:
                            getchar();
                            printf("Enter new Author Name: ");
                            fgets(book[i].book_author,
                                  sizeof(book[i].book_author), stdin);
                            book[i].book_author[strcspn(book[i].book_author, "\n")] = '\0';
                            save_books();
                            printf("Author Name updated successfully\n");
                            break;

                        case 4:
                        {
                                int new_quantity;
                                int issued_count = 0;
                                for(int j = 0; j < issue_book_count; j++)
                                {
                                        if(issue_book[j].Book_id == book[i].book_id && strcmp(issue_book[j].status, "Issued") == 0)
                                        {
                                                issued_count++;
                                        }
                                }
                                printf("Enter new total book quantity: ");
                                scanf("%d", &new_quantity);
                                if(new_quantity < 0)
                                {
                                        printf("Invalid quantity\n");
                                }
                                else if(new_quantity < issued_count)
                                {
                                        printf("Cannot set quantity below issued copies (%d)\n",issued_count);
                                }
                                else
                                {
                                        book[i].quantity = new_quantity - issued_count;
                                        save_books();
                                        printf("Quantity updated successfully\n");
                                        printf("Available copies: %d\n", book[i].quantity);
                                }

                                break;
                        }

                        case 5:
                            return;

                        default:
                            printf("Invalid choice\n");
                    }
                }
            }
        }
    }
    else
    {
        printf("Invalid search choice\n");
        return;
    }

    if(found == 0)
        printf("Book not found\n");
}