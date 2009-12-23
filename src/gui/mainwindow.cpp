/*mian window*/
#include <QtGui>
#include "mainwindow.h"
#include "viewer.h"
#include "highgui.h"

MainWindow::MainWindow()
 {
    Viewer *player = new Viewer(this);
    setCentralWidget(player);
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    setWindowTitle(tr("Movie Player"));
    resize(800, 800);
   
}
void MainWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
   
}
void MainWindow::open()
{ 
	QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
  
}
void MainWindow::about()
{ 
	QMessageBox::about(this, tr("About Application"), tr("MSU Motion Detection."));
} 

void MainWindow::edge()
 { 

 // center->myAlgorithm=EDGE;

} 

void MainWindow::gmmbs()
 { 
  
  // center->myAlgorithm=GMMBS;
}
void MainWindow::createActions()
 { 

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    
    edgeAct = new QAction(tr("edge"),this);
    edgeAct->setStatusTip(tr("edge")); 
    connect(edgeAct, SIGNAL(triggered()), this, SLOT(edge()));

    gmmbsAct = new QAction(tr("gmmbs"),this);
    gmmbsAct->setStatusTip(tr("gmmbs")); 
    connect(gmmbsAct, SIGNAL(triggered()), this, SLOT(gmmbs()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
  
    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    
    menuBar()->addSeparator();
    algorithmMenu = menuBar()->addMenu(tr("&Algorithm"));  
    algorithmMenu->addAction(edgeAct);
    algorithmMenu->addAction(gmmbsAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}  

void MainWindow::createToolBars()
{ 
    fileToolBar = addToolBar(tr("File"));
  
    fileToolBar->addAction(openAct);
} 

void MainWindow::createStatusBar()
{ 
    statusBar()->showMessage(tr("Ready"));
} 

void MainWindow::loadFile(const QString &fileName)
 { 
    
    CvCapture * camera = cvCaptureFromAVI(fileName.toUtf8());
    assert(camera);
    IplImage * frame=cvQueryFrame(camera);
    assert(frame);
	
	player->setIplImage(frame);
    statusBar()->showMessage(tr("file loaded"), 2000);
} 

QString MainWindow::strippedName(const QString &fullFileName)
{ 
    return QFileInfo(fullFileName).fileName();
} 

