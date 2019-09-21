#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#define noTrials 100

#include <vector.h>
#include <stack>
#include <QStringListModel>
#include <iostream>
#include <humanguess.h>
#include <selectmain.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionNew_triggered();

    void on_actionLoad_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionHuman_Guess_triggered();

    void on_pushButton_5_clicked();

    void on_actionAnalysis_triggered();

    void on_actionAnalyzer_Report_triggered();

    void on_actionNew_Same_Dictionary_triggered();

private:
    Ui::MainWindow *ui;

    Vector *root[noTrials];

    int UserWeight;
    int iteration;
    std::wstring Randomword;

    int Calctype;
    int start;

    QStringList RandomList;
    QStringListModel *Randommodel;

    QStringList absent_AlphabetList;
    QStringListModel *absent_Alphabetmodel;

    QStringList present_AlphabetList;
    QStringListModel *present_Alphabetmodel;

    std::wstring fileName;

    HumanGuess *Human;

    void Show();
    void writeToFile();

    void display(Vector *node);
    void StoreSimilarWords();

    void Copy(Vector *node, Vector *newNode);

    bool isLastIter();
    int Evaluator(std::wstring A, int type);
    void SelectSimilarWords(Vector *node, Vector *newNode, int type);
    int weight(const std::wstring &word);
    void SelectRandomWord();
    bool Found();
    bool isemptyTrie();
    void AlphabetProbability();

    //Analysis Variables
    void Computer_Guesser(std::wstring word);
    Vector *computer_Thinker;
    int no; //number of words to perform analysis on
    int worstcase;
    double average;
    int bestcase;

    QTime *time;

};

#endif // MAINWINDOW_H
