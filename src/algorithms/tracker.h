#ifndef TRACKER_H
#define TRACKER_H
#include "cv.h"
#include "cvaux.h"
#include "highgui.h"
#include <iostream>
#include <QObject>

using namespace std;

class Tracker : public QObject
{
 Q_OBJECT
 public:
    
 public slots:	
	void input(CvSeq*, IplImage*); //
 signals:
	void output(IplImage*);
 private:
	IplImage* dstFrame;
};
#endif
