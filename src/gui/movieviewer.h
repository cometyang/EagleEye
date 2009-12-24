#ifndef MOVIEVIEWER_H
#define MOVIEVIEWER_H

#include <iostream>

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>


#include <cv.h>


using namespace std;

class MovieViewer : public QWidget
{
	Q_OBJECT
    
	public:
		MovieViewer(QWidget *parent=0);
    
	public slots:
		void setIplImage(IplImage*);
	
	private:
		QVBoxLayout *mainLayout;
		QLabel *movieLabel;
	
};

#endif