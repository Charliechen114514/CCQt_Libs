#include "ccqt_readwritefile.h"
#include <QFile>

class Adapter_CCFileError_QFileError
{
public:
    static CCQt_FileError::Error toCCFileError(QFile::FileError e){
        return static_cast<CCQt_FileError::Error>(static_cast<int>(e));
    }
};


QString CCQt_ReadFile::readAll(const char* path)
{
    QFile reader(path);
    reader.open(QIODevice::ReadOnly);
    if(!reader.isOpen())
    {
        err.setErr(Adapter_CCFileError_QFileError::toCCFileError(reader.error()));
        return "";
    }
    QString tmp = reader.readAll();
    reader.close();
    return tmp;
}

QStringList CCQt_ReadFile::readLines(const char* path)
{
    QFile reader(path);
    reader.open(QIODevice::ReadOnly);
    if(!reader.isOpen())
    {
        err.setErr(Adapter_CCFileError_QFileError::toCCFileError(reader.error()));
        return QStringList();
    }
    QStringList tmp;
    while(!reader.atEnd())
        tmp.push_back(reader.readLine());
    reader.close();
    return tmp;
}


QStringList CCQt_ReadFile::readSeperator(const char* path, const QString seperator)
{
    return readAll(path).split(seperator);
}


bool CCQt_WriteFile::write(QString& str, const char* path)
{
    QFile writer(path);
    writer.error();
    writer.open(QIODevice::WriteOnly);
    if(!writer.isOpen())
    {
        err.setErr(Adapter_CCFileError_QFileError::toCCFileError(writer.error()));
        return false;
    }

    bool st = writer.write(str.toStdString().c_str()) != -1;
    writer.close();
    return st;
}

bool CCQt_WriteFile::writeWithSeperator(QStringList& l, const QString seperator, const char* path)
{
    QString tmp;
    for(auto i : l)
        tmp += i + seperator;
    tmp.removeLast();
    return write(tmp, path);
}




















