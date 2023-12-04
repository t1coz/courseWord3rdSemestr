#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QComboBox>
using namespace std ;

void saveTableContents(QTableWidget* tableWidget, const QString& fileName);
void loadTableContents(QTableWidget* tableWidget, QComboBox* comboWidget, const QString& fileName);
#endif
