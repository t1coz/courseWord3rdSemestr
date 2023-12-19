#include "ui_mainwindow.h"
#include "widget.h"
#include "mainwindow.h"
//#include "epubparser.h"
//#include "epubreaderdialog.h"
#include "data.h"

#include <QSettings>
#include <QDateTime>
#include <QDebug>
//#include <QWarning>

#define SAVES_PATH "/Users/hanna/Documents/qt/idgfa/idkwati/saves/"
#define PROJECT_PATH "/Users/hanna/Documents/qt/idgfa/idkwati/"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createShelveBtn_clicked()
{
    QString shelveName = ui->shelveNameLineEdit->text();
    if(shelveName == ""){
        QMessageBox::warning(this,"Shelve error", "You should enter a valid name. Try again.");
    }else{
        if(ui->typeOfShelve->findText(shelveName) == -1){   //not found in comboBox
            ui->typeOfShelve->addItem(shelveName);
        }else{
            QMessageBox::warning(this,"Shelve error", "Entered name already exists.");
        }
    }
}

void MainWindow::on_deleteShelveBtn_clicked()
{
    QString shelveName = ui->shelveNameLineEdit->text();
    if(shelveName == ""||shelveName == "undecided" ){
        QMessageBox::warning(this,"Shelve error", "You should enter a valid name. Try again.");
    }else{
        if(ui->typeOfShelve->findText(shelveName) != -1 ){   //found in comboBox
            ui->typeOfShelve->removeItem(ui->typeOfShelve->findText(shelveName,Qt::MatchContains));
            for (int i = 0; i < ui->bookTable->rowCount(); i++) {
                if (ui->bookTable->item(i, 1)->text() == shelveName) {
                    ui->bookTable->setItem(i, 1, new QTableWidgetItem("undecided"));
                }
            }
        }else{
            QMessageBox::warning(this,"Shelve error", "Entered shelve does not exist.");
        }
    }
}

void MainWindow::on_uploadFileBtn_clicked()
{
    QString defaultPath ="/Users/hanna/Desktop/books/";
    QString filter = "EPUB (*.epub)";
    QString fileName = QFileDialog::getOpenFileName(this, "Select a file", defaultPath, filter);
    ui->pathLbl->setText(fileName);
}


void MainWindow::on_addBookBtn_clicked()
{
    QString filePath = ui->pathLbl->text();
    QString bookName = ui->bookNameLineEdit->text();
    if(bookName == "" || filePath == ""){
        QMessageBox::warning(this,"Name", "You should upload the book and enter the name.\nTry again.");
    }else{
        QList<QTableWidgetItem *> NameList = ui->bookTable->findItems(bookName, Qt::MatchExactly);
        QList<QTableWidgetItem *> PathList = ui->bookTable->findItems(filePath, Qt::MatchExactly);

        if(NameList.isEmpty()!=0 && PathList.isEmpty()!=0 ){
            ui->bookTable->insertRow(0);
            ui->bookTable->setItem(0, 0, new QTableWidgetItem(bookName));
            ui->bookTable->setItem(0, 1, new QTableWidgetItem("undecided"));
            ui->bookTable->setItem(0, 2, new QTableWidgetItem(filePath));
        }else{
            QMessageBox::warning(this,"Book in the table", "Book already exists in the table. Try again.");
        }
    }
}
void MainWindow::on_deleteBookBtn_clicked(){
    QString bookName = ui->bookNameLineEdit->text();
    int rowIndex = 0, flag = 0;
    for (int i = 0; i < ui->bookTable->rowCount(); i++) {
        if (ui->bookTable->item(i, 0)->text() == bookName) {
            flag = 1;
            rowIndex = i;
            break;
        }
    }
    if(flag == 1){
        QString shelveName = ui->bookTable->item(rowIndex, 1)->text();
        ui->typeOfShelve->removeItem(ui->typeOfShelve->findText(shelveName,Qt::MatchContains));
        ui->bookTable->removeRow(rowIndex);

    }else{
        QMessageBox::warning(this,"Book in the table", "Book does not exist. Try again.");
    }
}

void MainWindow::on_saveTableBtn_clicked()
{

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd-MM-yyyy_hh:mm:ss");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    QString saveName = SAVES_PATH + formattedTimeMsg + ".txt";
    saveTableContents(ui->bookTable, saveName);
    QMessageBox::warning(this,"Book in the table", "The book list has been saved succesfully in \"idkwati/saves\" folder!");

}

void MainWindow::on_uploadTableBtn_clicked()
{
    QString filter = "TXT (*.txt)";
    QString fileName = QFileDialog::getOpenFileName(this, "Select a file", PROJECT_PATH, filter);
    ui->pathLbl->setText(fileName);
    loadTableContents(ui->bookTable, ui->typeOfShelve, fileName);
}

void MainWindow::on_setShelveBtn_clicked()
{
    int rowIndex = 0, flagTable = 0;
    QString bookName = ui->bookNameLineEdit->text();
    QString shelveName = ui->shelveNameLineEdit->text();

    if(bookName == ""||shelveName == ""){
        QMessageBox::warning(this,"Name", "You should enter the name of the book and the shelve. Try again.");
        return;
    }

    if(ui->typeOfShelve->findText(shelveName) != -1 ){   //found in comboBox
        for (int i = 0; i < ui->bookTable->rowCount(); i++) {
            if (ui->bookTable->item(i, 0)->text() == bookName) {
                flagTable = 1;
                rowIndex = i;
                break;
            }
        }
        if(flagTable == 1){
            ui->bookTable->setItem(rowIndex, 1, new QTableWidgetItem(shelveName));
        }else{
            QMessageBox::warning(this,"Book in the table", "Book does not exist. Try again.");
        }
    }else{
        QMessageBox::warning(this,"Shelve error", "Given shelve does not exist. You should add it separatly and try again..");

    }
}

void MainWindow::on_openBookBtn_clicked()
{
    QString bookPath;
    QString bookName = ui->bookNameLineEdit->text();
    int rowIndex = 0, flag = 0;


    for (int i = 0; i < ui->bookTable->rowCount(); i++) {
        if (ui->bookTable->item(i, 0)->text() == bookName) {
            flag = 1;
            rowIndex = i;
            break;
        }
    }
    if(flag == 1){
        bookPath =  ui->bookTable->item(rowIndex, 2)->text();
    }else{
        QMessageBox::warning(this,"Book in the table", "Book does not exist. Try again.");
    }
    bool endsWith = false;

    endsWith = bookPath.endsWith("epub",Qt::CaseInsensitive);
    if(endsWith == true){


        Widget *w = new Widget;
        w->setAttribute(Qt::WA_DeleteOnClose);

        QSettings settings;

        settings.setValue("lastFile", bookPath);
        if (!w->loadFile(bookPath, bookName)) {
            qWarning() << "Failed to load" << bookPath;
            return;
        }
        w->show();
    }else{
        QMessageBox::warning(this,"Format error", "Unsupported book format.");

    }
}
