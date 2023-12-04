#ifndef MOBIREADER_H
#define MOBIREADER_H

#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QTextBrowser>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QByteArray>
#include <zlib.h>

enum class MobiRecordType : quint32
{
    Header = 0xE9,
    Text = 0xE8,
    Image = 0xE7, // Hypothetical image record type
    AnotherRecord = 0xE6, // Hypothetical additional record type
    // Add more record types as needed
};

class MobiRecord
{
public:
    virtual ~MobiRecord() {}

    virtual bool parse(QDataStream &stream) = 0;
};

class MobiHeaderRecord : public MobiRecord
{
public:
    QString bookTitle;

    bool parse(QDataStream &stream) override;
};

class MobiTextRecord : public MobiRecord
{
public:
    QString textContent;

    bool parse(QDataStream &stream) override;
};

class MobiImageRecord : public MobiRecord
{
public:
    QByteArray imageData;

    bool parse(QDataStream &stream) override;
};

class MobiAnotherRecordType : public MobiRecord
{
public:
    QString someInfo;

    bool parse(QDataStream &stream) override;
};
#endif // MOBIREADER_H
