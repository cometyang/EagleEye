#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>
#include "movieviewer.h"
#include "tabdialog.h"
#include "../algorithms/codebook.h"
#include "../algorithms/tracker.h"
#include "../algorithms/edge.h"
#include "../algorithms/mhi.h"

using namespace std;

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
 { 
    Q_OBJECT

public:
    MainWindow();


protected:
    void closeEvent(QCloseEvent *event);

private slots:
  
    void open();
    void edge();
    void mhi();
	void gmmbs();
	void codebook();
    void about();

   

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
	void createDockWindows();
  
    void loadFile(const QString &fileName);



    QString strippedName(const QString &fullFileName);

    MovieViewer *player;
	MovieViewer *detector;
	MovieViewer *tracker;
	
	TabDialog* tabdialog;

	IFrameSource* mainSource;
	IAlgorithmModel* algmodel;
	Tracker* trackerModel;
	
    
	QString curFile;

    QMenu *fileMenu;
    QMenu *algorithmMenu;
	QMenu *viewMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    
   
    QAction *openAct;
    
    QAction *exitAct;
    QAction *edgeAct;
    QAction *gmmbsAct;
	QAction *mhiAct;
	QAction *codebookAct;
    
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif
