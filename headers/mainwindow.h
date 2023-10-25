#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTableWidgetItem>
//#include <QtPdf>
//#include <QtPdf/QPdfPageNavigator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
