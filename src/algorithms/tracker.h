#ifndef TRACKER_H
#define TRACKER_H
#include "cv.h"
#include <highgui.h>
#include <cvaux.h>
#include <cvblob.h>
#include <iostream>
#include <QObject>

using namespace std;

class Tracker : public QObject
{
 Q_OBJECT
 public:
    Tracker(IplImage*);
 public slots:	
	void input(IplImage*, IplImage*); //
 signals:
	void output(IplImage*);
 private:
	
	IplImage* oFrame;
	IplImage* labelImg;
	CvTracks tracks;
	CvBlobSeq* newBlobList; 
	CvBlobSeq* blobList;
	int nextBlobID;
	CvBlobDetector* blobDetect;
};
#endif
