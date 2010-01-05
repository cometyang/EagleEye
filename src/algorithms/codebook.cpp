#include "codebook.h"

CodeBook::CodeBook(IplImage* videoFrame)
{ 
  initialModel(videoFrame);
}

CodeBook::~CodeBook()
{
   if (model) cvReleaseBGCodeBookModel(&model);
   if (yuvFrame) cvReleaseImage(&yuvFrame);
   if (mask) cvReleaseImage(&mask);
}

void
CodeBook::initialModel(IplImage* videoFrame)
{
  nframes=1;
  nframesToLearnBG=10;
  
  model= cvCreateBGCodeBookModel();
  //Set color thresholds to default values
  model->modMin[0] = 3;
  model->modMin[1] = model->modMin[2] = 3;
  model->modMax[0] = 10;
  model->modMax[1] = model->modMax[2] = 10;
  model->cbBounds[0] = model->cbBounds[1] = model->cbBounds[2] = 10;

  yuvFrame = cvCloneImage(videoFrame);
  dstFrame = cvCloneImage(videoFrame);
  cvCvtColor(videoFrame, yuvFrame, CV_BGR2YCrCb );

  cvBGCodeBookUpdate(model, yuvFrame);
  mask = cvCreateImage(cvGetSize(videoFrame), IPL_DEPTH_8U, 1 );
  cvSet(mask,cvScalar(255));
}


void
CodeBook::updateModel(IplImage* videoFrame)
{          
	cvCvtColor(videoFrame, yuvFrame, CV_BGR2YCrCb );//YUV For codebook method
	//This is where we build our background model
	if( nframes-1 < nframesToLearnBG  )
		cvBGCodeBookUpdate( model, yuvFrame );
	if( nframes-1 == nframesToLearnBG  )
		cvBGCodeBookClearStale( model, model->t/2 );
	if( nframes-1 >= nframesToLearnBG  )
	{
		// Find foreground by codebook method
		cvBGCodeBookDiff( model, yuvFrame, mask);
        
        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* contour = 0;
         
        cvThreshold( mask, mask, 1, 255, CV_THRESH_BINARY );
        cvSegmentFGMask(mask);

        cvFindContours( mask, storage, &contour, sizeof(CvContour),
                      CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
		emit
		{
		output(contour, videoFrame);
		}
		cvZero( dstFrame );
        for( ; contour != 0; contour = contour->h_next )
        {
            CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&255 );
            /* replace CV_FILLED with 1 to see the outlines */
            cvDrawContours( dstFrame, contour, color, color, -1, CV_FILLED, 8 );
			CvRect box = cvBoundingRect(contour);
			cvRectangle(dstFrame, cvPoint(box.x,box.y), cvPoint(box.x+box.width, box.y+box.height), CV_RGB(255,0,0));
        }
		emit
		{
			output(dstFrame);
		}
	}
	nframes++;
}

void
CodeBook::input(IplImage* videoFrame)
{
   updateModel(videoFrame);
}