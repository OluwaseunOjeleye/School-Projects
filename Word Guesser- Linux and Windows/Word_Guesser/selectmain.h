#ifndef SELECTMAIN_H
#define SELECTMAIN_H

#include <QDialog>
#include <mainwindow.h>
#include <humanguess.h>

namespace Ui {
class SelectMain;
}

class SelectMain : public QDialog
{
    Q_OBJECT

public:
    explicit SelectMain(QWidget *parent = 0);
    ~SelectMain();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SelectMain *ui;

    HumanGuess *Human;

};

#endif // SELECTMAIN_H
