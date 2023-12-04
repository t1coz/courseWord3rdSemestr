#ifndef MOBIDIALOG_H
#define MOBIDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include "mobireader.h"
namespace Ui {
class MobiDialog;
}

class MobiDialog : public QDialog
{
    Q_OBJECT

public:
    MobiDialog(QWidget *parent = nullptr);
    ~MobiDialog();
private slots:
    void openMobiFile();
    void displayParsedInformation(const QList<MobiRecord *> &parsedRecords);
    void renderImage(const QByteArray &imageData);
private:
    QPushButton *openButton;
    QLabel *bookTitleLabel;
    QLabel *fileSizeLabel;
    QLabel *recordCountLabel;
    QLabel *imageLabel;
    Ui::MobiDialog *ui;
};

#endif // MOBIDIALOG_H
