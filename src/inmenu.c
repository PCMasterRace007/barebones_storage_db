#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>
#include "../include/var.h"
#include "../include/func.h"
char *tmpsqluppass;
char *tmpsqlupuser;
char *newuser;
char *newpass;
PGresult *res_newpass;
PGresult *res_newuser;
void inmenu()
{
    int ch;
    while (1)
    {
        printf("\nActions\n1.)Change Password\n2.)Change username\n3.)list storage\n4.)Exit");
        printf("\nEnter one of the following actions: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\nEnter new password: ");
            char *newpass = (char *)calloc(MAX, sizeof(char));
            scanf("%1000s", newpass);
            tmpsqluppass = (char *)calloc(MAX, sizeof(char));
            char *tmpsqluppass = concatsqluppass(password_login, newpass);
            password_login = newpass;
            res_newpass = PQexec(conn, tmpsqluppass);
            if (PQresultStatus(res_newpass) == PGRES_COMMAND_OK)
            {
                printf("\nPassword updated");
                printf("\nPlease re-login with new password");
                login_token = 0;
                return;
            }
            else
            {
                printf("\nError updating password, try again");
            }
            return;
            break;
        case 2:
            printf("\nEnter new username: ");
            char *newuser = (char *)calloc(MAX, sizeof(char));
            scanf("%1000s", newuser);
            tmpsqlupuser = (char *)calloc(MAX, sizeof(char));
            char *tmpsqlupuser = concatsqlupuser(username_login, newuser);
            username_login = newuser;
            res_newuser = PQexec(conn, tmpsqlupuser);
            if (PQresultStatus(res_newuser) == PGRES_COMMAND_OK)
            {
                printf("\nUsername updated");
                printf("\nPlease re-login with new Username");
                login_token = 0;
                return;
            }
            else
            {
                printf("\nError updating username, maybe try again with different username which is not previously taken");
            }
            break;
        case 4:
            return;
        default:
            printf("\nInvalid choice");
            break;
        }
        PQclear(res_newpass);
        free(newpass);
        free(newuser);
        free(tmpsqluppass);
        free(password_login);
        free(tmpsqlupuser);
        free(username_login);
    }
}
