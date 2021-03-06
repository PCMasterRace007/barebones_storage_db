#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#define MAX 1000
char *username;
char *password;
char *tmp;
char *tmpusr;
char *tmppass;
char *tmpsqlsel;
char *tmpsqlins;
char *tmpsqluppass;
PGconn *conn;
PGresult *res;
PGresult *update;
char *connect_str = "host=localhost port=5432 dbname=project";
FILE *fptr;
void concatsqlsel()
{
    free(tmpsqlsel);
    tmpsqlsel = (char *)calloc(MAX, sizeof(char));
    //printf("%s", tmpsqlsel);
    strcat(tmpsqlsel, "select * from user_list where username = \'");
    strcat(tmpsqlsel, username);
    strcat(tmpsqlsel, "\'");
    printf("Query to be passed, \"%s\"", tmpsqlsel);
}

void concatsqlins()
{
    free(tmpsqlins);
    tmpsqlins = (char *)calloc(MAX, sizeof(char));
    //printf("%s", tmpsqlins);
    strcat(tmpsqlins, "insert into user_list values(");
    strcat(tmpsqlins, "\'");
    strcat(tmpsqlins, username);
    strcat(tmpsqlins, "\'");
    strcat(tmpsqlins, ", ");
    strcat(tmpsqlins, "\'");
    strcat(tmpsqlins, password);
    strcat(tmpsqlins, "\'");
    strcat(tmpsqlins, ");");
    strcat(tmpsqlins, "\0");
    printf("query to be passed, \"%s\"", tmpsqlins);
}
void concatsqluppass()
{
    free(tmpsqluppass);
    tmpsqluppass = (char *)calloc(MAX, sizeof(char));
    strcat(tmpsqluppass, "update user_list set encpass =\'");
    strcat(tmpsqluppass, tmppass);
    strcat(tmpsqluppass, "\'");
    strcat(tmpsqluppass, "where encpass =\'");
    strcat(tmpsqluppass, password);
    strcat(tmpsqluppass, "\'");
    printf("query to be passed, \"%s\"", tmpsqluppass);
}
void inmenu()
{
    int ch;
    while (1)
    {
        printf("\nActions\n1.)Change Password\n2.)Change username\n3.)list storage\n4.)Exit");
        printf("\nEnter one of the following actions: ");
        scanf("%d", &ch);
        PQclear(update);
        switch (ch)
        {
        case 1:
            printf("\nEnter new password: ");
            tmppass = (char *)calloc(MAX, sizeof(char));
            scanf("%1000s", tmppass);
            concatsqluppass();
            update = PQexec(conn, tmpsqluppass);
            if (PQresultStatus(update) == PGRES_COMMAND_OK)
            {
                printf("\nPassword updated");
                free(tmppass);
            }
            else
            {
                printf("\nError updating password, try again");
            }
            break;
        case 2:
            break;
        case 4:
            return;
        default:
            printf("\nInvalid choice");
            break;
        }
    }
}
void signup()
{
    printf("Enter the username : - \n");
    username = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", username);
    printf("Enter the password: - \n");
    password = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", password);
    concatsqlins();
    res = PQexec(conn, tmpsqlins);
    if (PQresultStatus(res) == PGRES_COMMAND_OK)
    {
        printf("\nSignup resgistration Successfull");
    }
    else
    {
        printf("\nSignup not successful, try again");
    }
    PQclear(res);
    free(username);
    free(password);
}
void login()
{
    int i = 0;
    int j = 0;
    int k;
    int mrows;
    printf("Enter the username : \n");
    username = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", username);
    printf("Enter the password: \n");
    password = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", password);
    concatsqlsel();
    res = PQexec(conn, tmpsqlsel);
    if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) == 1)
    {
        printf("\n%d tuples found", PQntuples(res));
        printf("\nUsername found");
        if (strcmp(PQgetvalue(res, 0, 1), password) == 0)
        {
            printf("\nPassword matched");
            inmenu();
        }
        else
        {
            printf("\npassword did not match, try again");
        }
    }
    else
    {
        printf("\n%d", PQntuples(res));
        printf("\nUsername not found");
    }
    PQclear(res);
    free(username);
    free(password);
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
        printf("\n Invalid Choice !");
    }
}
void main()
{
    conn = PQconnectdb(connect_str);
    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("Connection failed %s", PQerrorMessage(conn));
    }
    else
    {
        printf("Connection established successfully to database %s", PQdb(conn));
        for (;;)
        {
            load();
        }
        PQfinish(conn);
    }
}
