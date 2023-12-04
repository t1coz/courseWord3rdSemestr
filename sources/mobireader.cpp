#include "mobireader.h"
bool MobiHeaderRecord::parse(QDataStream &stream)
{
    quint32 identifier;
    stream >> identifier;

    if (identifier != static_cast<quint32>(MobiRecordType::Header))
    {
        qWarning() << "Invalid MOBI header record identifier: " << identifier;
        return false;
    }

    quint16 length;
    stream >> length;

    QByteArray recordData;
    recordData.resize(length);
    stream.readRawData(recordData.data(), length);

    QDataStream recordDataStream(recordData);
    recordDataStream.setByteOrder(QDataStream::LittleEndian);

    quint32 recordType;
    recordDataStream >> recordType;

    if (recordType != static_cast<quint32>(MobiRecordType::Header))
    {
        qWarning() << "Invalid MOBI header record type: " << recordType;
        return false;
    }

    recordDataStream >> bookTitle;
    qDebug() << "Book Title: " << bookTitle;

    // Handle additional header fields as needed

    return true;
}

bool MobiTextRecord::parse(QDataStream &stream)
{
    quint32 identifier;
    stream >> identifier;

    if (identifier != static_cast<quint32>(MobiRecordType::Text))
    {
        qWarning() << "Invalid MOBI text record identifier: " << identifier;
        return false;
    }

    quint16 length;
    stream >> length;

    QByteArray recordData;
    recordData.resize(length);
    stream.readRawData(recordData.data(), length);

    QDataStream recordDataStream(recordData);
    recordDataStream.setByteOrder(QDataStream::LittleEndian);

    quint32 recordType;
    recordDataStream >> recordType;

    if (recordType != static_cast<quint32>(MobiRecordType::Text))
    {
        qWarning() << "Invalid MOBI text record type: " << recordType;
        return false;
    }

    recordDataStream >> textContent;
    qDebug() << "Text Content: " << textContent;

    // Handle additional text record fields as needed

    return true;
}

bool MobiImageRecord::parse(QDataStream &stream)
{
    quint32 identifier;
    stream >> identifier;

    if (identifier != static_cast<quint32>(MobiRecordType::Image))
    {
        qWarning() << "Invalid MOBI image record identifier: " << identifier;
        return false;
    }

    quint16 length;
    stream >> length;

    imageData.resize(length);
    stream.readRawData(imageData.data(), length);

    qDebug() << "Image Record: Image size - " << length;

    // Handle additional image record fields as needed

    return true;
}

bool MobiAnotherRecordType::parse(QDataStream &stream)
{
    quint32 identifier;
    stream >> identifier;

    if (identifier != static_cast<quint32>(MobiRecordType::AnotherRecord))
    {
        qWarning() << "Invalid MOBI another record type identifier: " << identifier;
        return false;
    }

    quint16 length;
    stream >> length;

    QByteArray recordData;
    recordData.resize(length);
    stream.readRawData(recordData.data(), length);

    QDataStream recordDataStream(recordData);
    recordDataStream.setByteOrder(QDataStream::LittleEndian);

    quint32 recordType;
    recordDataStream >> recordType;

    if (recordType != static_cast<quint32>(MobiRecordType::AnotherRecord))
    {
        qWarning() << "Invalid MOBI another record type: " << recordType;
        return false;
    }

    recordDataStream >> someInfo;
    qDebug() << "Another Record Type: " << someInfo;

    // Handle additional another record type fields as needed

    return true;
}
