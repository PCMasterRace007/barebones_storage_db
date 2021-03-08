
#ifndef LOGIN_H
#define LOGIN_H
#include <stdlib.h>
#include <stdio.h>
#include "var.h"
#include "concat.h"
#include "inmenu.h"
PGconn *conn;
PGresult *res_login;
void login()
{
    printf("Enter the username : \n");
    char *username_login = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", username_login);
    printf("Enter the password: \n");
    char *password_login = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", password_login);
    char *tmpsqlsel = concatsqlsel(username_login);
    res_login = PQexec(conn, tmpsqlsel);
    if (PQresultStatus(res_login) == PGRES_TUPLES_OK && PQntuples(res_login) == 1)
    {
        printf("\n%d tuples found", PQntuples(res_login));
        printf("\nUsername found");
        if (strcmp(PQgetvalue(res_login, 0, 1), password_login) == 0)
        {
            printf("\nPassword matched");
            inmenu(username_login, password_login);
        }
        else
        {
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
    free(username_login);
    free(password_login);
}
#endif