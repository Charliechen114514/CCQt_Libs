#ifndef TESTMAIN_H
#define TESTMAIN_H

#include <QWidget>

namespace Ui {
class TestMain;
}

class TestMain : public QWidget {
    Q_OBJECT

public:
    explicit TestMain(QWidget *parent = nullptr);
    ~TestMain();
signals:
    void tellSwitchState();
    void tellSwitchButtonState();

private:
    Ui::TestMain *ui;
};

#endif  // TESTMAIN_H
