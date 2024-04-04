#ifndef IMAGEBROWSERCORE_H
#define IMAGEBROWSERCORE_H
#include <QStringList>
#include <QObject>
#include <QImage>
#include "ccqt_readwritefile.h"

class ImageBrowserCore :public QObject
{
    Q_OBJECT
    ImageBrowserCore(const ImageBrowserCore&) = delete;
    const ImageBrowserCore& operator=(const ImageBrowserCore&) = delete;
private:
    QStringList             imageLists;
    int                     currentFocusIndex = 0;
    bool                    checkIndexVadilityCore(int index) const;
    bool                    checkIndexVadility(int index);
    bool                    isOverFlow(int index) const;
    bool                    isUnderFlow(int index) const;
    enum class IndexState
    {
        UNDER_FLOW,
        NO_FLOW,
        OVER_FLOW
    }state;
    CCQt_FileError          err;
    void                    setState(IndexState i){state = i;}
public:
    ~ImageBrowserCore()     = default;
    ImageBrowserCore()      = default;
    static QImage*  directAt(const QString& l);
    void                    enImages(const QString& l){imageLists += l;}
    void                    enImages(const QStringList& l){imageLists += l;}
    void                    enImagesWithoutDuplicate(const QString l){if(!imageLists.contains(l))
                                                                            imageLists += l;}
    bool                    removeImage(const QString l){return imageLists.removeOne(l);}
    bool                    removeSameImageAll(const QString l){return imageLists.removeAll(l);}
    bool                    removeIndex(const int index);
    bool                    removeIndexs(const QList<int>& indexs);
    QImage*                 at(int index);
    QImage*                 operator[](int index);
    QImage*                 toNext();
    QImage*                 viewFirst(){return jumpTo(0);}
    QImage*                 viewLast(){return jumpTo(imageLists.size() - 1);}
    QImage*                 toPrevious();
    QImage*                 getCurrentImage();
    QImage*                 jumpTo(int index);
    int                     size(){return imageLists.size();}
    int                     search(const QString& l) const{return imageLists.indexOf(l);}
    IndexState              checkForState(){return state;}
public slots:
    bool                    setCurrentViewIndex(int index);
};

#endif // IMAGEBROWSERCORE_H
