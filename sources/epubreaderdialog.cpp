#include "epubreaderdialog.h"
#include "ui_epubreaderdialog.h"

EpubReaderDialog::EpubReaderDialog(const QList<ContentHandler*>& contentHandlers, QWidget* parent)
    : QDialog(parent)
{
    mainLayout = new QVBoxLayout(this);

    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    // Create tabs and set up content
    metadataTab = new QWidget(this);
    tocTab = new QWidget(this);
    coverImageTab = new QWidget(this);
    spineItemsTab = new QWidget(this);
    otherContentTab = new QWidget(this);

    setupTabs(contentHandlers);

    // Set up main layout
    tabWidget->addTab(metadataTab, "Metadata");
    tabWidget->addTab(tocTab, "Table of Contents");
    tabWidget->addTab(coverImageTab, "Cover Image");
    tabWidget->addTab(spineItemsTab, "Spine Items");
    tabWidget->addTab(otherContentTab, "Other Content");

    setWindowTitle("EPUB Reader");
    setFixedSize(800, 600);
}

void EpubReaderDialog::setupTabs(const QList<ContentHandler*>& contentHandlers) {
    metadataTab->setLayout(new QVBoxLayout(metadataTab));
    tocTab->setLayout(new QVBoxLayout(tocTab));
    coverImageTab->setLayout(new QVBoxLayout(coverImageTab));
    spineItemsTab->setLayout(new QVBoxLayout(spineItemsTab));
    otherContentTab->setLayout(new QVBoxLayout(otherContentTab));

    metadataTextEdit = new QTextEdit(metadataTab);
    tocTextEdit = new QTextEdit(tocTab);
    coverImageLabel = new QLabel(coverImageTab);
    spineItemsTextEdit = new QTextEdit(spineItemsTab);
    otherContentGroupBox = new QGroupBox("Other Content", otherContentTab);
    otherContentLayout = new QVBoxLayout(otherContentGroupBox);

    metadataTextEdit->setReadOnly(true);
    tocTextEdit->setReadOnly(true);
    spineItemsTextEdit->setReadOnly(true);

    metadataTab->layout()->addWidget(metadataTextEdit);
    tocTab->layout()->addWidget(tocTextEdit);
    coverImageTab->layout()->addWidget(coverImageLabel);
    spineItemsTab->layout()->addWidget(spineItemsTextEdit);
    otherContentTab->layout()->addWidget(otherContentGroupBox);

    // Display metadata, table of contents, cover image, and spine items
    for (ContentHandler* handler : contentHandlers) {
        if (dynamic_cast<MetadataHandler*>(handler))
            metadataTextEdit->setPlainText(handler->getResult());
        else if (dynamic_cast<TableOfContentsHandler*>(handler))
            tocTextEdit->setPlainText(handler->getResult());
        else if (dynamic_cast<CoverImageHandler*>(handler))
            coverImageLabel->setPixmap(QPixmap(handler->getResult()));
        else if (dynamic_cast<SpineItemHandler*>(handler))
            spineItemsTextEdit->setPlainText(handler->getResult());
        else {
            QLabel* resultLabel = new QLabel(handler->getResult(), otherContentGroupBox);
            otherContentLayout->addWidget(resultLabel);
        }
    }
}
EpubReaderDialog::~EpubReaderDialog()
{
    delete ui;
}
