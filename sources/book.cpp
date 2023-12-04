#include "book.h"
#include "ui_mainwindow.h"

QString Book::getName(){
    return name;
}
QString Book::getNameAtIndex(int rowIndex){
    name = ui->bookTable->item(rowIndex, 0)->text();
    return name;
}
QString Book::getShelve(){
    return shelve;
}
QString Book::getShelveAtIndex(int rowIndex){
    QString rowShelve = ui->bookTable->item(rowIndex, 1)->text();
    return rowShelve;
}
QString Book::getPath(){
    return path;
}
QString Book::getPathAtIndex(int rowIndex){
    QString rowPath = ui->bookTable->item(rowIndex, 2)->text();
    return rowPath;
}

//void Book::setName(QString userName, int rowIndex){
//    ui->bookTable->setItem(rowIndex, 0, new QTableWidgetItem(userName));
//    name = userName;
//}
//void Book::setShelve(QString userShelve, int rowIndex){
//    ui->bookTable->setItem(rowIndex, 1, new QTableWidgetItem(userShelve));
//    shelve = userShelve;
//}
//void Book::setPath(QString userPath, int rowIndex){
//    ui->bookTable->setItem(rowIndex, 2, new QTableWidgetItem(userPath));
//    path = userPath;
//}
void getStr(char **string){
    int size = 0;
    int realSize = 16;
    *string = (char *)malloc(realSize * sizeof(char));
    rewind(stdin);
    char check;
    while (1) {
        check = (char)getchar();
        if (check == '\n') {
            if (size + 1 < realSize) {
                *string = (char *) realloc(*string, (size + 1) * sizeof(char));
            }
            (*string)[size] = '\0';
            return;
        }
        (*string)[size] = check;
        size++;
        if (size + 1 == realSize) {
            realSize *= 2;
            *string = (char *) realloc(*string, realSize * sizeof(char));
        }
    }
}
