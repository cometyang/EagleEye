#ifndef MOVIEVIEWER_H
#define MOVIEVIEWER_H

#include <iostream>

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QImage;
class QPixmap;
class QCheckBox;
class QGridLayout;
class QHBoxLayout;
class QSlider;
class QSpinBox;
class QToolButton;
class QVBoxLayout;
QT_END_NAMESPACE

#include <cv.h>


using namespace std;

class MovieViewer : public QWidget
{
	Q_OBJECT
    
	public:
		MovieViewer(QWidget *parent=0);
		enum MovieState 
		{ 
			NotRunning,
			Paused,
			Running
		}; 
    
	public slots:
		void setIplImage(IplImage* frame);
		void updateViewer(bool updating);
	
	private:
		
		void openFile(const QString &fileName);
        void createControls();
        void createButtons();
		
		QLabel *movieLabel;
		QSlider *frameSlider;
         
		QToolButton *openButton;
        QToolButton *playButton;
        QToolButton *pauseButton;
        QToolButton *stopButton;
        QToolButton *quitButton;

		QGridLayout *controlsLayout;
		QHBoxLayout *buttonsLayout;
		QVBoxLayout *mainLayout;
	
};

#endif