#ifndef HANDLERS_H
#define HANDLERS_H
#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDir>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QImageReader>

class ContentHandler {
public:
    virtual ~ContentHandler() {}

    virtual void handleContent(const QString& content, const QString& baseUrl) = 0;
    virtual QString getResult() const = 0;
};

// Text handler
class TextHandler : public ContentHandler {
public:
    void handleContent(const QString& content, const QString& baseUrl) override ;
    QString getResult() const override {return parsedText;}

private:
    QString parsedText;
};

// Image handler
class ImageHandler : public ContentHandler {
public:
    void handleContent(const QString& content, const QString& baseUrl) override;
    QString getResult() const override {return imagePaths.join("\n");}

private:
    QStringList imagePaths;
    QString convertToAbsoluteUrl(const QString& url, const QString& baseUrl) const ;
};

// Metadata handler
class MetadataHandler : public ContentHandler {
public:
    void handleContent(const QString& content, const QString& baseUrl) override;
    QString getResult() const override {return metadata;}

private:
    QString metadata;
};

// Table of Contents handler
class TableOfContentsHandler : public ContentHandler {
public:
    void handleContent(const QString& content, const QString& baseUrl) override;
    QString getResult() const override {return tocContent;}

private:
    QString tocContent;
};

class CoverImageHandler : public ContentHandler {
public:
    void handleContent(const QString& content, const QString& baseUrl) override;

    QString getResult() const override {
        return coverImagePath;
    }

private:
    QString coverImagePath;
    QString convertToAbsoluteUrl(const QString& url, const QString& baseUrl) const ;
};

// Spine item handler
class SpineItemHandler : public ContentHandler {
public:
    void handleContent(const QString& content, const QString& baseUrl) override;

    QString getResult() const override {return spineItems.join("\n");}

private:
    QStringList spineItems;
};
#endif // HANDLERS_H
