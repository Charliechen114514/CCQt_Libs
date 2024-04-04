#ifndef IMAGEBROWSER_H
#define IMAGEBROWSER_H
#include <QWidget>

class QFileSystemModel;
class ImageBrowserCore;
namespace Ui {
class ImageBrowser;
}

class ImageBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit    ImageBrowser(QWidget *parent = nullptr);
    void        setImageViewFilter(const QStringList& filters);
    void        setImageShowDirectory(QString dirPath);
    void        setFileViewVisiblility(bool st);
    void        showCurrent();
    QStringList getFilters(){return filters;}
    ~ImageBrowser();

private slots:
    void on_imageLists_clicked(const QModelIndex &index);

private:
    QStringList                         filters{"*.png", "*.jpg", "*.jpeg"};

    void                                initConnections();
    std::unique_ptr<ImageBrowserCore>   core;
    std::unique_ptr<QFileSystemModel>   fileModels;
    std::unique_ptr<QImage>             currentShow;
    Ui::ImageBrowser *ui;
};

#endif // IMAGEBROWSER_H
