#ifndef EPUBPARSER_H
#define EPUBPARSER_H
#include "handlers.h"

class EpubParser {
public:
    explicit EpubParser(const QString& filePath);
    ~EpubParser();

    void parse();

    QString getParsedText() const;
    QString getImagePaths() const;
    QString getMetadata() const;
    QString getCoverImagePath() const;
    QString getTableOfContents() const;
    QString getStylesheets() const;
    QString getSpineItems() const;
    QString getError() const;

    void addContentHandler(ContentHandler* handler);

private:
    QList<ContentHandler*> contentHandlers;
    QString error;

    void parseContentFile(const QString& contentFilePath, const QString& baseUrl);
};

#endif // EPUBPARSER_H
