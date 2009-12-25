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
		void next();

	private:
		void cvtIplImage2QPixmap(IplImage*);

		CvCapture* sourceCapture;
		IplImage* nextFrame;
		QImage nextQImage;
		QImage nextQPixmap;
};


#endif