#ifndef VIEWER_H
#define VIEWER_H

#include <iostream>

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>


#include <cv.h>


using namespace std;

class Viewer : public QWidget
{
	Q_OBJECT
    
	public:
		Viewer(QWidget *parent=0);
    public slots:
		void setIplImage(IplImage*);
		
	
	private:
		
		QVBoxLayout *mainLayout;
		QLabel *movieLabel;
		QPixmap currentPixmap;
		
};

#endif