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
	 virtual void next() = 0; //Obtain next IplImage*
 signals:
	 void updated(const QPixmap&);

};
#endif