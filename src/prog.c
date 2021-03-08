#include "../include/concat.h"
#include "../include/var.h"
#include "../include/signup.h"
#include "../include/login.h"
//#include "../include/inmenu.h"
char *username;
char *password;
char *newpass;
char *newuser;
char *tmpsqluppass;
PGresult *update;
char *connect_str = "host=localhost port=5432 dbname=project";
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
int main()
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
