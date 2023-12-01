#ifndef EPUBPARSER_H
#define EPUBPARSER_H
#include "handlers.h"
class EpubParser {
public:
    explicit EpubParser(const QString& filePath);

    void parse();

    QList<ContentHandler*> getContentHandlers() const;

    QString getError() const;

private:
    QList<ContentHandler*> contentHandlers;
    QString error;

    void parseContentFile(const QString& contentFilePath, const QString& baseUrl);
};

#endif // EPUBPARSER_H
