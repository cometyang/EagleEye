#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>
//#include "movieplayer.h"
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
    void gmmbs();
    void about();
   

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
  
    void loadFile(const QString &fileName);
  
    QString strippedName(const QString &fullFileName);

  //  MoviePlayer *player;
    QString curFile;

    QMenu *fileMenu;
    QMenu *algorithmMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    
   
    QAction *openAct;
    
    QAction *exitAct;
    QAction *edgeAct;
    QAction *gmmbsAct;
    
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif
