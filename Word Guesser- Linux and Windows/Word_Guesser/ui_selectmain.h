/********************************************************************************
** Form generated from reading UI file 'selectmain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTMAIN_H
#define UI_SELECTMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectMain
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *SelectMain)
    {
        if (SelectMain->objectName().isEmpty())
            SelectMain->setObjectName(QString::fromUtf8("SelectMain"));
        SelectMain->resize(361, 131);
        pushButton = new QPushButton(SelectMain);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 151, 51));
        pushButton_2 = new QPushButton(SelectMain);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 10, 161, 51));
        pushButton_3 = new QPushButton(SelectMain);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(90, 70, 161, 51));

        retranslateUi(SelectMain);

        QMetaObject::connectSlotsByName(SelectMain);
    } // setupUi

    void retranslateUi(QDialog *SelectMain)
    {
        SelectMain->setWindowTitle(QApplication::translate("SelectMain", "Guesser", nullptr));
        pushButton->setText(QApplication::translate("SelectMain", "Computer-Human", nullptr));
        pushButton_2->setText(QApplication::translate("SelectMain", "Human-Computer", nullptr));
        pushButton_3->setText(QApplication::translate("SelectMain", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectMain: public Ui_SelectMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTMAIN_H
