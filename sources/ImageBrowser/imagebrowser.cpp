#include <QFileSystemModel>
#include "imagebrowser.h"
#include "imagebrowsercore.h"
#include "ui_imagebrowser.h"
#include <QFileInfo>
#include <QMessageBox>
ImageBrowser::ImageBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageBrowser)
{
    ui->setupUi(this);
    core = std::make_unique<ImageBrowserCore>();
    fileModels = std::make_unique<QFileSystemModel>();
    ui->imageLists->setModel(fileModels.get());
    fileModels->setNameFilterDisables(false);
    ui->imageLists->setColumnHidden(1, true);
    ui->imageLists->setColumnHidden(2, true);
    ui->imageLists->setColumnHidden(3, true);
    setImageViewFilter(filters);
}

void ImageBrowser::setImageViewFilter(const QStringList& filters)
{
    fileModels->setNameFilters(filters);
}

void ImageBrowser::setImageShowDirectory(QString dirPath)
{
    fileModels->setRootPath(dirPath);
    ui->imageLists->setRootIndex(fileModels->index(dirPath));
    QDir dir(dirPath);
    auto res= dir.entryInfoList(filters,QDir::Files | QDir::Readable,QDir::Name);
    QDirIterator iter(dirPath, filters,
                      QDir::Files | QDir::Readable,
                      QDirIterator::Subdirectories);
    QStringList resfin;
    while(iter.hasNext())
    {
        iter.next();
        resfin << iter.fileInfo().absoluteFilePath();
    }

    core->enImages(resfin);
}

void ImageBrowser::setFileViewVisiblility(bool st)
{
    ui->imageLists->setVisible(st);
}

ImageBrowser::~ImageBrowser()
{
    delete ui;
}

void ImageBrowser::showCurrent()
{
    currentShow.reset(core->getCurrentImage());
    if(!currentShow)
        return;
    ui->imageViewer->setPixmap(QPixmap::fromImage(*currentShow).scaled(ui->imageViewer->size(),Qt::KeepAspectRatio));
}

void ImageBrowser::on_imageLists_clicked(const QModelIndex &index)
{
    QString pathGet = fileModels->filePath(index);
    if(!QFileInfo(pathGet).isFile())
        return;
    int _index = core->search(pathGet);
    if(_index == -1)
    {
        QMessageBox::critical(this, "出错", "找不到" + pathGet);
        return;
    }
    core->setCurrentViewIndex(_index);
    showCurrent();
}

