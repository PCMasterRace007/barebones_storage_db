#ifndef INMENU_H
#define INMENU_H
#include <stdlib.h>
#include <stdio.h>
#include "concat.h"
#include "login.h"
char *tmpsqluppass;
char *newuser;
PGresult *res_newpass;
void inmenu(char *username, char *password)
{
    char *username_param, *password_param;
    password_param = password;
    username_param = username;
    int ch;
    while (1)
    {
        free(newpass);
        free(tmpsqluppass);
        printf("\nActions\n1.)Change Password\n2.)Change username\n3.)list storage\n4.)Exit");
        printf("\nEnter one of the following actions: ");
        scanf("%d", &ch);
        PQclear(res_newpass);
        switch (ch)
        {
        case 1:
            printf("\nEnter new password: ");
            char *newpass = (char *)calloc(MAX, sizeof(char));
            scanf("%1000s", newpass);
            char *tmpsqluppass = concatsqluppass(password_param, newpass);
            free(password_param);
            password_param = newpass;
            res_newpass = PQexec(conn, tmpsqluppass);
            if (PQresultStatus(res_newpass) == PGRES_COMMAND_OK)
            {
                printf("\nPassword updated");
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
#endif