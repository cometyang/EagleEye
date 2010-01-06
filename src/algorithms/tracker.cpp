#include "tracker.h"
Tracker::Tracker(IplImage* videoFrame)
{ 
   oFrame= cvCloneImage(videoFrame);
   labelImg = cvCreateImage(cvGetSize(videoFrame), IPL_DEPTH_LABEL, 1);
   nextBlobID=1;
   blobDetect = cvCreateBlobDetectorCC();
   newBlobList=NULL;
   blobList=NULL;
}

void
Tracker::input(IplImage* dstFrame, IplImage* videoFrame)
{
    
	cvConvertScale(videoFrame, oFrame, 1, 0);
	//cvThreshold(img, img, 100, 200, CV_THRESH_BINARY);
    //IplImage *chB=cvCreateImage(cvGetSize(img),8,1);

     //cvSplit(img,chB,NULL,NULL,NULL);
	//cvSetImageROI(dstFrame, cvRect(10, 10, dstFrame->height-10, dFrame->width-10));
	CvBlobs blobs;
	unsigned int result = cvLabel(dstFrame, labelImg, blobs);
  /*  for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
    {
    CvContourChainCode *contour = cvGetContour(it->second, labelImg);
    cvRenderContourChainCode(contour, oFrame);

   
    delete contour;
    }*/
   cvFilterByArea(blobs, 100, 50000);
    
   cvUpdateTracks(blobs, tracks, 5., 1);
  
   cvRenderBlobs(labelImg, blobs, oFrame, oFrame,CV_BLOB_RENDER_BOUNDING_BOX);

   cvRenderTracks(tracks, oFrame, oFrame, CV_TRACK_RENDER_ID);
	/*blobDetect->DetectNewBlob(oFrame, dstFrame, newBlobList, blobList);

	if (newBlobList)
	{    //Loop on the new blob found.
        for(int i=0; i<newBlobList->GetBlobNum(); ++i)
        {
            CvBlob* pBN = newBlobList->GetBlob(i);
            pBN->ID = nextBlobID;

            //Check if the size of the new blob is big enough to be inserted in the blobList.
            if(pBN && pBN->w >= CV_BLOB_MINW && pBN->h >= CV_BLOB_MINH)
            {
                   cout << "Add blob #" << nextBlobID << endl; 
                   blobList->AddBlob(pBN);
                   nextBlobID++;                  
            }
        }
	}*/
	emit
	{
	 output(oFrame);
	}
    
}

