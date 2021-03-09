#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>
#include "../include/var.h"
#include "../include/func.h"
char *username_signup;
char *password_signup;
char *tmpsqlins;
PGresult *res_signup;
void signup()
{
    printf("\nEnter the username : ");
    username_signup = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", username_signup);
    printf("\nEnter the password: ");
    password_signup = (char *)calloc(MAX, sizeof(char));
    scanf("%1000s", password_signup);
    tmpsqlins = (char *)calloc(MAX, sizeof(char));
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
