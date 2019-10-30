#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "class_terminal.h"

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
    void on_horizontalSlider_valueChanged(int value);

    void on_bt_acionar_clicked();


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void InicializarParametros();

    QString str;
    QStringList txt0;   // habilitar entrada de código
    QStringList txt1;   // mostrar velocidade do cooler
    QStringList txt2;   // controlar a velocidade
    bool flagstart = true;

    Class_terminal OperadorTerminal;


};

#endif // MAINWINDOW_H
