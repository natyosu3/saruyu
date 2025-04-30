#include <iostream>
#include <libpq-fe.h>

void checkConnection(PGconn *conn)
{
    if (PQstatus(conn) != CONNECTION_OK)
    {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        exit(1);
    }
}

void executeQuery(PGconn *conn, const char *query)
{
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        std::cerr << "Query failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);
}

int main()
{
    const char *conninfo = "host=localhost port=5432 dbname=mydatabase user=user password=password";

    // データベースに接続
    PGconn *conn = PQconnectdb(conninfo);
    checkConnection(conn);

    // テーブルを作成
    const char *createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            id SERIAL PRIMARY KEY,
            name VARCHAR(100),
            age INT
        )
    )";
    executeQuery(conn, createTableQuery);
    std::cout << "Table created successfully." << std::endl;

    // データを挿入
    const char *insertDataQuery = R"(
        INSERT INTO users (name, age) VALUES
        ('Alice', 30),
        ('Bob', 25),
        ('Charlie', 35)
    )";
    executeQuery(conn, insertDataQuery);
    std::cout << "Data inserted successfully." << std::endl;

    // 接続を閉じる
    PQfinish(conn);
    std::cout << "Connection closed." << std::endl;

    return 0;
}