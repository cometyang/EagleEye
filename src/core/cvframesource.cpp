#include "cvframesource.h"

CvFrameSource::CvFrameSource(CvCapture* capture) : IFrameSource()
{
      sourceCapture=capture;
	  RGBImage=NULL;
	  nextQImage=NULL;
	
}

void
CvFrameSource::setCapture(CvCapture* capture)
{
      //if(capture) cvReleaseCapture(capture);
	  sourceCapture=capture;
}

bool
CvFrameSource::next()
{
    if (getFramePosition()<(getFrameCount()-1))
	{
	cvtIplImage2QPixmap(cvQueryFrame(sourceCapture));
	emit
	{
		updated(QPixmap::fromImage(*nextQImage));
	    frameChanged(getFramePosition());
	}
	if (RGBImage) cvReleaseImage(&RGBImage);
	return true;
	}
	else
	{
	return false;
	}
}



void
CvFrameSource::reset()
{
	cvSetCaptureProperty(sourceCapture, CV_CAP_PROP_POS_FRAMES, 0);
}

bool
CvFrameSource::isValid() const
{ 
  if (sourceCapture)
	  return true;
  else
	  return false;
} 

int
CvFrameSource::getFrameCount() const
{
  return cvGetCaptureProperty(sourceCapture, CV_CAP_PROP_FRAME_COUNT);
}

int
CvFrameSource::getFramePosition() const
 { 
   return cvGetCaptureProperty(sourceCapture, CV_CAP_PROP_POS_FRAMES);  
}

void
CvFrameSource::setFramePosition(int pos)
{ 
   if (getFramePosition() != pos && pos<(getFrameCount()-1))
   {
   cvSetCaptureProperty(sourceCapture, CV_CAP_PROP_POS_FRAMES, pos);
   cvtIplImage2QPixmap(cvQueryFrame(sourceCapture));
   emit
	{
		updated(QPixmap::fromImage(*nextQImage));
	  //  frameChanged(pos);
	}
   if (RGBImage) cvReleaseImage(&RGBImage);
   }
}

void
CvFrameSource::cvtIplImage2QPixmap(IplImage *BGRImage)
{
	RGBImage=cvCreateImage(cvGetSize(BGRImage), BGRImage->depth, BGRImage->nChannels);
    cvCvtColor(BGRImage, RGBImage, CV_BGR2RGB);
    nextQImage=new QImage((uchar *)RGBImage->imageData, RGBImage->width, RGBImage->height, RGBImage->widthStep, QImage::Format_RGB888);
}
