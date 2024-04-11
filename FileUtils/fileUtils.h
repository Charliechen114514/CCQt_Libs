#ifndef FILEUTILS_H
#define FILEUTILS_H
#include <QStringList>
namespace FileUtilities{
using Path = QString;
struct FileError
{
    enum class Error{
        NoError = 0,
        ReadError = 1,
        WriteError = 2,
        FatalError = 3,
        ResourceError = 4,
        OpenError = 5,
        AbortError = 6,
        TimeOutError = 7,
        UnspecifiedError = 8,
        RemoveError = 9,
        RenameError = 10,
        PositionError = 11,
        ResizeError = 12,
        PermissionsError = 13,
        CopyError = 14
    }error;

    FileError() = default;
    FileError(const FileError& e);
    const FileError& operator=(const FileError& e);

    void        setError(Error& e){error = e;}
    void        clearError(){error = Error::NoError;}
    bool        ownsError() const;
    static bool ownsError(const FileError& e);
    static bool ownsError(const FileError::Error e);
};

using Result        = std::pair<QString, FileError::Error>;
using ResultList    = std::pair<QStringList, FileError::Error>;
static bool help_check[[maybe_unused]](const Result& res){
    return FileError::ownsError(res.second);
}

static bool help_check[[maybe_unused]](const ResultList& res){
    return FileError::ownsError(res.second);
}

class FileReader
{
private:
    Path            readingPath;
    QString         seperator;
    FileError       err;
public:
    FileReader() = default;
    FileReader(const Path& path, const QString& seperator):
        readingPath(path), seperator(seperator){}
    FileReader(const Path&& path, const QString&& seperator):
        readingPath(path), seperator(seperator){}
    Q_DISABLE_COPY(FileReader);
    void setReadingPath(const Path& read){readingPath = read;}
    void setSeperator(const QString& seperator){this->seperator = seperator;}
    QString             readAll() ;
    QStringList         readLists();
    QStringList         readLists(const QString& seperator);
    bool                isFineCurrent() const{return !err.ownsError();}
    FileError::Error    getError() const{return err.error;}
    static Result       readAll(const   Path& readPath);
    static ResultList   readLists(const Path& readPath, const QString& seperator);
};

class FileWriter
{
private:
    Path            readingPath;
    QString         seperator;
    FileError       err;
public:
    FileWriter() = default;
    FileWriter(const Path& path, const QString& seperator):
        readingPath(path), seperator(seperator){}
    FileWriter(const Path&& path, const QString&& seperator):
        readingPath(path), seperator(seperator){}
    Q_DISABLE_COPY(FileWriter);
    void setReadingPath(const Path& read){readingPath = read;}
    void setSeperator(const QString& seperator){this->seperator = seperator;}
    bool                    isFineCurrent() const{return !err.ownsError();}
    FileError::Error        getError() const{return err.error;}
    FileError::Error        write(const QStringList& buf) const;
    static FileError::Error write(  const QString& Path,
                                const QStringList &buf,
                                QString seperator=""  );
};

struct FileUtility
{
    static bool isExist(const Path& path);
    static bool isDir(const Path& path);
    static bool isFile(const Path& file);
    static QString desktopPlace();
};


}   // FileUtilities
#endif // FILEUTILS_H
