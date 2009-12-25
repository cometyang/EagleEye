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
        
		void setState(ViewerState newState);
		void setSource(const QString &fileName);
		void setSource(IFrameSource*);

	public slots:
		void showFrame(const QPixmap&);
		
		void start();
		void pause();
		void stop();
		void queryNextFrame();
		void goToFrame(int);
        
		void updateControls();
        
	signals:
		void started();
		void updatedPlayer(const QPixmap&);
		void updatedDetector(const QPixmap&);
		void stateChanged();
		void finished();
		
		void threshholdChanged(int);
	
	private:
		
		
        void createControls();
		

		IFrameSource* viewerSource;

		QLabel *movieLabel;
		QSlider *frameSlider;

		ViewerState currentState;
		QTimer* viewerTimer;
         
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