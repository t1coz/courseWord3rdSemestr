#include "handlers.h"

void TextHandler::handleContent(const QString& content, const QString& baseUrl) {
    // Process text content
    parsedText += content;
}


void ImageHandler::handleContent(const QString& content, const QString& baseUrl){
    // Process image content
    QString absoluteUrl = convertToAbsoluteUrl(content, baseUrl);
    imagePaths.append(absoluteUrl);
}
QString ImageHandler::convertToAbsoluteUrl(const QString& url, const QString& baseUrl) const {
    if (url.startsWith("http") || url.startsWith("/")) {
        // Already an absolute URL or starts with a root path
        return url;
    } else {
        // Convert to absolute URL
        return baseUrl + url;
    }
}

void MetadataHandler::handleContent(const QString& content, const QString& baseUrl){
    // Process metadata content
    metadata += content;
}

void TableOfContentsHandler::handleContent(const QString& content, const QString& baseUrl){
    // Process table of contents content
    tocContent += content;
}
QString CoverImageHandler::convertToAbsoluteUrl(const QString& url, const QString& baseUrl) const {
    if (url.startsWith("http") || url.startsWith("/")) {
        // Already an absolute URL or starts with a root path
        return url;
    } else {
        // Convert to absolute URL
        return baseUrl + url;
    }
}
void CoverImageHandler::handleContent(const QString& content, const QString& baseUrl){
    // Process cover image content
    coverImagePath = convertToAbsoluteUrl(content, baseUrl);
}
void SpineItemHandler::handleContent(const QString& content, const QString& baseUrl) {
    // Process spine item content
    spineItems.append(content);
}