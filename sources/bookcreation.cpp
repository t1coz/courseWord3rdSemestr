#include "bookcreation.h"
#include "ui_bookcreation.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
bookCreation::bookCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookCreation)
{
    ui->setupUi(this);
}

bookCreation::~bookCreation()
{
    delete ui;
}


void bookCreation::on_uploadBtn_clicked()
{
    QString filter = "PDF (*.pdf) ;;  EPUB (*.epub) ;; Mobi (*.mobi)";
    QString fileName = QFileDialog::getOpenFileName(this, "Select a file", QDir::homePath(),filter);
    ui->pathLbl->setText(fileName);

//    if(bookName == "" && ){

//    }
}


void bookCreation::on_pushButton_2_clicked()
{
    QString filePath = ui->pathLbl->text();
    QString bookName = ui->nameLineEdit->text();
    if(bookName == "" || filePath == "no path uploaded"){
        QMessageBox::warning(this,"Name", "You should upload the book and enter the name.\nTry again.");
    }else{

    }
}

void bookCreation::on_pushButton_clicked()
{
    this->close();
}

