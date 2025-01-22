#include "TestTools.h"
#include "ui_TestTools.h"

TestTools::TestTools(QWidget *parent) : QWidget(parent), ui(new Ui::TestTools) {
    ui->setupUi(this);
}

TestTools::~TestTools() {
    delete ui;
}
