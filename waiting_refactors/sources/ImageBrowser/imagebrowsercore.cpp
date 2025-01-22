#include "imagebrowsercore.h"
#include <QFile>
bool ImageBrowserCore::checkIndexVadilityCore(int index) const
{
    return index >=0 && index < imageLists.size();
}

QImage* ImageBrowserCore::directAt(const QString& l)
{
    return new QImage(l);
}

bool ImageBrowserCore::checkIndexVadility(int index)
{
    if(!checkIndexVadilityCore(index))
    {
        if(isUnderFlow(index))
        {
            setState(IndexState::UNDER_FLOW);
            return false;
        }
        else
        {
            setState(IndexState::OVER_FLOW);
            return false;
        }
    }
    return true;
}

bool ImageBrowserCore::isOverFlow(int index) const
{
    return index >= imageLists.size();
}
bool ImageBrowserCore::isUnderFlow(int index) const
{
    return index < 0;
}

bool ImageBrowserCore::removeIndex(const int index)
{
    if(!checkIndexVadility(index))
        return false;
    imageLists.remove(index);
    return true;
}
bool ImageBrowserCore::removeIndexs(const QList<int>& indexs)
{
    bool flag = true;
    for(const int& index : indexs)
        flag &= removeIndex(index);
    return flag;
}

QImage*  ImageBrowserCore::at(int index)
{
    if(!checkIndexVadility(index))
        return nullptr;

    QString path = imageLists.at(index);
    if(!QFile::exists(path))
    {
        err.setErr(CCQt_FileError::Error::OpenError);
        return nullptr;
    }

    return new QImage(path);
}

QImage* ImageBrowserCore::operator[](int index){
    return at(index);
}

QImage* ImageBrowserCore::jumpTo(int index)
{
    if(!checkIndexVadility(index))
        return nullptr;

    QString path = imageLists.at(index);
    if(!QFile::exists(path))
    {
        err.setErr(CCQt_FileError::Error::OpenError);
        return nullptr;
    }
    currentFocusIndex = index;
    return new QImage(path);
}


QImage* ImageBrowserCore::toNext()
{
    return jumpTo(currentFocusIndex + 1);
}
QImage* ImageBrowserCore::toPrevious()
{
    return jumpTo(currentFocusIndex - 1);
}

QImage* ImageBrowserCore::getCurrentImage()
{
    return jumpTo(currentFocusIndex);
}

bool ImageBrowserCore::setCurrentViewIndex(int index)
{
    if(!checkIndexVadility(index))
        return false;
    currentFocusIndex = index;
    return true;
}


