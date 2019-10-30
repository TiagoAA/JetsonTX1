#ifndef CLASS_TERMINAL_H
#define CLASS_TERMINAL_H

#include <QString>
#include <QProcess>
#include <QException>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDir>

#include <iostream>
#include <string>
#include <exception>




class Class_terminal
{
private:   
    QProcess *OperadorTerminal;

public:
    Class_terminal();
    ~Class_terminal();

    QString Program;

    void OpenTerminal();
    void OpenTerminal(QStringList code);
    void OpenTerminal2(QStringList code);

    QString GetCurrentDir();
    bool MakeExecutableFileSH(QString DirPath, QString FileName , QStringList CodeLines);
    void MakeExecutable(QString PathFileName);
    void ExecuteFile(QString PathFileName);


    char* ConverteQstringtoCharArray(QString txt);

};

#endif // CLASS_TERMINAL_H
