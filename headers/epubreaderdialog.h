#ifndef EPUBREADERDIALOG_H
#define EPUBREADERDIALOG_H
#include "handlers.h"
#include <QTextEdit>
#include <QDialog>
#include <QGroupBox>
#include <QTabWidget>

namespace Ui {
class EpubReaderDialog;
}

class EpubReaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EpubReaderDialog(const QList<ContentHandler*>& contentHandlers, QWidget* parent = nullptr);
    ~EpubReaderDialog();

private:
    Ui::EpubReaderDialog *ui;
    QVBoxLayout* mainLayout;

    QTabWidget* tabWidget;
    QWidget* metadataTab;
    QWidget* tocTab;
    QWidget* coverImageTab;
    QWidget* spineItemsTab;
    QWidget* otherContentTab;

    QTextEdit* metadataTextEdit;
    QTextEdit* tocTextEdit;
    QLabel* coverImageLabel;
    QTextEdit* spineItemsTextEdit;
    QGroupBox* otherContentGroupBox;
    QVBoxLayout* otherContentLayout;

    void setupTabs(const QList<ContentHandler*>& contentHandlers);
};

#endif // EPUBREADERDIALOG_H
