#include "class_terminal.h"



///////////////////////////////////////////////////////////
/// Construtor
///////////////////////////////////////////////////////////
//#pragma region Construtor
    Class_terminal::Class_terminal()
    {
        Program = "gnome-terminal";
        OperadorTerminal = new QProcess();
    }
    Class_terminal::~Class_terminal()
    {
        OperadorTerminal->close();
    }
//#pragma endregion


///////////////////////////////////////////////////////////
/// OpenTerminal
///////////////////////////////////////////////////////////
//#pragma region Metodo

    /// Open Terminal only
    void Class_terminal::OpenTerminal()
    {
        OperadorTerminal = new QProcess();
        OperadorTerminal->start(Program, QIODevice::WriteOnly);
//        qDebug () << OperadorTerminal->readAllStandardOutput();
    }

    /// Open Terminal and send command code
    void Class_terminal::OpenTerminal(QStringList code)
    {
        QStringList params;
        params << "-x" << code; //  params << "-x" << "qtdiag";

        OperadorTerminal = new QProcess();

        OperadorTerminal->start(Program, params, QIODevice::WriteOnly);
        OperadorTerminal->waitForStarted();
        //        QString p_stdout = OperadorTerminal->readAllStandardOutput();
        //        QString p_stderr = OperadorTerminal->readAllStandardError();
    }

    /// Open terminla without "-x" start argument
    void Class_terminal::OpenTerminal2(QStringList code)
    {
        OperadorTerminal = new QProcess();

        OperadorTerminal->start(Program, code, QIODevice::WriteOnly);
        OperadorTerminal->waitForStarted();
    }




//#pragma endregion



/////////////////////////////////////////////////////////////
/////GetCurrentDir
/////////////////////////////////////////////////////////////
//#pragma region Metodo
    QString Class_terminal::GetCurrentDir()
    {
        QDir dir;
        QString Path = dir.absolutePath();
        qDebug () << "DEBUG (GetCurrentDir) ==> " << Path;
        return Path;
    }
//#pragma endregion


/////////////////////////////////////////////////////////////
/////GetCurrentDir
/////////////////////////////////////////////////////////////
//#pragma region Metodo
    bool Class_terminal::MakeExecutableFileSH(QString DirPath, QString FileName, QStringList CodeLines)
    {
        bool status = true;
        QString FilePath = DirPath + "/" + FileName;
        qDebug () << "DEBUG (MakeExecutableFileSH) ==> " << FilePath;

        QFile NewFile(FilePath);


        //Checar se arquivo não foi criado
        if(!NewFile.open(QFile::WriteOnly|QFile::Text))
        {
            return false;
        }

        //Preencher arquivo
        QTextStream OperadorFile(&NewFile);

        int NumLines = CodeLines.count();

        for(int ii=0;ii<NumLines; ii++)
        {
            QString txt = CodeLines[ii];
            OperadorFile << txt << "\n";
        }
        NewFile.flush();
        NewFile.close();

        // tornar arquivo executavel
        MakeExecutable(FilePath);

        // Executar script


        return status;
    }
//#pragma endregion


/////////////////////////////////////////////////////////////
///// MakeExecutable
/////////////////////////////////////////////////////////////
//#pragma region Metodo
     void Class_terminal::MakeExecutable(QString PathFileName)
     {
        QStringList params;
//        params << "sudo";
//        params << "su";
        params << "chmod";
        params << "+x";
        params << PathFileName;

        qDebug () << "DEBUG (MakeExecutable) ==> " << PathFileName;

        OpenTerminal(params);
     }
//#pragma endregion


/////////////////////////////////////////////////////////////
///// ExecuteFile
/////////////////////////////////////////////////////////////
//#pragma region Metodo
    void Class_terminal::ExecuteFile(QString PathFileName)
    {
        QStringList params;
        params << "bash";
        params << "-c";
        params << PathFileName;

        qDebug () << "DEBUG (ExecuteFile) ==> " << PathFileName;

        OpenTerminal(params);
    }
//#pragma endregion


/////////////////////////////////////////////////////////////
/////
/////////////////////////////////////////////////////////////
//#pragma region Metodo

//#pragma endregion



/////////////////////////////////////////////////////////////
/////
/////////////////////////////////////////////////////////////
//#pragma region Metodo

//#pragma endregion










/////////////////////////////////////////////////////////////
///// ConverteQstringtoCharArray
/////////////////////////////////////////////////////////////
//#pragma region Metodo
    char* Class_terminal::ConverteQstringtoCharArray(QString txt)
    {
        // converter de QString para char*
        QByteArray temp = txt.toLocal8Bit();
        char *comando = (char *)strdup(temp.constData());
        return comando;
    }
//#pragma endregion



///////////////////////////////////////////////////////////
/// PrintCodeTerminal
///////////////////////////////////////////////////////////
//#pragma region PrintCodeTerminal
//    void Class_terminal::PrintCodeTerminal(QStringList code)
//    {
//        try
//        {
//
//        }
//        catch(QException &e)
//        {
////            qWarning("Erro na Função PrintCodeTerminal: \n");
////            qWarning( e.what());
//            QMessageBox::warning(0, "Erro Função PrintCodeTerminal", e.what());
//        }
//    }
//#pragma endregion


/////////////////////////////////////////////////////////////
/////
/////////////////////////////////////////////////////////////
//#pragma region Metodo

//#pragma endregion
