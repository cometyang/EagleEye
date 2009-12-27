#include "cvframesource.h"

CvFrameSource::CvFrameSource(CvCapture* capture) : IFrameSource()
{
      sourceCapture=capture;
	  
	  //BufferLength=10;     
	 
	
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
	emit
	{
		updated(cvQueryFrame(sourceCapture));
	    frameChanged(getFramePosition());
	}
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
   emit
	{
		updated(cvQueryFrame(sourceCapture));
	  //  frameChanged(pos);
	}
   }
}


