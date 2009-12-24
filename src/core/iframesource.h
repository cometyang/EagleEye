#ifndef IFRAMESOURCE_H
#define	IFRAMESOURCE_H

QT_BEGIN_NAMESPACE
class QPixmap;
QT_END_NAMESPACE

class IFrameSource
{
 public:
	 virtual QPixmap* next() = 0; //Obtain next IplImage*

};
#endif