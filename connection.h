#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>

static bool createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    std::cout << db.open();

    QSqlQuery query;
    query.exec("create table users ("
               "id integer primary key autoincrement, "
               "name varchar(55), "
               "gender varchar(55), "
               "email varchar(55), "
               "phone varchar(55), "
               "course varchar(55), "
               "fv varchar(55)"
               ")");
    return true;
};

#endif // CONNECTION_H
