#include <QtGui>
#include "viewer.h"

Viewer::Viewer(QWidget* parent)
    : QWidget(parent)
{
	movieLabel = new QLabel(tr("No movie loaded"));
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
    movieLabel->setScaledContents(true);
	
    
   
	mainLayout = new QVBoxLayout;
    mainLayout->addWidget(movieLabel);
	setLayout(mainLayout);
	
}
 
 void
 Viewer::setIplImage(IplImage *BGRImage)
 {
	IplImage* RGBImage=cvCreateImage(cvGetSize(BGRImage), BGRImage->depth, BGRImage->nChannels);
    cvCvtColor(BGRImage, RGBImage, CV_BGR2RGB);
    QImage qimage((uchar *)RGBImage->imageData, RGBImage->width, RGBImage->height, RGBImage->widthStep, QImage::Format_RGB888);
	QPixmap qcvpixmap=QPixmap::fromImage(qimage);
	cout<<" "<<qcvpixmap.height()<<" "<<qcvpixmap.width()<<endl;
	//movieLabel->setPixmap(qcvpixmap);
    //QImage image("test.jpg");
    //movieLabel->setPixmap(QPixmap::fromImage(image));
    cvReleaseImage(&RGBImage);
    
 }

 