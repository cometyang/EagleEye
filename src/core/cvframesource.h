#ifndef CVFRAMESOURCE_H
#define	CVFRAMESOURCE_H

#include <QWidget>
#include <cv.h>
#include <highgui.h>
#include "iframesource.h"

class CvFrameSource : public IFrameSource
{
    public:
	    CvFrameSource(CvCapture*);
		void setCapture(CvCapture*);
		QPixmap* next();
		
	private:
		CvCapture* sourceCapture;
		IplImage* nextFrame;
		QPixmap* cvtIplImage2QPixmap(IplImage*);
};


#endif