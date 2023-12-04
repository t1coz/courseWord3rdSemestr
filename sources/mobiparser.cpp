#include "mobiparser.h"

#include "mobireader.h"
#include "mobifile.h"
#include <QDebug>

bool MobiReader::openMobiFile(const QString &filePath)
{
    MobiFile mobiFile(filePath);
    if (!mobiFile.open())
    {
        return false;
    }

    if (!mobiFile.validateMobiFile())
    {
        mobiFile.close();
        return false;
    }

    parseRecords(mobiFile);

    mobiFile.close();
    return true;
}

const QList<MobiRecord *> &MobiReader::getParsedRecords() const
{
    return parsedRecords;
}

void MobiReader::parseRecords(MobiFile &mobiFile)
{
    while (!mobiFile.atEnd())
    {
        MobiRecord *record = mobiFile.readRecord();
        if (record)
        {
            parsedRecords.append(record);
        }
    }
}
