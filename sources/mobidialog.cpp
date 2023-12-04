#include "mobidialog.h"
#include "mobiparser.h"
#include "ui_mobidialog.h"
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>

MobiDialog::MobiDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("MOBI Reader");

    QVBoxLayout *layout = new QVBoxLayout();

    openButton = new QPushButton("Open MOBI File");
    connect(openButton, &QPushButton::clicked, this, &MobiDialog::openMobiFile);

    bookTitleLabel = new QLabel("Book Title: N/A");
    fileSizeLabel = new QLabel("File Size: N/A");
    recordCountLabel = new QLabel("Record Count: N/A");

    imageLabel = new QLabel();
    imageLabel->setScaledContents(true); // Ensure the image is scaled to fit the QLabel

    layout->addWidget(openButton);
    layout->addWidget(bookTitleLabel);
    layout->addWidget(fileSizeLabel);
    layout->addWidget(recordCountLabel);
    layout->addWidget(imageLabel);

    setLayout(layout);
}

void MobiDialog::openMobiFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open MOBI File", QString(), "MOBI Files (*.mobi)");
    if (!filePath.isEmpty())
    {
        MobiReader mobiReader;
        if (mobiReader.openMobiFile(filePath))
        {
            displayParsedInformation(mobiReader.getParsedRecords());
        }
    }
}

void MobiDialog::displayParsedInformation(const QList<MobiRecord *> &parsedRecords)
{
    QDialog *infoDialog = new QDialog(this);
    infoDialog->setWindowTitle("Parsed Information");

    QVBoxLayout *layout = new QVBoxLayout();
    QTextBrowser *textBrowser = new QTextBrowser();

    for (const MobiRecord *record : parsedRecords)
    {
        const MobiHeaderRecord *headerRecord = dynamic_cast<const MobiHeaderRecord *>(record);
        const MobiTextRecord *textRecord = dynamic_cast<const MobiTextRecord *>(record);
        const MobiImageRecord *imageRecord = dynamic_cast<const MobiImageRecord *>(record);

        if (headerRecord)
        {
            textBrowser->append("Book Title: " + headerRecord->bookTitle);
        }
        else if (textRecord)
        {
            textBrowser->append("Text Content: " + textRecord->textContent);
        }
        else if (imageRecord)
        {
            textBrowser->append("Image Record: Image size - " + QString::number(imageRecord->imageData.size()));

            // Render the image
            renderImage(imageRecord->imageData);
        }
        // Add similar cases for other record types

        // Note: You may want to provide a more sophisticated way of displaying the information
        // based on the specific record types you have in your MOBI files.
    }

    layout->addWidget(textBrowser);
    infoDialog->setLayout(layout);

    infoDialog->exec();
}

void MobiDialog::renderImage(const QByteArray &imageData)
{
    // Load image from data and set it to the imageLabel
    QImage image;
    if (image.loadFromData(imageData))
    {
        imageLabel->setPixmap(QPixmap::fromImage(image));
    }
    else
    {
        qWarning() << "Failed to load image from data.";
    }
}
MobiDialog::~MobiDialog()
{
    delete ui;
}
