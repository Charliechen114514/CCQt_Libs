#ifndef HISTORICALMANAGER_H
#define HISTORICALMANAGER_H
#include <QString>
#include "ccqt_readwritefile.h"

class HistoricalManager
{
private:
    HistoricalManager() = delete;
    const HistoricalManager& operator=(const HistoricalManager&) = delete;
    HistoricalManager(const HistoricalManager&) = delete;
protected:
    QString                         readFromWhere;
    HistoricalManager(const QString& readFromWhere):readFromWhere(readFromWhere){}
    virtual ~HistoricalManager() = default;
    CCQt_FileError::Error                       pathValidError;
    bool                                        loadBackHistories(QString bufs);
    void                                        setErr(CCQt_FileError::Error e){pathValidError = e;}
    virtual void                                writeBack() = 0;
public:
    bool                                        resetRecordingPath(const QString& readFromWhere);
    QString                                     loadHistoryRaw();
};

class SimpleHistoricalManager : public HistoricalManager
{
    SimpleHistoricalManager() = delete;
    const SimpleHistoricalManager& operator=(const SimpleHistoricalManager&) = delete;
    SimpleHistoricalManager(const SimpleHistoricalManager&) = delete;
protected:
    QStringList             readingCache;
    QString                 recognizeChar;
    SimpleHistoricalManager(const QString& readFromWhere, QString seperateChar):
        HistoricalManager(readFromWhere), recognizeChar(seperateChar)
    {
        CCQt_ReadFile f;
        readingCache = f.readSeperator(readFromWhere.toStdString().c_str(), recognizeChar);
        if(f.ownsError())
            pathValidError = f.getErr();
    }
    void                    writeBack() override
    {
        CCQt_WriteFile f;
        QString res;
        if(!f.writeWithSeperator(
                readingCache, QString(recognizeChar),
                readFromWhere.toStdString().c_str()))
        {
            pathValidError = f.getErr();
        }
    }
    class SimpleHistoricalManagerFactory
    {
    public:
        static std::unique_ptr<SimpleHistoricalManager> create(
            const QString& readFromWhere, QString seperateChar){
            SimpleHistoricalManager* manager = new SimpleHistoricalManager(readFromWhere, seperateChar);
            return std::unique_ptr<SimpleHistoricalManager>(manager);
        }
    };
public:
    static SimpleHistoricalManagerFactory factory;
    void                    enHist(const QString& record){readingCache.append(record);}
    bool                    removeOne(const QString& r){return readingCache.removeOne(r);}
    long long               indexOf(const QString& r){return readingCache.indexOf(r);};
    auto                    begin(){return readingCache.begin();}
    auto                    end(){return readingCache.end();}
    QStringList             getCacheCopy(){return readingCache;};
};



#endif // HISTORICALMANAGER_H
