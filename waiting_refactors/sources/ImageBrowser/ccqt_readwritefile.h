#ifndef CCQT_READWRITEFILE_H
#define CCQT_READWRITEFILE_H
#include <QStringList>

class CCQt_FileError
{
public:
    enum class Error
    {
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
    };
    void    setErr(Error e){err = e;}
    Error&  getErr(){return err;}
    void    clearError(){err = Error::NoError;}
private:
    Error   err = Error::NoError;
};


class CCQt_ReadFile
{
public:
    QString      readAll(const char* path);
    QStringList  readLines(const char* path);
    QStringList  readSeperator(const char* path, const QString seperator);
    CCQt_FileError::Error& getErr(){return err.getErr();}
    bool ownsError(){return err.getErr() != CCQt_FileError::Error::NoError;};
private:
    CCQt_FileError  err;
};

class CCQt_WriteFile
{
public:
    bool write(QString& str, const char* path);
    bool writeWithSeperator(QStringList& l, const QString seperator, const char* path);
    CCQt_FileError::Error& getErr(){return err.getErr();}
    bool ownsError(){return err.getErr() != CCQt_FileError::Error::NoError;};
private:
    CCQt_FileError  err;
};



#endif // CCQT_READWRITEFILE_H
