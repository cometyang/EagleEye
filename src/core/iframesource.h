#ifndef IFRAMESOURCE_H
#define	IFRAMESOURCE_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QPixmap;
QT_END_NAMESPACE

class IFrameSource : public QObject
{
 Q_OBJECT
 public:
	 virtual bool next() = 0; //Obtain next IplImage*
	 virtual void reset() = 0; //Return to initial condition
	 virtual bool isValid() const=0; //Check if source is valid
	 virtual int getFrameCount() const =0; //return frame count in source
	 virtual int getFramePosition() const=0; //return frame position
	 virtual void setFramePosition(int)=0; //set frame position
	 
 signals:
	 void updated(const QPixmap&);
	 void frameChanged(int);

};
#endif