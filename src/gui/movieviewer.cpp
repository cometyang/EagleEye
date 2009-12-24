#include <QtGui>
#include "movieviewer.h"

MovieViewer::MovieViewer(QWidget* parent)
    : QWidget(parent)
{
	movieLabel = new QLabel(tr("No movie loaded"));
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
   
	mainLayout = new QVBoxLayout;
    mainLayout->addWidget(movieLabel);
	setLayout(mainLayout);
	
}
 
 void
 MovieViewer::setIplImage(IplImage *BGRImage)
 {
	IplImage* RGBImage=cvCreateImage(cvGetSize(BGRImage), BGRImage->depth, BGRImage->nChannels);
    cvCvtColor(BGRImage, RGBImage, CV_BGR2RGB);
    QImage qimage((uchar *)RGBImage->imageData, RGBImage->width, RGBImage->height, RGBImage->widthStep, QImage::Format_RGB888);
    movieLabel->setPixmap(QPixmap::fromImage(qimage));
    cvReleaseImage(&RGBImage);
 }

 