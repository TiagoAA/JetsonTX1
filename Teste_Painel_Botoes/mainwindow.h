#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>

#include <stdio.h>
#include <class_jetson_buttons.h>




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
    void on_pushButton_clicked();
    void MyFunctionTimer_1();



private:
    Ui::MainWindow *ui;

    void InicializarTimer(int msec); /**! inicializar timer */

    QTimer *timer; /**! timer para checar buttons */

    Class_Jetson_Buttons OperadorClassButton; /**! Operador da classse Button */




};

#endif // MAINWINDOW_H
