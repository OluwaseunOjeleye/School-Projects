#ifndef HUMANGUESS_H
#define HUMANGUESS_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class HumanGuess;
}

class HumanGuess : public QDialog
{
    Q_OBJECT

public:
    explicit HumanGuess(QWidget *parent = 0);
    ~HumanGuess();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::HumanGuess *ui;

    std::vector<std::wstring> Words;
    std::wstring computerword;

    int maxWords;
    int iteration;

    //std::string fileName;

    bool correct;
    int Calctype;

    QStringList RandomList;
    QStringListModel *Randommodel;

    QStringList GuessedList;
    QStringListModel *Guessedmodel;

    void PickWord();
    int Evaluator(std::wstring A, int type);
};

#endif // HUMANGUESS_H
