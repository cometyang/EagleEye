#ifndef CVFRAMESOURCE_H
#define	CVFRAMESOURCE_H

#include <QWidget>
#include <deque>
#include <cv.h>
#include <highgui.h>
#include "iframesource.h"

class CvFrameSource : public IFrameSource
{
    public:
	    CvFrameSource(CvCapture*);
		void setCapture(CvCapture*);	
		bool hasNext();
		IplImage* nextFrame();

		void reset();
		bool isValid() const;
		int getFrameCount() const;
		int getFramePosition() const;
		IplImage* setFramePosition(int);
		

	

	private:
		CvCapture* sourceCapture;
		IplImage* nextIplImage;

};


#endif