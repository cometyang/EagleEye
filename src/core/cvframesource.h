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
		bool next();
		void reset();
		bool isValid() const;
		int getFrameCount() const;
		int getFramePosition() const;
		void setFramePosition(int);

	

	private:
		CvCapture* sourceCapture;

};


#endif