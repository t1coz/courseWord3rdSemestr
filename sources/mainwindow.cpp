#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bookcreation.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
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

void MainWindow::on_pushButton_clicked()
{
    bookCreation bookCreationDialog;
    bookCreationDialog.setModal(true);
    bookCreationDialog.exec();
}


void MainWindow::on_createShelveBtn_clicked()
{
    QString shelveName = ui->shelveNameLineEdit->text();
    if(shelveName == ""){
        QMessageBox::warning(this,"Shelve error", "You enter valid name. Try again.");
    }else{
        ui->typeOfShelve->addItem(shelveName);
    }
    //shelveNameLineEdit
}

