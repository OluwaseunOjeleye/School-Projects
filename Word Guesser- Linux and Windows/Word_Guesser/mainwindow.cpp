#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QElapsedTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initializing important private variables
    Human=new HumanGuess();
    computer_Thinker=new Vector();

    setFixedSize(width(), height());

    UserWeight=0;
    iteration=0;
    Randomword=L"";

    Calctype=1;
    start=0;

    worstcase=0, average=0, bestcase=100, no=0;

    for(int i=0; i<noTrials; i++){
            root[i]=new Vector();
    }

    // Create model
    Randommodel=new QStringListModel(this);
    absent_Alphabetmodel=new QStringListModel(this);
    present_Alphabetmodel=new QStringListModel(this);

    fileName=L"";

    ui->label_7->setText(QString::number(0)+"msec");

    //fileName="/home/oluwa53un/Desktop/Program Last Last/Word_Guesser/Word_Guesser/sozluk";
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()  //Start Button
{
        //if no word is loaded
        if(isemptyTrie()){
            QMessageBox::warning(this, tr("Error:"), tr("No word in list. Load a file!!!"));
            return;
        }

        //if start was clicked when the user is using the program
        if(iteration!=0){
            QMessageBox::warning(this, tr("Error:"), tr("Wrong Button Clicked!!!"));

            //Although the wrong button was clicked but the user can continue
            SelectSimilarWords(root[iteration], root[iteration+1], Calctype);
            return;
        }

        //if cartesian or normal is not selected
        if(!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked()){
            QMessageBox::warning(this, tr("Error:"), tr("Select Normal or Cartesian"));
            return;
        }

        if(start!=0 && no==0){
            QMessageBox::warning(this, tr("Error:"), tr("Click on Guess Button"));
            return;
        }

        //Cartesian or Normal
        if(ui->radioButton->isChecked()){
            this->Calctype=0;
        }
        else{
            this->Calctype=1;
        }

        //Starting Prediction
        this->iteration=0;

        ui->label_6->setText(QString::number(iteration));


        ui->textEdit_4->setText(QString::number(root[iteration]->noOfwords));
        ui->textEdit_4->show();



        Randomword=L"";
        SelectRandomWord();
        Copy(root[0], root[1]); //copying from root0 to root1
        //std::wcout<<"Iteration: "<<iteration<<" User Weight: "<<UserWeight<<" Random word: "<<Randomword<<std::endl;
        start++;
}

void MainWindow::Show(){    //For displaying values on GUI
    RandomList.append(QString::fromStdWString(Randomword));
    Randommodel->setStringList(RandomList);
    ui->listView->setModel(Randommodel);

    AlphabetProbability();
    ui->listView_2->setModel(absent_Alphabetmodel);
    ui->listView_3->setModel(present_Alphabetmodel);


    ui->textEdit->setText(QString::fromStdWString(Randomword));
    ui->textEdit->show();

    ui->textEdit_4->setText(QString::number(root[iteration]->noOfwords));
    ui->textEdit_4->show();

    if(Found()){
        QMessageBox MsgBox;
        MsgBox.setText("The word you guessed is: "+ QString::fromStdWString(Randomword));
        MsgBox.exec();
        return;
    }

    //For Palindrome Words
    if(root[iteration]->checkIfSimilar==0){
        QMessageBox::warning(this, tr("Info:"), tr("The Word is Similar"));

        RandomList.append("...........");
        Randommodel->setStringList(RandomList);
        ui->listView->setModel(Randommodel);

        //printing all words on screen since they are similar
        for(int i=0; i<root[iteration]->noOfwords; i++){
            RandomList.append(QString::fromStdWString(root[iteration]->Words[i]));
            Randommodel->setStringList(RandomList);
            ui->listView->setModel(Randommodel);
        }

        return;
    }

    QString nstring = QInputDialog::getText(0,"Input Number of Similar Letters","Here..");
    this->UserWeight = nstring.toInt();
    ui->textEdit_3->setText(QString::number(UserWeight));
    ui->textEdit_3->show();

    SelectSimilarWords(root[iteration], root[iteration+1], Calctype);
}


void MainWindow::writeToFile(){ //writing to file if word doesnot exist in file
    QMessageBox::StandardButton question;
    question=QMessageBox::question(this, "Add New Word", "Do you want to add the word? ",QMessageBox::Yes|QMessageBox::No);
    if (question == QMessageBox::Yes){

        //std::cout<<this->fileName<<std::endl;
        QFile file(QString::fromStdWString(this->fileName));

        if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QMessageBox::warning(this, tr("Error opening!"), tr("Could not open the file"));
            return;
        }

        QString nstring = QInputDialog::getText(0,"Input The word You Guessed","Here..");
        QTextStream out(&file);
        out<<nstring<< endl;
        file.close();
    }


}

void MainWindow::on_pushButton_clicked()    //Guess Button
{
    if(isemptyTrie() && iteration==0){
        QMessageBox::warning(this, tr("Error:"), tr("No word in list. Load a file!!!"));
        return;
    }

    //if start button hasnot been clicked
    if(start==0){
        QMessageBox::warning(this, tr("Error:"), tr("Click on Start Button!!!"));
        return;
    }

    this->iteration++;

    if(isemptyTrie()){
        QMessageBox::warning(this, tr("Error:"), tr("No word in list!!!"));
        writeToFile();
        return;
    }

    //if not maxIteration
    if(!isLastIter()){
        if(iteration==1){
            ui->label_6->setText(QString::number(iteration));
            Show();
        }
        else{
            /*if(iteration>5){root[iteration]->display();}*/
            ui->label_6->setText(QString::number(iteration));

            Randomword=L"";
            SelectRandomWord();

            Show();
        }
    }
    else{
        QMessageBox::warning(this, tr("Error:"), tr("End of Trial"));
    }
    //std::wcout<<"Iteration: "<<iteration<<" User Weight: "<<UserWeight<<" Random word: "<<Randomword<<std::endl;
}


void MainWindow::on_pushButton_3_clicked()  //Correct Button
{
    if(start==0){
        QMessageBox::warning(this, tr("Error:"), tr("Click on Start Button!!!"));
        return;
    }

    if(isemptyTrie()){
        QMessageBox::warning(this, tr("Error:"), tr("No word in list!!!"));
        return;
    }

    QMessageBox::warning(this, tr("Info:"), tr("Word Found!!!"));

    QMessageBox::StandardButton question;
    question=QMessageBox::question(this, "Quit", "Do you want to continue?",QMessageBox::Yes|QMessageBox::No);
    if (question == QMessageBox::No){
        QApplication::quit();
    }
    else{
        on_actionNew_triggered();
    }
}


void MainWindow::on_pushButton_4_clicked()  //Exit Button
{
    QMessageBox::StandardButton question;
    question=QMessageBox::question(this, "Quit", "Are you sure?",QMessageBox::Yes|QMessageBox::No);
    if (question == QMessageBox::Yes){
        QApplication::quit();
    }
    else{
    }
}

void MainWindow::on_actionNew_Same_Dictionary_triggered()//Clearing Operation for new operation using same dictionary
{
    if(root[0]->noOfwords==0){
        QMessageBox::warning(this, tr("Info:"), tr("Load New File..."));
        return;
    }

    UserWeight=0;
    iteration=0;
    Randomword=L"";
    start=0;

    fileName=L"";

    //clearing all roots except from root0 for same dictionary operation
    for(int i=1; i<noTrials; i++){
        delete root[i];
    }
    for(int i=1; i<noTrials; i++){
        root[i]=new Vector();
    }

    ui->textEdit->setText("");
    ui->label_6->setText("");
    ui->textEdit_3->setText("");
    ui->textEdit_4->setText(QString::number(root[0]->noOfwords));
    ui->label_7->setText(QString::number(0)+"msec");

    RandomList.clear();
    Randommodel->setStringList(RandomList);
    ui->listView->setModel(Randommodel);

    absent_AlphabetList.clear();
    absent_Alphabetmodel->setStringList(absent_AlphabetList);
    ui->listView_2->setModel(absent_Alphabetmodel);

    present_AlphabetList.clear();
    present_Alphabetmodel->setStringList(present_AlphabetList);
    ui->listView_3->setModel(present_Alphabetmodel);

    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);

    QMessageBox::warning(this, tr("Info:"), tr("Continue Operation..."));
}

void MainWindow::on_actionNew_triggered()   //Clearing Function for New Operation
{
    //clearing all roots for a new dictionary operation

    on_actionNew_Same_Dictionary_triggered();
    delete root[0];
    root[0]=new Vector();

    delete computer_Thinker;
    computer_Thinker=new Vector();

    worstcase=0;
    bestcase=100;
    average=0;
    no=0;

    ui->textEdit_4->setText("");
    QMessageBox::warning(this, tr("Info:"), tr("Load New File..."));
}

void MainWindow::on_actionLoad_triggered()//Loading new Dictionary
{
    if(root[0]->noOfwords!=0){
        QMessageBox::warning(this, tr("Error: "), tr("Words can't be loaded"));
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Text File[Dictionary]"));

    this->fileName=fileName.toStdWString();

    //QFile file(QString::fromStdString(fileName));
    if (fileName.isEmpty()){
        return;
    }
    else{   }
    QFile file(fileName);
    if (!file.exists()) {
        QMessageBox::warning(this, tr("Error opening!"), tr("File doesnot exist"));
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this, tr("Error opening!"), tr("Could not open the file"));
            return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        std::wstring word = line.toStdWString();
        std::wstring charList=L" ";
        if(charList.find(word)==std::wstring::npos){ //if charList characters not in word
            //std::cout<<word<<std::endl;
            root[0]->insert(word);
            computer_Thinker->insert(word); //storing words for com-com operation
        }
    }
    file.close();
    QMessageBox::warning(this, tr("Loading..."), tr("Words Loaded"));
}



void MainWindow::on_actionAbout_triggered()//About Us
{
    QMessageBox::about(this,"About Word Guesser-V1.0","<font size=2><b>By: Aaron, Amal, Elcin, Farukcan, Seun, Ugur, Yasir</b></font> ");
}

void MainWindow::on_actionExit_triggered()  //Exit Button
{
    on_pushButton_4_clicked();
}


void MainWindow::on_actionHuman_Guess_triggered()   //Human-Computer
{
    //Human->setModal(false);
    Human->show();
    this->close();
}


void MainWindow::on_pushButton_5_clicked()  //Select Main WIndows
{   QMessageBox::StandardButton question;
    question=QMessageBox::question(this, "Main Menu", "Are you sure?",QMessageBox::Yes|QMessageBox::No);
    if (question == QMessageBox::Yes){
        SelectMain *selMain=new SelectMain();
        selMain->show();
        this->close();
    }
}


//Copying Trie node words to Trie newNode
void MainWindow::Copy(Vector *node, Vector *newNode){
    for(int i=0; i<node->noOfwords; i++){
        newNode->insert(node->Words[i]);
    }
}


//check if it's last trial
bool MainWindow::isLastIter(){
    if(iteration<=noTrials){
        return false;
    }
    else{
        return true;
    }
}

//is there only a word in list?
bool MainWindow::Found(){
    if(root[iteration]->noOfwords==1){
        return true;
    }
    else{
        return false;
    }
}

//is present list empty
bool MainWindow::isemptyTrie(){
    if(root[iteration]->noOfwords==0){
        return true;
    }
    return false;
}

//Cartesian n Normal weight evaluator
int MainWindow::Evaluator(std::wstring A, int type){
    int weight=0;
    for(int i=0; i<A.length(); i++){
        for(int j=0; j<Randomword.length(); j++){
            if(type==1){                //Cartesian olan
                if(A[i]==Randomword[j]){
                    weight+=1;
                }
            }
            else{                       //Cartesian olmayan
                if(A[i]==Randomword[j]){
                    weight+=1;
                    break;
                }
            }
        }
    }
    //std::cout<<A<<" is "<<weight<<std::endl;
    return weight;
}

//Fuction that transfer possible words from one root to another
void MainWindow::SelectSimilarWords(Vector *node, Vector *newNode, int type){
    for(int i=0; i<node->noOfwords; i++){

        int point=Evaluator(node->Words[i], type);

        if((point==UserWeight) && (node->Words[i]!=Randomword)){
            newNode->insert(node->Words[i]);
        }
    }

}


//calculate the best randomword to select by summing the frequency of every letter in the word-L""
//calculate the best randomword to select by summing the frequency of every consonant letter in the word-L"aeıioöuü"
//calculate the best randomword to select by summing the frequency of every vowel letter in the word-use !=

int MainWindow::weight(const std::wstring &word){
    int weight=0;
    std::wstring charList=L"";//L"aeıioöuü";
    for(int i=0; i<word.length(); i++){
        if(charList.find(word[i])==std::wstring::npos){ //if charList characters not in word
            weight+=root[iteration]->characterFrequency[word[i]];
            charList+=word[i];
        }
    }
    return weight;
}

//Selecting random word
void MainWindow::SelectRandomWord(){
    Randomword=root[iteration]->Words[0];
    for(int i=1; i<root[iteration]->noOfwords; i++){
        //if(weight(root[iteration]->Words[i]) > weight(Randomword)){
        if(root[iteration]->Words[i].length() > Randomword.length()){
            this->Randomword=root[iteration]->Words[i];
        }
    }
}

//Display possible and impossible letters after every iteration
void MainWindow::AlphabetProbability(){
    absent_AlphabetList.clear();
    present_AlphabetList.clear();

    std::wstring charList=L"ĞğŞşÇçIıİiÖöÜü";
    for(int i=0; i<Ascii_char_Size; i++){
        wchar_t charAlp=wchar_t(i);
        if((charList.find(charAlp)!=std::wstring::npos)||(i>=65&&i<=90)||(i>=97&&i<=122)){//if character is any turkish character
            if(root[iteration]->characterFrequency[i]==0){  //if frequency of the character is 0 then it doesn't exist
                std::wstring alp(1, charAlp);
                absent_AlphabetList.append(QString::fromStdWString(alp));
                absent_Alphabetmodel->setStringList(absent_AlphabetList);
            }
            else{//if frequency of the character isnot 0 then it exist
                std::wstring alp(1, charAlp);
                present_AlphabetList.append(QString::fromStdWString(alp));
                present_Alphabetmodel->setStringList(present_AlphabetList);
            }
        }
    }
    return;
}

void MainWindow::Computer_Guesser(std::wstring word)    //Computer_Guesser Button
{
    if(isemptyTrie() && iteration==0){
        QMessageBox::warning(this, tr("Error:"), tr("No word in list. Load a file!!!"));
        return;
    }

    this->iteration++;

    if(isemptyTrie()){
        QMessageBox::warning(this, tr("Error:"), tr("No word in list. Load a file!!!"));
        writeToFile();
        return;
    }

    if(!isLastIter()){
        if(iteration==1){
            ui->label_6->setText(QString::number(iteration));

            this->UserWeight = Evaluator(word, Calctype);

            SelectSimilarWords(root[iteration], root[iteration+1], Calctype);
        }
        else{
            ui->label_6->setText(QString::number(iteration));

            Randomword=L"";
            SelectRandomWord();

            this->UserWeight = Evaluator(word, Calctype);
            SelectSimilarWords(root[iteration], root[iteration+1], Calctype);
        }
    }
    else{
        QMessageBox::warning(this, tr("Error:"), tr("End of Trial"));
    }
    //std::wcout<<"Iteration: "<<iteration<<" User Weight: "<<UserWeight<<" Random word: "<<Randomword<<std::endl;
}


void MainWindow::on_actionAnalysis_triggered()
{
    if(isemptyTrie()){
        QMessageBox::warning(this, tr("Error:"), tr("No word in list to analyze. Load a file!!!"));
        return;
    }

    if(!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked()){
        QMessageBox::warning(this, tr("Error:"), tr("Select Normal or Cartesian"));
        return;
    }

    if(iteration!=0){
        QMessageBox::warning(this, tr("Error:"), tr("Start New Operation To analyze the dictionary!!!"));
        return;
    }


    QString nstring = QInputDialog::getText(0,"Info","Input Number of words to analyze");
    this->no = nstring.toInt();

    if(no==0){return;}

    QElapsedTimer timer;
    timer.start();

    int i;
    qsrand(QDateTime::currentMSecsSinceEpoch()/1000);
    for(int c=0; c<this->no; c++){
        i=qrand()%computer_Thinker->noOfwords;
        while(computer_Thinker->Words[i]!=Randomword){
            if(this->iteration==0){
                on_pushButton_2_clicked();
            }
            Computer_Guesser(computer_Thinker->Words[i]);
        }
        std::wcout<<c<<"--"<<computer_Thinker->Words[i]<<"--"<<iteration<<std::endl;
        if(iteration>this->worstcase){
            this->worstcase=iteration;
        }
        if(iteration<this->bestcase){
            this->bestcase=iteration;
        }
        this->average+=iteration;
        computer_Thinker->no_trials=iteration;
        UserWeight=0;
        iteration=0;
        Randomword=L"";
        start=0;

        for(int i=1; i<noTrials; i++){
            delete root[i];
        }
        for(int i=1; i<noTrials; i++){
            root[i]=new Vector();
        }
    }
    ui->label_7->setText(QString::number(timer.elapsed())+"msec");

    this->average=average/no;
    std::cout<<bestcase<<"---"<<average<<"---"<<worstcase<<std::endl;
    QMessageBox::warning(this, tr("Info:"), tr("Analysis Completed!!!"));
    QMessageBox::information(nullptr,"Analyzer Message",
         QString("Number Of Words-%1 \nBest case-%2 \nAverage-%3 \nWorst case-%4")
             .arg(this->no)
             .arg(bestcase)
             .arg(average)
             .arg(worstcase), "Ok");
}

void MainWindow::on_actionAnalyzer_Report_triggered()
{
    if(isemptyTrie()){
        QMessageBox::information(nullptr,"Analyzer Message",
             QString("Last Report:\nNumber Of Words-Nil \nBest case-Nil \nAverage-Nil \nWorst case-Nil"), "Ok");
        return;
    }
    QMessageBox::information(nullptr,"Analyzer Message",
         QString("Last Report:\nNumber Of Words-%1 \nBest case-%2 \nAverage-%3 \nWorst case-%4")
             .arg(this->no)
             .arg(bestcase)
             .arg(average)
             .arg(worstcase), "Ok");
}


