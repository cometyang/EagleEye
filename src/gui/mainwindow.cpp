/*mian window*/
#include <QtGui>
#include "mainwindow.h"
#include "highgui.h"
#include "cuda/cudaTest.h"

MainWindow::MainWindow()
 {
    createActions();
    createMenus();
    createToolBars();
	createDockWindows();
    createStatusBar();

    setWindowTitle(tr("Movie Player"));
	setUnifiedTitleAndToolBarOnMac(true);
    setAnimated(true);
    setDockNestingEnabled (true);
	runTestCuda();    
	resize(300, 400);
   
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
	QMessageBox::about(this, tr("About"), tr("<h4><i>Motion Detection Application</i></h4>"
		      "<h4><font color=maroon>Mississippi State University </font></h4>"
		      "<h4><font color=red>Author: He Yang </font></h4>"));
} 

void MainWindow::edge()
{ 

	disconnect(mainSource, SIGNAL(updated(IplImage*)), algmodel, SLOT(input(IplImage*)));
	disconnect(algmodel, SIGNAL(output(IplImage*)), detector, SLOT(setIplImage(IplImage*)));
    disconnect(algmodel, SIGNAL(output(IplImage*, IplImage*)), trackerModel, SLOT(input(IplImage*, IplImage*)));
    
	delete algmodel;
	algmodel= new Edge(mainSource->nextFrame());
	
	connect(mainSource, SIGNAL(updated(IplImage*)), algmodel, SLOT(input(IplImage*)));
	connect(algmodel, SIGNAL(output(IplImage*)), detector, SLOT(setIplImage(IplImage*)));
   // connect(algmodel, SIGNAL(output(IplImage*, IplImage*)), trackerModel, SLOT(input(IplImage*, IplImage*)));


} 

void MainWindow::mhi()
{ 

	disconnect(mainSource, SIGNAL(updated(IplImage*)), algmodel, SLOT(input(IplImage*)));
	disconnect(algmodel, SIGNAL(output(IplImage*)), detector, SLOT(setIplImage(IplImage*)));
    disconnect(algmodel, SIGNAL(output(IplImage*, IplImage*)), trackerModel, SLOT(input(IplImage*, IplImage*)));
    
	delete algmodel;
	algmodel= new MHI(mainSource->nextFrame());
	
	connect(mainSource, SIGNAL(updated(IplImage*)), algmodel, SLOT(input(IplImage*)));
	connect(algmodel, SIGNAL(output(IplImage*)), detector, SLOT(setIplImage(IplImage*)));
    connect(algmodel, SIGNAL(output(IplImage*, IplImage*)), trackerModel, SLOT(input(IplImage*, IplImage*)));


} 
void MainWindow::gmmbs()
{ 
  
  // center->myAlgorithm=GMMBS;
}

void MainWindow::codebook()
{
	disconnect(mainSource, SIGNAL(updated(IplImage*)), algmodel, SLOT(input(IplImage*)));
	disconnect(algmodel, SIGNAL(output(IplImage*)), detector, SLOT(setIplImage(IplImage*)));
    disconnect(algmodel, SIGNAL(output(IplImage*, IplImage*)), trackerModel, SLOT(input(IplImage*, IplImage*)));
    
	delete algmodel;
	algmodel= new CodeBook(mainSource->nextFrame());
	
	connect(mainSource, SIGNAL(updated(IplImage*)), algmodel, SLOT(input(IplImage*)));
	connect(algmodel, SIGNAL(output(IplImage*)), detector, SLOT(setIplImage(IplImage*)));
    connect(algmodel, SIGNAL(output(IplImage*, IplImage*)), trackerModel, SLOT(input(IplImage*, IplImage*)));
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

    mhiAct = new QAction(tr("mhi"),this);
    mhiAct->setStatusTip(tr("mhi")); 
    connect(mhiAct, SIGNAL(triggered()), this, SLOT(mhi()));

	codebookAct = new QAction(tr("codebook"),this);
    codebookAct->setStatusTip(tr("codebook")); 
    connect(codebookAct, SIGNAL(triggered()), this, SLOT(codebook()));

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
    algorithmMenu->addAction(mhiAct);
	algorithmMenu->addAction(codebookAct);

	menuBar()->addSeparator();
    viewMenu = menuBar()->addMenu(tr("&View")); 

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

void MainWindow::createDockWindows()
{ 
    QDockWidget *dock = new QDockWidget(tr("Player"), this);
    player = new MovieViewer(dock);
    dock->setWidget(player);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Detector"), this);
    detector = new MovieViewer(dock);
    dock->setWidget(detector);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Tracker"), this);
    tracker = new MovieViewer(dock);
    dock->setWidget(tracker);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

	connect(player, SIGNAL(stateChanged(ViewerState)), detector, SLOT(setState(ViewerState)));
	connect(detector, SIGNAL(stateChanged(ViewerState)), tracker, SLOT(setState(ViewerState)));
	//connect(tracker, SIGNAL(stateChanged(ViewerState)), player, SLOT(setState(ViewerState)));
} 

void MainWindow::createStatusBar()
{ 
    statusBar()->showMessage(tr("Ready"));
} 

void MainWindow::loadFile(const QString &filename)
 { 
    CvCapture * camera = cvCaptureFromAVI(filename.toUtf8());
    assert(camera);
    mainSource =new CvFrameSource(camera);
    algmodel= new CodeBook(mainSource->nextFrame());
	trackerModel = new Tracker(mainSource->nextFrame());
	tabdialog = new TabDialog(filename);
    tabdialog->show();

	connect(mainSource, SIGNAL(updated(IplImage*)), algmodel, SLOT(input(IplImage*)));
	connect(algmodel, SIGNAL(output(IplImage*)), detector, SLOT(setIplImage(IplImage*)));
    connect(algmodel, SIGNAL(output(IplImage*, IplImage*)), trackerModel, SLOT(input(IplImage*, IplImage*)));
    connect(trackerModel, SIGNAL(output(IplImage*)), tracker, SLOT(setIplImage(IplImage*)));

	player->setSource(mainSource);
	
	
	
	
    statusBar()->showMessage(tr("file loaded"), 2000);
} 

QString MainWindow::strippedName(const QString &fullFileName)
{ 
    return QFileInfo(fullFileName).fileName();
} 

