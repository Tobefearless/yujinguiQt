#ifndef DISTORTMAINWINDOW_H
#define DISTORTMAINWINDOW_H

#include <QDialog>

namespace Ui {
class DisTortMainWindow;
}

class DisTortMainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DisTortMainWindow(QWidget *parent = 0);
    ~DisTortMainWindow();

private:
    Ui::DisTortMainWindow *ui;
};

#endif // DISTORTMAINWINDOW_H
