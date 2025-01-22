#include "TestMain.h"
#include "ui_TestMain.h"

TestMain::TestMain(QWidget *parent) : QWidget(parent), ui(new Ui::TestMain) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this,
            &TestMain::tellSwitchState);
    connect(ui->pushButton_2, &QPushButton::clicked, this,
            &TestMain::tellSwitchButtonState);
}

TestMain::~TestMain() {
    delete ui;
}
