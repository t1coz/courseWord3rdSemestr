#ifndef MOBIFILE_H
#define MOBIFILE_H

#include <QFile>
#include <QDataStream>
#include <QList>
#include "mobireader.h"

class MobiFile
{
public:
    MobiFile(const QString &filePath) : filePath(filePath) {}

    bool open();
    bool validateMobiFile();
    void close();
    bool atEnd() const;
    MobiRecord *readRecord();
    bool parseMobiFile();

private:
    MobiRecord *createRecord(MobiRecordType recordType);

private:
    QFile file;
    QDataStream stream;
    const QString filePath;
    QList<MobiRecord *> parsedRecords;
};

#endif // MOBIFILE_H
