#ifndef IALGORITHMMODEL_H
#define	IALGORITHMMODEL_H

#include <QObject>
#include <cv.h>

class IAlgorithmModel : public QObject
{
 Q_OBJECT
 public:
	virtual void initialModel(IplImage*) = 0; //
	virtual void updateModel(IplImage*) = 0;
 public slots:	
	virtual void input(IplImage*) =0; //
 signals:
	void output(IplImage*);	
};
#endif