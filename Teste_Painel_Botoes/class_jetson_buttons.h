//**
 /* Classe para gerenciar funções do painel de botões 
 * 
 * @author Tiago A Alvarenga
 * @since 01/10/2019
 * @version 1.0
 */


#ifndef CLASS_JETSON_BUTTONS_H
#define CLASS_JETSON_BUTTONS_H

#include <QString>
#include <QProcess>
#include <QException>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDir>

#include <iostream>
#include <ostream>
#include <string>
#include <exception>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include <jetsonGPIO.h>



class Class_Jetson_Buttons
{
private:


public:
    Class_Jetson_Buttons();
    ~Class_Jetson_Buttons();


/**
 * @brief Configurar pinos GPIO => ENUM from jetsonGPIO.h
 */
    int pin13;// = gpio38;   // sync
    int pin16;// = gpio37;   // Vmod1
    int pin18;// = gpio184;  // save_file
    int pin29;// = gpio219;  // Disp2
    int pin31;// = gpio186;  // power_off
    int pin33;// = gpio63;   // Vmod2
    int pin32;// = gpio36;   // Disp1
    int pin37;// = gpio187;


    void InitButtons();

    void ButtonCheck();//(int &pinName, int &Status);








};

#endif // CLASS_JETSON_BUTTONS_H
