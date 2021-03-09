#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libpq-fe.h>
#include "../include/func.h"
#define MAX 1000
char *concatsqlsel(char *tmpuser)
{
    char *sql;
    sql = (char *)calloc(MAX, sizeof(char));
    strcat(sql, "select * from user_list where username = \'");
    strcat(sql, tmpuser);
    strcat(sql, "\';");
    strcat(sql, "\0");
    printf("Query to be passed, \"%s\"", sql);
    return sql;
}

char *concatsqlins(char *tmpuser, char *tmppass)
{
    char *sql;
    sql = (char *)calloc(MAX, sizeof(char));
    strcat(sql, "insert into user_list values(");
    strcat(sql, "\'");
    strcat(sql, tmpuser);
    strcat(sql, "\'");
    strcat(sql, ", ");
    strcat(sql, "\'");
    strcat(sql, tmppass);
    strcat(sql, "\'");
    strcat(sql, ");");
    strcat(sql, "\0");
    printf("query to be passed, \"%s\"", sql);
    return sql;
}

char *concatsqluppass(char *tmppass, char *tmppassnew)
{
    char *sql;
    sql = (char *)calloc(MAX, sizeof(char));
    strcat(sql, "update user_list set encpass = '");
    strcat(sql, tmppassnew);
    strcat(sql, "'");
    strcat(sql, " where encpass = '");
    strcat(sql, tmppass);
    strcat(sql, "'");
    strcat(sql, "\0");
    printf("query to be passed, \"%s\"", sql);
    return sql;
}

char *concatsqlupuser(char *tmpuser, char *tmpusernew)
{
    char *sql;
    sql = (char *)calloc(MAX, sizeof(char));
    strcat(sql, "update user_list set username = '");
    strcat(sql, tmpusernew);
    strcat(sql, "'");
    strcat(sql, " where username = '");
    strcat(sql, tmpuser);
    strcat(sql, "'");
    strcat(sql, "\0");
    printf("query to be passed, \"%s\"", sql);
    return sql;
}