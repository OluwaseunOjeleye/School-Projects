#include "selectmain.h"

#include "ui_selectmain.h"

#include <QMessageBox>

SelectMain::SelectMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMain)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    Human=new HumanGuess();
}

SelectMain::~SelectMain()
{
    delete ui;
}

void SelectMain::on_pushButton_clicked()
{
    MainWindow *Main=new MainWindow();
    Main->show();
    this->close();
}

void SelectMain::on_pushButton_2_clicked()
{
    Human->show();
    this->close();
}

void SelectMain::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton question;
    question=QMessageBox::question(this, "Quit", "Are you sure?",QMessageBox::Yes|QMessageBox::No);
    if (question == QMessageBox::Yes){
        QApplication::quit();
    }
    else{
    }
}
