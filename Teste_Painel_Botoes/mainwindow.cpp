#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <stdio.h>
#include <stdlib.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /// Inicializar Timer
    InicializarTimer(500);



}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_pushButton_clicked
 * Botão Limpar Textbox
 */
void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();

    QString txt;

    // teste enun
    ui->textBrowser->append(txt.sprintf(" pin13 = %d",OperadorClassButton.pin13));
    ui->textBrowser->append(txt.sprintf(" pin16 = %d",OperadorClassButton.pin16));
    ui->textBrowser->append(txt.sprintf(" pin18 = %d",OperadorClassButton.pin18));
    ui->textBrowser->append(txt.sprintf(" pin29 = %d",OperadorClassButton.pin29));
    ui->textBrowser->append(txt.sprintf(" pin31 = %d",OperadorClassButton.pin31));
    ui->textBrowser->append(txt.sprintf(" pin32 = %d",OperadorClassButton.pin32));
    ui->textBrowser->append(txt.sprintf(" pin33 = %d",OperadorClassButton.pin33));
    ui->textBrowser->append(txt.sprintf(" pin37 = %d",OperadorClassButton.pin37));

}

/**
 * @brief MainWindow::MyFunctionTimer_1
 * Checar repetidamente os botoes
 */
void MainWindow::MyFunctionTimer_1()
{
    /// Monitora Botoes
    OperadorClassButton.ButtonCheck();
}

/**
 * @brief MainWindow::InicializarTimer
 * @param msec: tempo em milesegundos
 */
void MainWindow::InicializarTimer(int msec)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MyFunctionTimer_1()));
    timer->start(msec);
}
