#ifndef CODEBOOK_H
#define CODEBOOK_H
#include "ialgorithmmodel.h"
#include "cvaux.h"
#include "highgui.h"
#include "cxmisc.h"
#include <iostream>

using namespace std;

class CodeBook  : public IAlgorithmModel
{
  Q_OBJECT
  public:
    CodeBook(IplImage*);
    ~CodeBook();
	void initialModel(IplImage*);
	void updateModel(IplImage*);

  public slots: 
    void input(IplImage*);
	
  private:
    int nframes;
    int nframesToLearnBG;

	IplImage* yuvFrame;
	IplImage* mask;
	IplImage* dstFrame;
	
	CvBGCodeBookModel* model;
};

#endif
