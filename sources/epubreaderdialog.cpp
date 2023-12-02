#include "epubreaderdialog.h"
#include "ui_epubreaderdialog.h"

EpubReaderDialog::EpubReaderDialog(EpubParser* epubParser, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::EpubReaderDialog)
{
    ui->setupUi(this);
    mainLayout = new QVBoxLayout(this);
    contentScrollArea = new QScrollArea(this);
    contentWidget = new QWidget(this);
    contentLayout = new QVBoxLayout(contentWidget);
    textEdit = new QTextEdit(contentWidget);
    imageLabel = new QLabel(contentWidget);

    setupUI(epubParser);
    displayContent(epubParser);
}

void EpubReaderDialog::setupUI(EpubParser* epubParser) {
    // Set up the content scroll area
    contentScrollArea->setWidgetResizable(true);
    contentScrollArea->setWidget(contentWidget);
    mainLayout->addWidget(contentScrollArea);

    // Set up the content layout
    contentLayout->addWidget(textEdit);
    contentLayout->addWidget(imageLabel);

    setWindowTitle("EPUB Reader");
    setFixedSize(800, 600);
}

void EpubReaderDialog::displayContent(EpubParser* epubParser) {
    if (!epubParser->getError().isEmpty()) {
        textEdit->setPlainText(epubParser->getError());
        return;
    }

    // Display parsed content in the text edit
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
