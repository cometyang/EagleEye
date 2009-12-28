#ifndef MOVIEVIEWER_H
#define MOVIEVIEWER_H

#include <iostream>

#include <QWidget>

#include "../core/cvframesource.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QImage;
class QTimer;
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
		enum ViewerState 
		{ 
			NotRunning,
			Paused,
			Running
		}; 
        
		
		void setSource(const QString &fileName);
		void setSource(IFrameSource*);

	public slots:
		
		void setState(ViewerState newState);
		void start();
		void pause();
		void stop();
		void queryNextFrame();
		void goToFrame(int);
		void updateControls();
		void setIplImage(IplImage*);
        
	signals:
		void started();
		void stateChanged(ViewerState);
		
	
	private:
		
		
        void createControls();
		

		IFrameSource* viewerSource;

		QLabel *movieLabel;
		QSlider *frameSlider;

		ViewerState currentState;
		QTimer* viewerTimer;
        
		QImage* frameQImage;


		QToolButton *openButton;
        QToolButton *playButton;
        QToolButton *pauseButton;
        QToolButton *stopButton;
        QToolButton *quitButton;

		QHBoxLayout *frameSliderLayout;
		QHBoxLayout *buttonsLayout;
		QVBoxLayout *controlsLayout;
		
		QVBoxLayout *mainLayout;
	
};
#endif