#include "epubparser.h"


EpubParser::EpubParser(const QString& filePath) {
    // Create content handlers
    contentHandlers.append(new TextHandler());
    contentHandlers.append(new ImageHandler());
    contentHandlers.append(new MetadataHandler());
    contentHandlers.append(new TableOfContentsHandler());
    contentHandlers.append(new CoverImageHandler());

    // Open the EPUB file as a QFile
    QFile epubFile(filePath);

    if (!epubFile.open(QIODevice::ReadOnly)) {
        error = "Failed to open EPUB file.";
        return;
    }

    // Read the EPUB file content
    QXmlStreamReader xmlReader(&epubFile);

    QString baseUrl = QFileInfo(filePath).dir().path() + "/";
    QString item = "item";
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

    // Additional parsing logic can be added here
    qDebug() << "Additional parsing logic...";
}

QString EpubParser::getError() const {
    return error;
}
