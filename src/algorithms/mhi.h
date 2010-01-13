#ifndef MHI_H
#define MHI_H
 
#include <cv.h>
#include <highgui.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <cvaux.h>
#include "ialgorithmmodel.h"


 
using namespace std;

class MHI  : public IAlgorithmModel
{
  Q_OBJECT
  public:
    MHI(IplImage*);
    ~MHI();
	void initialModel(IplImage*);
	void updateModel(IplImage*);
    void clear_up_images();
  public slots: 
    void input(IplImage*);
	
  private:
    
	double MHI_DURATION;
	double MAX_TIME_DELTA;
	double MIN_TIME_DELTA;
 
	// Number of cyclic frame image_bufferfer used for motion detection (depend on FPS)
	int N;
	int DIFFERENCE_THRESHOLD;
 
	// Image image_buffer
	IplImage **image_buffer;
	int last_index;
	double timestamp;
 
	// Temporary images
	IplImage *mhi;
	IplImage *silhouette;
	IplImage *orientation;
	IplImage *orientation_mask;
	IplImage *segment_mask;
 
	// Temporary storage
	CvMemStorage *storage;
 
	
	void clean_up_images();
	void initialize_images(IplImage*);
	void motionDetection(IplImage* );
};
 
#endif //MOTION_DETECTION