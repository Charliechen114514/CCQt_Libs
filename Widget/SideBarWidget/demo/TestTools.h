#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include <QWidget>

namespace Ui {
class TestTools;
}

class TestTools : public QWidget {
    Q_OBJECT

public:
    explicit TestTools(QWidget *parent = nullptr);
    ~TestTools();

private:
    Ui::TestTools *ui;
};

#endif  // TESTTOOLS_H
