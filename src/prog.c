#include <libpq-fe.h>
#include "../include/var.h"
#include "../include/func.h"
PGconn *conn;
char *connect_str = "host=localhost port=5432 dbname=project";
void load()
{
    int load_ch;
    printf("\nEnter 1 to Signup\nEnter 2 to Login\nEnter 3 to exit");
    printf("\nEnter your choice: ");
    scanf("%d", &load_ch);
    if (load_ch == 1)
    {
        signup();
    }
    else if (load_ch == 2)
    {
        login();
        if (login_token)
        {
            inmenu();
        }
    }
    else if (load_ch == 3)
    {
        exit(0);
    }
    else
    {
        printf("\nInvalid Choice !");
    }
}
int main()
{
    conn = PQconnectdb(connect_str);
    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("\nConnection failed %s", PQerrorMessage(conn));
    }
    else
    {
        printf("\nConnection established successfully to database %s", PQdb(conn));
        for (;;)
        {
            load();
        }
        PQfinish(conn);
    }
}
