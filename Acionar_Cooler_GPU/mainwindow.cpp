#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InicializarParametros();

}

MainWindow::~MainWindow()
{
    delete ui;
}


// https://wiki.qt.io/How_to_Use_QSettings
void MainWindow::InicializarParametros()
{
    str = "";
    txt0 << "qtdiag"; //<< "sudo" << "su";
    txt1 << "sudo" << "watch" << "-n" << "1" << "cat" << "/sys/kernel/debug/tegra_fan/cur_pwm";
    txt2 << "sudo" << "echo" << "50" << ">" << "/sys/kernel/debug/tegra_fan/target_pwm";
    //sudo echo 0 > /sys/kernel/debug/tegra_fan/target_pwm
}


// Mostra a barra de status
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lcdNumber->display(value);
    ui->progressBar->setValue(value);
}


// Botão de controle da velocidade do cooler
void MainWindow::on_bt_acionar_clicked()
{
    // Acionar apenas a primeira vez
    if(flagstart)
    {
        flagstart = false;
        ui->textBrowser->clear();
//        ui->textBrowser->append(txt0);
//        ui->textBrowser->append(txt1);

//        OperadorTerminal.OpenTerminal(txt0);
    }

    // Forma o código que controla a velocidade do cooler
    str.sprintf("sudo echo %d > /sys/kernel/debug/tegra_fan/target_pwm", ui->horizontalSlider->value());

    ui->textBrowser->append(str);

////////////////////////////////////////////////
    //gnome-terminal -e "bash -c '/home/ubuntu/scripts/wifi.sh'"
    QStringList Argumentos;


////////////////////////////////////////////////
/// Criar Modelo de arquivo para ajustar verlocidade
////////////////////////////////////////////////
    QString PathDir  = OperadorTerminal.GetCurrentDir();
    QString FileName = "ControleFAN.sh";
    QString FilePath = PathDir + "/" + FileName;


    //// Criar arquivo com os controles do cooler
    Argumentos.clear();
    Argumentos << "#!/bin/bash";
    Argumentos << "sudo su << EOF";
    Argumentos << "sleep 1";
    Argumentos << str;
    Argumentos << "EOF";
    Argumentos << "exit";


    OperadorTerminal.MakeExecutableFileSH(PathDir, FileName, Argumentos);
    OperadorTerminal.ExecuteFile(FilePath);



}

// Botão monitorar velocidade
void MainWindow::on_pushButton_clicked()
{
    OperadorTerminal.OpenTerminal(txt1);
}
