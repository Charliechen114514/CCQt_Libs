#include <QFileInfo>
#include <QStandardPaths>
#include "fileUtils.h"
using namespace FileUtilities;

struct ErrorAdapter
{
    static FileError::Error errorAdapter(QFile::FileError f){
        return FileError::Error{static_cast<int>(f)};
    }
};

const FileError& FileError::operator=(const FileError& e){
    if(&e == this)
        return *this;
    this->error = e.error;
    return *this;
}

FileError::FileError(const FileError& e)
{
    this->error = e.error;
}

bool FileError::ownsError() const{
    return error != Error::NoError;
}

bool FileError::ownsError(const FileError& e) {
    return Error::NoError != e.error;
}

bool FileError::ownsError(const FileError::Error e){
    return e != Error::NoError;
}

Result FileReader::readAll(const Path& readPath)
{
    QFile f(readPath);
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
    {
        return {"", ErrorAdapter::errorAdapter(f.error())};
    }

    return {f.readAll(), ErrorAdapter::errorAdapter(f.error())};

}

ResultList FileReader::readLists(const Path& readPath, const QString& seperator)
{
    Result res = readAll(readPath);
    if(FileError::ownsError(res.second))
        return {QStringList(), res.second};

    return {res.first.split(seperator), res.second};
}

QString FileReader::readAll()
{
    Result res = readAll(this->readingPath);
    err.error = res.second;
    return res.first;
}
QStringList FileReader::readLists()
{
    ResultList res = readLists(this->readingPath, this->seperator);
    err.error = res.second;
    return res.first;
}

QStringList FileReader::readLists(const QString& seperator)
{
    ResultList res = readLists(this->readingPath, seperator);
    setSeperator(seperator);
    err.error = res.second;
    return res.first;
}

FileError::Error FileWriter::write(  const QString& Path,
                const QStringList& buf,
                QString seperator)
{
    QFile f(Path);
    f.open(QIODevice::WriteOnly);
    if(!f.isOpen())
        return ErrorAdapter::errorAdapter(f.error());

    QString res;
    for(const auto& each : buf)
        res += each + seperator;

    f.write(res.toStdString().c_str());
    return ErrorAdapter::errorAdapter(f.error());
}

FileError::Error FileWriter::write(const QStringList& buf) const
{
    return write(this->readingPath, buf, this->seperator);
}

bool FileUtility::isExist(const Path& path)
{
    return QFileInfo::exists(path);
}
bool FileUtility::isDir(const Path& path)
{
    return QFileInfo(path).isDir();
}
bool FileUtility::isFile(const Path& file)
{
    return QFileInfo(file).isFile();
}

QString FileUtility::desktopPlace()
{
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}
