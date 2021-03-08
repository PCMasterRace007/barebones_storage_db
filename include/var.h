#ifndef VAR_H
#define VAR_H
#include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
extern char *username_signup;
extern char *password_signup;
extern char *username_login;
extern char *password_login;
extern char *username_param;
extern char *password_param;
extern char *newpass;
extern char *newuser;
extern char *tmpsqlsel;
extern char *tmpsqlins;
extern char *tmpsqluppass;
extern PGconn *conn;
extern PGresult *res_login;
extern PGresult *res_signup;
extern PGresult *res_newpass;
extern char *connect_str;
#endif