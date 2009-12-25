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
		void reset();
		bool isValid() const;
		int getFrameCount() const;

	private:
		void cvtIplImage2QPixmap(IplImage*);

		CvCapture* sourceCapture;
		IplImage* RGBImage;
		QImage* nextQImage;
	
};


#endif