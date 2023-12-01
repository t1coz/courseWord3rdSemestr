#ifndef BOOK_H
#define BOOK_H
#include "mainwindow.h"
#include <iostream>
#include <QString>
#include <QTableWidget>
#include "ui_mainwindow.h"
#include <curses.h>
using namespace std;
class Book: public MainWindow{
    QString name;
    QString shelve;
    QString path;
public:
    Book(QString name, QString shelve, QString path) :
        name(name), shelve(shelve), path(path) {}
    QString getName();
    QString getNameAtIndex(int rowIndex);
    QString getShelve();
    QString getShelveAtIndex(int rowIndex);
    QString getPath();
    QString getPathAtIndex(int rowIndex);
//    void setName(QString userName, int rowIndex);
//    void setShelve(QString userShelve, int rowIndex);
//    void setPath(QString userPath, int rowIndex);

};
void getStr(char **string);
#endif
