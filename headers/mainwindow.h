#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTableWidgetItem>
//#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    QTableWidget* getTableWidget();
    ~MainWindow();
    //QList<Book> books;

private slots:
    void on_createShelveBtn_clicked();

    void on_deleteShelveBtn_clicked();

    void on_uploadFileBtn_clicked();

    void on_addBookBtn_clicked();

    void on_deleteBookBtn_clicked();

    void on_saveTableBtn_clicked();

    void on_uploadTableBtn_clicked();

    void on_setShelveBtn_clicked();

    void on_openBookBtn_clicked();

   // QList<Book> on_debug_clicked(QTableWidget* table, QList<Book>& books);

private:

};
#endif // MAINWINDOW_H
