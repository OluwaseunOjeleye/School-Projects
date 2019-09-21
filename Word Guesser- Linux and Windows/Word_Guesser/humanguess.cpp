#include "humanguess.h"
#include "ui_humanguess.h"

#include <mainwindow.h>

#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QFileDialog>
#include <QDateTime>

HumanGuess::HumanGuess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HumanGuess)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    Randommodel=new QStringListModel(this);
    Guessedmodel=new QStringListModel(this);

    correct=false;

    this->iteration=0;
    //fileName="/home/oluwa53un/Desktop/Program Last Last/Word_Guesser/Word_Guesser/ourSozluk";

}

HumanGuess::~HumanGuess()
{
    delete ui;
}

void HumanGuess::on_pushButton_4_clicked()  //Start Button
{
    if(Words.empty()){
        QMessageBox::warning(this, tr("Error:"), tr("Load Words..."));
        return;
    }

    if(iteration>0){
        QMessageBox::warning(this, tr("Error:"), tr("You're in the middle of a Game"));
        return;
    }

    if(!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked()){
        QMessageBox::warning(this, tr("Error:"), tr("Select Normal or Cartesian"));
        return;
    }

    if(ui->radioButton->isChecked()){
        this->Calctype=0;
    }
    else{
        this->Calctype=1;
    }

    PickWord();
    QMessageBox MsgBox;
    MsgBox.setText("Word has been picked");
    MsgBox.exec();

    ui->label->setText(QString::number(iteration));
    iteration++;
}


void HumanGuess::on_pushButton_clicked()    //Guess Button
{
    ui->label->setText(QString::number(iteration));
    if(correct==true){
        QMessageBox::warning(this, tr("Info:"), tr("You are correct"));
        return;
    }

    if(iteration==0){
        QMessageBox::warning(this, tr("Error:"), tr("Click on Start"));
        return;
    }

    std::wstring guess=ui->textEdit->toPlainText().toStdWString();

    if (std::find(Words.begin(), Words.end(),guess)== Words.end()){
        QMessageBox::warning(this, tr("Error:"), tr("The word doesnot exist in Dictionary"));
        return;
    }


    int weight=Evaluator(guess, Calctype);

    GuessedList.append(QString::fromStdWString(guess)+"\t"+QString::number(weight));
    Guessedmodel->setStringList(GuessedList);
    ui->listView_2->setModel(Guessedmodel);


    if(guess!=computerword){
        QMessageBox::warning(this, tr("Info:"), tr("Wrong Guess"));
        auto itr = std::find(Words.begin(), Words.end(), guess);
        if (itr != Words.end()) Words.erase(itr);
        maxWords=Words.size();

        RandomList.clear();
        for(int i=0; i<maxWords; i++){
            RandomList.append(QString::fromStdWString(Words[i]));
            Randommodel->setStringList(RandomList);
            ui->listView->setModel(Randommodel);
        }
    }
    else{
        QMessageBox MsgBox;
        MsgBox.setText("You are correct");
        MsgBox.exec();
        correct=true;
        return;
    }

    this->iteration++;
}

void HumanGuess::on_pushButton_2_clicked()  //Mainwindow Button
{
    SelectMain *selMain=new SelectMain();
    selMain->show();
    this->close();
}

void HumanGuess::on_pushButton_3_clicked()  //Load Button
{
    if(!Words.empty()){
        QMessageBox::warning(this, tr("Error:"), tr("Words can't be loaded"));
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Text File[Dictionary]"));

    QString nstring = QInputDialog::getText(0,"Input max no of words to Load","Here");
    this->maxWords = nstring.toInt();


    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this, tr("Error opening!"), tr("Could not open the file"));
            return;
    }

    int size=0;
    std::vector<std::wstring> WordsFile;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        std::wstring word = line.toStdWString();
        WordsFile.resize(size+1);
        WordsFile[size]=word;

        size++;
    }

    qsrand(QDateTime::currentMSecsSinceEpoch()/1000);
    for(int i=0; i<maxWords; i++){
        Words.resize(i+1);
        Words[i]=WordsFile[qrand()%size];
        RandomList.append(QString::fromStdWString(Words[i]));
        Randommodel->setStringList(RandomList);
        ui->listView->setModel(Randommodel);
    }

    file.close();
    QMessageBox::warning(this, tr("Loading..."), tr("Words Loaded"));
}


void HumanGuess::on_pushButton_5_clicked()     //Clear Button
{
    Words.clear();
    computerword=L"";

    maxWords=0;
    iteration=0;

    correct=false;

    ui->label->setText(QString::number(iteration));
    ui->textEdit->clear();

    RandomList.clear();
    Randommodel->setStringList(RandomList);
    ui->listView->setModel(Randommodel);

    GuessedList.clear();
    Guessedmodel->setStringList(GuessedList);
    ui->listView_2->setModel(Guessedmodel);

    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
}


void HumanGuess::on_pushButton_6_clicked()  //Exit Button
{
    QMessageBox::StandardButton question;
    question=QMessageBox::question(this, "Quit", "Are you sure?",QMessageBox::Yes|QMessageBox::No);
    if (question == QMessageBox::Yes){
        QApplication::quit();
    }
    else{
    }
}


void HumanGuess::PickWord(){
    qsrand(QDateTime::currentMSecsSinceEpoch()/1000);
    int i=qrand()%maxWords;
    this->computerword=Words[i];
}

int HumanGuess::Evaluator(std::wstring A, int type){
    int weight=0;
    for(int i=0; i<A.length(); i++){
        for(int j=0; j<computerword.length(); j++){
            if(type==1){                //Cartesian olan
                if(A[i]==computerword[j]){
                    weight+=1;
                }
            }
            else{                       //Cartesian olmayan
                if(A[i]==computerword[j]){
                    weight+=1;
                    break;
                }
            }

        }
    }
    return weight;
}


