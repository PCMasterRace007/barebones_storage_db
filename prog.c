#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
/*void rtrim(char a[100])
{
    char rtrim[100] = "\0";
    int i = strlen(a) - 1;
    while (i >= 0)
    {
        if (a[i] == ' ' || a[i] == '\t')
        {
            rtrim[i] = '\0';
            i--;
        }
        if (a[i] != ' ' || a[i] != '\t')
        {
            break;
        }
    }
    while (i >= 0)
    {
        rtrim[i] = a[i];
        i--;
    }
    printf("\nAfter rtrim string is [%s]\n", rtrim);
    rtrimfinal = rtrim;
}
void ltrim(char b[100])
{
    char ltrim[100] = "\0";
    int i = 0, j = 0;
    while (b[i] != '\0')
    {
        if (b[i] != ' ' && b[i] != '\t')
        {
            break;
        }
        i++;
    }
    while (b[i] != '\0')
    {
        ltrim[j++] = b[i];
        i++;
    }
    printf("\nAfter ltrim string is %s \n", ltrim);
    ltrimfinal = ltrim;
}*/
char username[50];
char password[50];
char tmp[100];
char tmpusr[50];
char tmppass[50];
char tmpsql[1000];
PGconn *conn;
PGresult *res;
char *connect_str = "host=localhost port=5432 dbname=project";
FILE *fptr;
void signup()
{
    printf("Enter the username : - \n");
    scanf("%s", username);
    printf("Enter the password: - \n");
    scanf("%s", password);
    fptr = fopen("data.txt", "w");
    fputs(username, fptr);
    fputs(" ", fptr);
    fputs(password, fptr);
    fclose(fptr);
    strcat(tmpsql, "insert into user_list values(");
    strcat(tmpsql, "\'");
    strcat(tmpsql, username);
    strcat(tmpsql, "\'");
    strcat(tmpsql, ", ");
    strcat(tmpsql, "\'");
    strcat(tmpsql, password);
    strcat(tmpsql, "\'");
    strcat(tmpsql, ");");
    strcat(tmpsql, "\0");
    printf("%s", tmpsql);
    res = PQexec(conn, tmpsql); 

}
void login()
{
    int i = 0;
    int j = 0;
    int k;
    printf("Enter the username : - \n");
    scanf("%s", username);
    printf("Enter the password: - \n");
    scanf("%s", password);
    fptr = fopen("data.txt", "r");
    fgets(tmp, 50, (FILE *)fptr);
    while (tmp[i] != ' ')
    {
        tmpusr[i] = tmp[i];
        i++;
    }
    k = strcmp(username, tmpusr);
    if (k == 0)
    {
        printf("\nUsername matched");
        while (tmp[i + 1] != '\0')
        {
            tmppass[j++] = tmp[i + 1];
            i++;
        }
        k = strcmp(password, tmppass);
        if (k == 0)
        {
            printf("\nPassword matched");
        }
        else
        {
            printf("Incorrect Password");
        }
    }
    else
    {
        printf("\nIncorrect Username");
    }
    fclose(fptr);
}
void load()
{
    printf("\n Enter 1 to Signup\n Enter 2 to Login\n Enter 3 to exit\n");
    int load_ch;
    scanf("%d", &load_ch);
    if (load_ch == 1)
    {
        signup();
    }
    else if (load_ch == 2)
    {
        login();
    }
    else if (load_ch == 3)
    {
        exit(0);
    }
    else
    {
        printf("\n Invalid Choice ! ");
    }
}
void main()
{
    conn = PQconnectdb(connect_str); 
    if(PQstatus(conn) != CONNECTION_OK)
    {
	    printf("Connection failed %s", PQerrorMessage(conn));
    }
    else
    {
    	printf("Connection established successfully to database %s", PQdb(conn));
    }
    for (;;)
    {
        load();
    }
    PQfinish(conn);
}

