#ifndef EPUBREADERDIALOG_H
#define EPUBREADERDIALOG_H
#include "epubparser.h"

#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QDir>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTabWidget>
#include <QScrollArea>
namespace Ui {
class EpubReaderDialog;
}

class EpubReaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EpubReaderDialog(EpubParser* epubParser, QWidget* parent = nullptr);
    ~EpubReaderDialog();

private:
    Ui::EpubReaderDialog *ui;

    QVBoxLayout* mainLayout;
    QScrollArea* contentScrollArea;
    QWidget* contentWidget;
    QVBoxLayout* contentLayout;
    QTextEdit* textEdit;
    QLabel* imageLabel;

    void setupUI(EpubParser* epubParser);
    void displayContent(EpubParser* epubParser);
};

#endif // EPUBREADERDIALOG_H
