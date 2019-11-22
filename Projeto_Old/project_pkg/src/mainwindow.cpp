#include "ui_mainwindow.h"
#include "../include/project_pkg/mainwindow.h"

MainWindow::MainWindow(int argc, char*argv[], QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/icon.png"));
    spinner = NULL;
    ros::init(argc, argv, "Project");
    if ( ros::master::check() )
    {
        ui->lblConnect->setText("Connect to Ros!");
        spinner = new ros::AsyncSpinner(2);

    }
    else{
        ui->lblConnect->setText("Failed to Connect to Ros!");
        this->setEnabled(false);
    }
    ui->dispositivoGpBox->setVisible(true);
    ui->imuGP->setVisible(false);
    ui->vModeCB->setVisible(false);
    ui->vModeLbl->setVisible(false);
    ui->imuGP->setVisible(false);

    glViewer = new GLWidget(ui->viewFrame);
    glViewer->resize(630,400);   
    glViewer->Set_id(1);    
    
    main_timer = new QTimer();
    connect(main_timer, SIGNAL(timeout()), this, SLOT(updateBTN()));
    main_timer->start(10);
    QWidget::showMaximized();
}

MainWindow::~MainWindow()
{
    if(ros::isStarted()) {
        if(spinner)
        {
            spinner->stop();
        }
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
    }
    wait();
    main_timer->stop();
    delete ui;
}


bool first_sync = true;

void MainWindow::updateBTN(){
	int ind1 = this->ui->dispositivosCB->currentIndex();
	int ind3 = this->ui->vModeCB->currentIndex();
	bool state_sync = this->ui->checkBox->isChecked();
	//std::cout << dispCB << " - " << ind1 << std::endl;
	//std::cout << dispCB2 << " - " << ind2 << std::endl;
	if(changeBTN){
		if(dispCB == 1){
			ind1 ++;
			if(ind1 == 6) ind1 = 0;
		}
	
		if(vModCB == 1){
			ind3 ++;
			if(ind3 == 4) ind3 = 0;
		}
		
		this->ui->dispositivosCB->setCurrentIndex(ind1);
		this->ui->vModeCB->setCurrentIndex(ind3);
		dispCB = 0;
		vModCB = 0;
		changeBTN = false;
	}
	//if(exitCond == 1)
		//this->close();
	if(saveSignal == 1){
		situation.append("Btn Save pressed!");		
		saveSignal = 0;
	}
	ros::NodeHandle nh, nh2;
	if(syncCond == 1){
		if(first_sync == true){
			glViewer->Syncronize(nh, nh2);
			spinner->start();
			first_sync = false;
		}
		if(state_sync == false){
			this->ui->checkBox->setChecked(true);
		}
	}
	else{
		if(state_sync == true){
			this->ui->checkBox->setChecked(false);
			
		}
		first_sync = true;
	}
	if(situation_change == true){
		ui->txtBox->setText(situation);
		situation_change = false;	
	}


	if(imu_on == true){
		ui->imuGP->setVisible(true);
		ui->rollSLBL->setText(QString::number(roll));
		ui->pitchSLBL->setText(QString::number(pitch));
		ui->yawSLBL->setText(QString::number(yaw));
		imu_on = false;
	}
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
    ros::shutdown();
}

// ----------------------------------------------------------------------------------------------------------------------------------

void MainWindow::LaserInit(int viewer){
    ros::NodeHandle laser_nodeHandle;
    if (viewer == 0)
    {
        glViewer->LaserInit(laser_nodeHandle);
        this->ui->dispositivoLbl->setText("Laser");
        this->ui->vModeCB->setVisible(true);
        this->ui->vModeLbl->setVisible(true);
    }
    spinner->start();
}

void MainWindow::ZedInit(int viewer){
    if (viewer == 0)
    {
        glViewer->ZedInit();
        this->ui->dispositivoLbl->setText("Zed");
        this->ui->vModeCB->setVisible(true);
        this->ui->vModeLbl->setVisible(true);
    }
    spinner->start();
}

void MainWindow::AstraInit(int viewer){
    ros::NodeHandle astra_nodeHandle;
    if (viewer == 0){
        glViewer->AstraInit(astra_nodeHandle);
        glViewer->SetStatus(3);
        this->ui->dispositivoLbl->setText("Astra");
        this->ui->vModeCB->setVisible(true);
        this->ui->vModeLbl->setVisible(true);

    }
    spinner->start();
}

void MainWindow::ImuInit(int viewer){
    ros::NodeHandle imu_nodeHandle;
    if (viewer == 0){
        glViewer->ImuInit(imu_nodeHandle);
        if(imu_on = true){
        	glViewer->SetStatus(5);
        	this->ui->dispositivoLbl->setText("Imu");
        	imu_on = false;
        }
        else{
        	glViewer->SetStatus(0);
        	situation.clear();
        	situation.append("Dispositivo IMU não foi conectado!");
        	ui->txtBox->setText(situation);
        }	
        	
    }
    spinner->start();
}

void MainWindow::KinectInit(int viewer){
    ros::NodeHandle kinect_nodeHandle;
    int aux;
    if (viewer == 0)
    {
        aux = glViewer->KinectStart();
        if(aux > 0){
            situation.append("Dispositivo RGBD conectado com sucesso!");
            ui->dispositivoLbl->setText("Kinect");
            glViewer->SetStatus(1);
            this->ui->vModeCB->setVisible(true);
            this->ui->vModeLbl->setVisible(true);
        }else{
            situation.append("Nenhum dispositivo RGBD conectado!");
        }
    }

    spinner->start();
}

// ----------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------

void MainWindow::stopp()
{
    ros::shutdown();
}

//Seleção do Dispositivo

void MainWindow::on_dispositivosCB_activated(int index)
{
    situation.clear();
    int aux;

    if(spinner && !spinner->canStart())
        spinner->stop();

    if(index==0)
    {
        situation.append("Nenhum Dispositivo Selecionado!");

    }
    if(index==1)
        LaserInit(0);
    if(index==2)
        KinectInit(0);
    if(index==3)
        ImuInit(0);
    if(index==4)
        AstraInit(0);
    if(index==5)
        ZedInit(0);
        
    ui->txtBox->setText(situation);
  
}

void MainWindow::on_dispositivosCB_currentIndexChanged(const QString &arg1)
{
	
    situation.clear();
    this->ui->dispositivoLbl->clear();
    this->glViewer->Stop();
    this->ui->vModeCB->setVisible(false);
    this->ui->vModeLbl->setVisible(false);

    if(spinner && !spinner->canStart())
        spinner->stop();
        
        
	int index = this->ui->dispositivosCB->currentIndex();
	std::cout << index << std::endl;
    if(index==0)
    {
        situation.append("Nenhum Dispositivo Selecionado!");
       }
    if(index ==1)
        LaserInit(0);
    if(index==2)
        KinectInit(0);
    if(index==3)
        ImuInit(0);
    if(index==4)
        AstraInit(0);
    if(index==5)
        ZedInit(0);
        
    ui->txtBox->setText(situation);
}

void MainWindow::on_angSpin_valueChanged(double arg1)
{
    QString aux_aux;
    aux_aux.clear();
    int id;
    id = (arg1+135)/0.35;
    //aux_aux.append(QString::number(glViewer2->laser->laserData[id].distancia));

}

void MainWindow::on_vModeCB_currentIndexChanged(int index)
{
	glViewer->ChangeMod(index);
}

void MainWindow::on_pushButton_clicked()
{
	glViewer->saveFiles();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
	situation.clear();
    if(arg1 == 0){
    	situation.append("Syncronization OFF");
    	syncCond = 0;
    	glViewer->Syncronize_OFF();

    }
    else{
        situation.append("Syncronization ON");
        syncCond = 1;
    }
    //std::cout << "sync: " << syncCond << std::endl;
      this->ui->dispositivosCB->setCurrentIndex(0);
      ui->txtBox->setText(situation);
}
