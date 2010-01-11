#include "edge.h"

Edge::Edge(IplImage* videoFrame)
{ 
  initialModel(videoFrame);
}

Edge::~Edge()
{
   if (grayFrame) cvReleaseImage(&grayFrame);
   if (dstFrame) cvReleaseImage(&dstFrame);
   if (mask) cvReleaseImage(&mask);
}

void
Edge::initialModel(IplImage* videoFrame)
{ 
  grayFrame = cvCreateImage(cvGetSize(videoFrame), IPL_DEPTH_8U, 1 );
  dstFrame = cvCreateImage(cvGetSize(videoFrame), IPL_DEPTH_16S, 1 );
  mask = cvCreateImage(cvGetSize(videoFrame), IPL_DEPTH_8U, 1 );
  cvSet(mask,cvScalar(0));
}


void
Edge::updateModel(IplImage* videoFrame)
{          
    cvCvtColor(videoFrame, grayFrame, CV_BGR2GRAY);
	cvSobel(grayFrame, dstFrame, 1, 0, 3);
	cvConvertScaleAbs( dstFrame , mask); 
	cvThreshold( mask, mask, 100, 255, CV_THRESH_BINARY );
	emit
		{
		output(mask);
		output(mask, videoFrame);
		}
}

void
Edge::input(IplImage* videoFrame)
{
   updateModel(videoFrame);
}