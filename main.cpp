#include "pch.h"
#include <iostream>
using namespace std;
#include "Connection.h"
#include "CommonConnectionPool.h"

int main()
{
    /*
    Connection conn;
    char sql[1024] = { 0 };
    sprintf_s(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
        "zhang san", 20, "male");
    conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
    conn.update(sql);
    */

    clock_t begin = clock();
    ConnectionPool* cp = ConnectionPool::getConnectionPool();

    for (int i = 0; i < 1000; i++) {
   /*     Connection conn;
        char sql[1024] = { 0 };
        sprintf_s(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
            "zhang san", 20, "male");
        conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
        conn.update(sql);*/

        shared_ptr<Connection> sp = cp->getConnection();
        char sql[1024] = { 0 };
        sprintf_s(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
            "zhang san", 20, "male");
        //sp.connect("127.0.0.1", 3306, "root", "123456", "chat");
        sp->update(sql);
        
    }
    clock_t end = clock();
    cout << (end - begin) << "ms" << endl;

    return 0;
}