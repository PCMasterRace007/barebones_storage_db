#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>
#include "../include/var.h"
#include "../include/func.h"
PGresult *res_login;
char *username_login;
char *password_login;
char *tmpsqlsel;
int login_token = 0;
void login()
{
    free(username_login);
    free(password_login);
    printf("\nEnter the username : ");
    username_login = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", username_login);
    printf("\nEnter the password: ");
    password_login = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", password_login);
    tmpsqlsel = (char *)calloc(MAX, sizeof(char));
    tmpsqlsel = concatsqlsel(username_login);
    res_login = PQexec(conn, tmpsqlsel);
    if (PQresultStatus(res_login) == PGRES_TUPLES_OK && PQntuples(res_login) == 1)
    {
        printf("\n%d tuples found", PQntuples(res_login));
        printf("\nUsername found");
        if (strcmp(PQgetvalue(res_login, 0, 1), password_login) == 0)
        {
            printf("\nPassword matched");
            login_token = 1;
        }
        else
        {
            login_token = 0;
            printf("\npassword did not match, try again");
        }
    }
    else
    {
        printf("\n%d", PQntuples(res_login));
        printf("\nUsername not found");
    }
    PQclear(res_login);
    free(tmpsqlsel);
}
