#include "epubreaderdialog.h"
#include "ui_epubreaderdialog.h"
#include "epubparser.h"
EpubReaderDialog::EpubReaderDialog(EpubParser* epubParser, QWidget* parent)
    : QDialog(parent),
     ui(new Ui::EpubReaderDialog)
{
    mainLayout = new QVBoxLayout(this);
    titleLabel = new QLabel("EPUB Reader", this);
    textEdit = new QTextEdit(this);
    imageLabel = new QLabel(this);

    setupUI(epubParser);
    displayContent(epubParser);
}

void EpubReaderDialog::setupUI(EpubParser* epubParser) {
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(imageLabel);

    setWindowTitle("EPUB Reader");
    setFixedSize(800, 600);
}

void EpubReaderDialog::displayContent(EpubParser* epubParser) {
    if (!epubParser->getError().isEmpty()) {
        QMessageBox::critical(this, "Error", epubParser->getError());
        return;
    }

    // Display parsed text content in the text edit
    textEdit->setPlainText(epubParser->getParsedText());

    // Display cover image
    QString imagePath = epubParser->getCoverImagePath();
    if (!imagePath.isEmpty()) {
        QImageReader imageReader(imagePath);
        QSize imageSize = imageReader.size();
        imageLabel->setPixmap(QPixmap::fromImageReader(&imageReader));
        imageLabel->setFixedSize(imageSize);
    }
}
EpubReaderDialog::~EpubReaderDialog()
{
    delete ui;
}
