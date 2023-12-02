#include "epubparser.h"


EpubParser::EpubParser(const QString& filePath) {
    // Add default content handlers
    contentHandlers.append(new TextHandler());
    contentHandlers.append(new ImageHandler());
    contentHandlers.append(new MetadataHandler());
    contentHandlers.append(new TableOfContentsHandler());
    contentHandlers.append(new CoverImageHandler());
    contentHandlers.append(new SpineItemHandler());

    // Open the EPUB file as a QFile
    QFile epubFile(filePath);

    if (!epubFile.open(QIODevice::ReadOnly)) {
        error = "Failed to open EPUB file.";
        return;
    }

    // Read the EPUB file content
    QXmlStreamReader xmlReader(&epubFile);

    QString baseUrl = QFileInfo(filePath).dir().path() + "/";
    QString item  = "item";
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == item) {
                // Handle content files (HTML, images, etc.)
                parseContentFile(xmlReader.attributes().value("href").toString(), baseUrl);
            }
        }
    }

    // Close the file
    epubFile.close();
}

EpubParser::~EpubParser() {
    // Cleanup content handlers
    qDeleteAll(contentHandlers);
    contentHandlers.clear();
}

void EpubParser::parseContentFile(const QString& contentFilePath, const QString& baseUrl) {
    // Open the content file as a QFile
    QFile contentFile(baseUrl + contentFilePath);

    if (!contentFile.open(QIODevice::ReadOnly)) {
        error = "Failed to open content file: " + contentFilePath;
        return;
    }

    // Read the content file content
    QString content = contentFile.readAll();

    // Let each handler process the content
    for (ContentHandler* handler : contentHandlers) {
        handler->handleContent(content, baseUrl);
    }

    // Close the content file
    contentFile.close();
}

void EpubParser::parse() {
    if (!error.isEmpty()) {
        qDebug() << "Error: " << error;
        return;
    }

    qDebug() << "Parsing EPUB file...";
}

QString EpubParser::getParsedText() const {
    return dynamic_cast<TextHandler*>(contentHandlers[0])->getResult();
}

QString EpubParser::getImagePaths() const {
    return dynamic_cast<ImageHandler*>(contentHandlers[1])->getResult();
}

QString EpubParser::getMetadata() const {
    return dynamic_cast<MetadataHandler*>(contentHandlers[2])->getResult();
}

QString EpubParser::getTableOfContents() const {
    return dynamic_cast<TableOfContentsHandler*>(contentHandlers[3])->getResult();
}

QString EpubParser::getCoverImagePath() const {
    return dynamic_cast<CoverImageHandler*>(contentHandlers[4])->getResult();
}

QString EpubParser::getSpineItems() const {
    return dynamic_cast<SpineItemHandler*>(contentHandlers[5])->getResult();
}

QString EpubParser::getError() const {
    return error;
}

void EpubParser::addContentHandler(ContentHandler* handler) {
    // Add a custom content handler
    contentHandlers.append(handler);
}
