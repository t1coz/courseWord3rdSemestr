#include "data.h"

void saveTableContents(QTableWidget* tableWidget, const QString& fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (int row = 0; row < tableWidget->rowCount(); ++row)
    {
        for (int column = 0; column < tableWidget->columnCount(); ++column)
        {
            QTableWidgetItem* item = tableWidget->item(row, column);
            if (item)
                out << item->text();
            out << "\t";
        }
        out << "\n";
    }
    file.close();
}
void loadTableContents(QTableWidget* tableWidget, QComboBox* comboWidget, const QString& fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    tableWidget->setRowCount(0) ;
    tableWidget->clear() ;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split("\t");
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        for (int column = 0; column < fields.size(); ++column)
        {
            QTableWidgetItem* item = new QTableWidgetItem(fields[column]);
            tableWidget->setItem(row, column, item);
        }
    }
    for (int i = 0; i < tableWidget->rowCount(); i++) {
        QString givenShelve = tableWidget->item(i, 1)->text()  ;
        if (comboWidget->findText(givenShelve) == -1) {
            comboWidget->addItem(givenShelve);
        }
    }
    file.close();
}
