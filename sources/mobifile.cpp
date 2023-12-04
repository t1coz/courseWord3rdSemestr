#include "mobifile.h"

#include <QDebug>

bool MobiFile::open()
{
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open MOBI file: " << file.errorString();
        return false;
    }

    stream.setDevice(&file);
    return true;
}

bool MobiFile::validateMobiFile()
{
    quint32 identifier;
    stream >> identifier;

    if (identifier != 0x4D4F4249) // MOBI identifier
    {
        qWarning() << "Invalid MOBI file. Expected MOBI identifier, but found: " << identifier;
        return false;
    }

    return true;
}

void MobiFile::close()
{
    file.close();
}

bool MobiFile::atEnd() const
{
    return stream.atEnd();
}

MobiRecord *MobiFile::readRecord()
{
    quint32 recordType;
    stream >> recordType;

    MobiRecord *record = createRecord(static_cast<MobiRecordType>(recordType));
    if (record)
    {
        if (!record->parse(stream))
        {
            qWarning() << "Failed to parse record of type: " << static_cast<quint32>(recordType);
            delete record;
            return nullptr;
        }
    }

    return record;
}

bool MobiFile::parseMobiFile()
{
    while (!stream.atEnd())
    {
        MobiRecord *record = readRecord();
        if (record)
        {
            parsedRecords.append(record);
        }
    }

    return true;
}

MobiRecord *MobiFile::createRecord(MobiRecordType recordType)
{
    switch (recordType)
    {
    case MobiRecordType::Header:
        return new MobiHeaderRecord();
    case MobiRecordType::Text:
        return new MobiTextRecord();
    case MobiRecordType::Image:
        return new MobiImageRecord();
    case MobiRecordType::AnotherRecord:
        return new MobiAnotherRecordType();
    // Add more cases for other record types
    default:
        qWarning() << "Unsupported record type: " << static_cast<quint32>(recordType);
        return nullptr;
    }
}
