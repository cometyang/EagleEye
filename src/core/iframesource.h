#ifndef IFRAMESOURCE_H
#define	IFRAMESOURCE_H

#include <QObject>
#include <cv.h>

QT_BEGIN_NAMESPACE
class QPixmap;
QT_END_NAMESPACE

class IFrameSource : public QObject
{
 Q_OBJECT
 public:
	 virtual bool hasNext() = 0; //Obtain next IplImage*
	 virtual IplImage* nextFrame() = 0; //retun next Frame
	 virtual void reset() = 0; //Return to initial condition
	 virtual bool isValid() const=0; //Check if source is valid
	 virtual int getFrameCount() const =0; //return frame count in source
	 virtual int getFramePosition() const=0; //return frame position
	 virtual IplImage* setFramePosition(int)=0; //set frame position
	 
 signals:
	 void updated(IplImage*);
	 void frameChanged(int);

};
#endif