#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "minify.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<QFileDialog>
using namespace std;
void minify2(string inputFile, string outputFile) {
    ifstream indata(inputFile);
    ofstream outdata(outputFile);
    string sentence;
    while (getline(indata, sentence)) {		//Reading file
        string res = "";
        for (int i = 0; i < sentence.size(); i++) {
            if (sentence.at(i) != '\t' && sentence.at(i) != '\n' && sentence.at(i) != ' ')
                res += sentence.at(i);
        }
        outdata << res;
    }
    indata.close();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_6_clicked()         //Minify button
{
    QString s1 = QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen","All Files (*)");
    //string s2 = ".../.../newsample.txt";

    minify2 (s1.toStdString(), "newsample.txt");
}


void MainWindow::on_pushButton_clicked()           //Compress button
{

}


void MainWindow::on_pushButton_2_clicked()          //Decompress button
{

}


void MainWindow::on_pushButton_3_clicked()          //Formatting button
{

}


void MainWindow::on_pushButton_4_clicked()          //Convert to JSON
{

}


void MainWindow::on_pushButton_5_clicked()          //Graph Visualize
{

}


void MainWindow::on_toolButton_clicked()            //minify browse
{

}

