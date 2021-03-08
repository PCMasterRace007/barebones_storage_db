#ifndef SIGNUP_H
#define SIGNUP_H
#include <stdlib.h>
#include <stdio.h>
#include "var.h"
char *tmpsqlins;
PGconn *conn;
PGresult *res_signup;
void signup()
{
    printf("Enter the username : - \n");
    char *username_signup = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", username_signup);
    printf("Enter the password: - \n");
    char *password_signup = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", password_signup);
    tmpsqlins = concatsqlins(username_signup, password_signup);
    res_signup = PQexec(conn, tmpsqlins);
    if (PQresultStatus(res_signup) == PGRES_COMMAND_OK)
    {
        printf("\nSignup resgistration Successfull");
    }
    else
    {
        printf("\nSignup not successful, try again");
    }
    free(tmpsqlins);
    PQclear(res_signup);
    free(username_signup);
    free(password_signup);
}
#endif