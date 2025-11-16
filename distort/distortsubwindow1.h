#ifndef DISTORTSUBWINDOW1_H
#define DISTORTSUBWINDOW1_H

#include <QDialog>

namespace Ui {
class DisTortSubWindow1;
}

class DisTortSubWindow1 : public QDialog
{
    Q_OBJECT

public:
    explicit DisTortSubWindow1(QWidget *parent = 0);
    ~DisTortSubWindow1();

private:
    Ui::DisTortSubWindow1 *ui;
};

#endif // DISTORTSUBWINDOW1_H
