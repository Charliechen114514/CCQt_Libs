#include "MainWindow.h"
#include "TestMain.h"
#include "TestTools.h"
#include "qboxlayout.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    TestMain*   mainWidget  = new TestMain(this);
    TestTools*  toolsWidget = new TestTools(this);
    QWidgetList lmain;
    lmain << mainWidget;
    QWidgetList ltools;
    ltools << toolsWidget;
    ui->centralwidget->addLayout(new QVBoxLayout(this), lmain,
                                 SideBarWidget::Role::MainSide);
    ui->centralwidget->addLayout(new QVBoxLayout(this), ltools,
                                 SideBarWidget::Role::SideBar);
    connect(mainWidget, &TestMain::tellSwitchState, ui->centralwidget,
            &SideBarWidget::switch_state);
    connect(mainWidget, &TestMain::tellSwitchButtonState, ui->centralwidget,
            &SideBarWidget::switch_button_visible);
    ui->centralwidget->setButtonVisible(false);
}

MainWindow::~MainWindow() {
    delete ui;
}
