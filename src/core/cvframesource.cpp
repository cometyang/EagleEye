#include "cvframesource.h"

CvFrameSource::CvFrameSource(CvCapture* capture) : IFrameSource()
{
      sourceCapture=capture;
	  nextFrame=cvQueryFrame(sourceCapture);
}

void
CvFrameSource::setCapture(CvCapture* capture)
{
      //if(capture) cvReleaseCapture(capture);
	  sourceCapture=capture;
}

QPixmap*
CvFrameSource::next()
{
    nextFrame=cvQueryFrame(sourceCapture);
	return cvtIplImage2QPixmap(nextFrame);
}

QPixmap*
CvFrameSource::cvtIplImage2QPixmap(IplImage *BGRImage)
{
	IplImage* RGBImage=cvCreateImage(cvGetSize(BGRImage), BGRImage->depth, BGRImage->nChannels);
    cvCvtColor(BGRImage, RGBImage, CV_BGR2RGB);
    QImage qimage((uchar *)RGBImage->imageData, RGBImage->width, RGBImage->height, RGBImage->widthStep, QImage::Format_RGB888);
    return &(QPixmap::fromImage(qimage));
   // cvReleaseImage(&RGBImage);
}
