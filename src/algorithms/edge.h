#ifndef EDGE_H
#define EDGE_H
#include "ialgorithmmodel.h"
#include "cvaux.h"
#include "highgui.h"
#include "cxmisc.h"
#include <iostream>

using namespace std;

class Edge  : public IAlgorithmModel
{
  Q_OBJECT
  public:
    Edge(IplImage*);
    ~Edge();
	void initialModel(IplImage*);
	void updateModel(IplImage*);

  public slots: 
    void input(IplImage*);
	
  private:
	IplImage* mask;
	IplImage* dstFrame;
	IplImage* grayFrame;
};

#endif
