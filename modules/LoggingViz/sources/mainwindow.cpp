#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
	ui->setupUi(this);
	this->setUsage();
	connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(initializeClass()));
	connect(ui->actionAbout_DIVA, SIGNAL(triggered()),this,SLOT(aboutDIVA()));
}

void MainWindow::initializeClass(){
	if (ui->radioButton_1->isChecked()) this->makeGPSEnvironment();
	if (ui->radioButton_2->isChecked()) this->makeCAMEnvironment();
	if (ui->radioButton_5->isChecked()) this->makeCANEnvironment();
}

void MainWindow::aboutDIVA(){
	InformDialog *ifdlg = new InformDialog(this);
	ifdlg->show();
}

void MainWindow::setUsage(){
	//Setting Date
	QString date = QString::fromLocal8Bit(ts.getDate().c_str());
	ui->label_3->setText(date);
	//Setting Memory
	QStorageInfo storage=QStorageInfo::root();
	double total=(storage.bytesTotal()/1024/1024/1024);
    double free=(storage.bytesAvailable()/1024/1024/1024);
    double used=total-free;
    int percent=static_cast<int>((used/total)*100);
    ui->progressBar->setValue(percent);
}

// ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * //


//GPS logviz environment setting 
void MainWindow::makeGPSEnvironment(){
	//widget initial
	gpsMapView = new QWebEngineView(this);
	gpsMapPage = gpsMapView->page();
	ui->verticalLayout_1->layout()->addWidget(gpsMapView);
	//gpsMapView->setUrl(QUrl("qrc:///kakao_map.html")); //whae ang dae?
	gpsMapPage->setUrl(QUrl("http://localhost:8080/kakao_map.html"));
	gpsMapPage->setView(gpsMapView);
	gpsMapView->show();
}

void MainWindow::displayGPS(QString latitude, QString longitude, double hdop){
	if(latitude != "0" && longitude != "0"){
		gpsMapPage->runJavaScript(QString("addMarker(%1, %2);").arg(latitude).arg(longitude));
		if(gpscnt == 0 || gpscnt%10 == 0){
			gpsMapPage->runJavaScript(QString("getAddr();"),[this](const QVariant &v){
				gpsaddr = v.toString();
			});
		}
	}
	if(gpscnt%10 == 0){
		if(hdop<=1){
			cout<<1<<endl;
		}else if(hdop<=5){
			cout<<5<<endl;
		}else{
			cout<<"else"<<endl;
		}
	}
	gpscnt++;
}


// ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * //
//Camera logviz environment setting 
void MainWindow::makeCAMEnvironment(){
	//widget initial
	camWidget = new QLabel(this);
	ui->verticalLayout_4->layout()->addWidget(camWidget);

	//thread initial
	cmlvt = new CamLogVizThread(this);

	//SIGNAL&SLOTS
	connect(ui->pushButton_2, SIGNAL(clicked()), cmlvt, SLOT(start()));
	connect(cmlvt, SIGNAL(sendQimage(QImage)),this, SLOT(displayCam(QImage)));
	connect(ui->pushButton_3, SIGNAL(clicked()), cmlvt, SLOT(stop()));
}
//if camlogvizthread send signal sendQimage, then this function is call. 
void MainWindow::displayCam(QImage image){
	camWidget -> setPixmap(QPixmap::fromImage(image).scaled(camWidget->width(), camWidget->height(), Qt::KeepAspectRatio));
	camWidget -> setAlignment(Qt::AlignCenter);
	camWidget -> show();
	QCoreApplication::processEvents();
}
// ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * //

//CAN logviz environment setting
void MainWindow::makeCANEnvironment(){
	//widgets initial
	canSpeedWidget = new SpeedoMeter(this);
	ui->horizontalLayout_2->layout()->addWidget(canSpeedWidget);

	//class initial
	cnlvt = new CanLogVizThread(this);

	//SIGNAL&SLOTS
	connect(ui->pushButton_2, SIGNAL(clicked()), cnlvt, SLOT(start()));
	connect(cnlvt, SIGNAL(sendVel(double)),this, SLOT(displayVel(double)));
	connect(ui->pushButton_3, SIGNAL(clicked()), cnlvt, SLOT(stop()));
}

void MainWindow::displayVel(double value){
	canSpeedWidget->setValue(value);
}

MainWindow::~MainWindow(){
	delete ui;
}

