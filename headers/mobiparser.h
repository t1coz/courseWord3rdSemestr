#ifndef MOBIPARSER_H
#define MOBIPARSER_H

#include <QList>
#include "mobireader.h"
#include "MobiFile.h"

class MobiReader
{
public:
    bool openMobiFile(const QString &filePath);

    const QList<MobiRecord *> &getParsedRecords() const;

private:
    void parseRecords(MobiFile &mobiFile);

private:
    QList<MobiRecord *> parsedRecords;
};

#endif // MOBIPARSER_H
