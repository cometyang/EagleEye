#include "tracker.h"
Tracker::Tracker(IplImage* videoFrame)
{ 
   oFrame= cvCloneImage(videoFrame);
   labelImg = cvCreateImage(cvGetSize(videoFrame), IPL_DEPTH_LABEL, 1);
}

void
Tracker::input(IplImage* dstFrame, IplImage* videoFrame)
{
    
	cvConvertScale(videoFrame, oFrame, 1, 0);
	//cvThreshold(img, img, 100, 200, CV_THRESH_BINARY);
    //IplImage *chB=cvCreateImage(cvGetSize(img),8,1);

     //cvSplit(img,chB,NULL,NULL,NULL);
	//cvSetImageROI(dFrame, cvRect(10, 10, dFrame->height-10, dFrame->width-10));
	CvBlobs blobs;
	cvLabel(dstFrame, labelImg, blobs);

	//cvFilterByArea(blobs, 10, 1000);
    
    //cvUpdateTracks(blobs, tracks, 5., 10);
  
    cvRenderBlobs(labelImg, blobs, oFrame, oFrame,CV_BLOB_RENDER_BOUNDING_BOX);

   // cvRenderTracks(tracks, oFrame, oFrame, CV_TRACK_RENDER_ID);
	
	emit
	{
	 output(oFrame);
	}
    
}

