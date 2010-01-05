#include "tracker.h"
void
Tracker::input(CvSeq* contour, IplImage* videoFrame)
{
    dstFrame = cvCloneImage(videoFrame);
	for( ; contour != 0; contour = contour->h_next )
        {
			CvRect box = cvBoundingRect(contour);
			cvRectangle(dstFrame, cvPoint(box.x,box.y), cvPoint(box.x+box.width, box.y+box.height), CV_RGB(255,0,0));
        }
		emit
		{
			output(dstFrame);
		}
    
}

