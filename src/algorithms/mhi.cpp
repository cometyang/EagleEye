#include "mhi.h"

MHI::MHI(IplImage* videoFrame)
{
	
	MHI_DURATION = 1.0;
	MAX_TIME_DELTA = 0.5;
	MIN_TIME_DELTA = 0.1;
 
	// Number of cyclic frame image_bufferfer used for motion detection (depend on FPS)
	N = 2;
	DIFFERENCE_THRESHOLD = 40;
 
	// Image image_buffer
	image_buffer = 0;
	last_index = 0;
	timestamp = 0;
 
	// Temporary images
	mhi = NULL;
	silhouette = NULL;
	orientation = NULL;
	orientation_mask = NULL;
	segment_mask = NULL;
 
	// Temporary storage
	storage = 0;
	initialModel(videoFrame);
} 

MHI::~MHI()
{
    for(int i = 0; i < N; i++) {
    cvReleaseImage(&image_buffer[i]);
  }
  
  cvReleaseImage(&mhi);
  cvReleaseImage(&silhouette);
  cvReleaseImage(&orientation);
  cvReleaseImage(&orientation_mask);
  cvReleaseImage(&segment_mask);
  
  if (storage)
    cvClearMemStorage(storage);
}

 
// Initialize heavily used images (once).
void
MHI::initialModel(IplImage* videoFrame)
{
  // allocate images at the beginning or
  // reallocate them if the frame image_size is changed
  CvSize image_size=cvGetSize(videoFrame);
  if (!mhi || mhi->width != image_size.width || mhi->height != image_size.height) {
      if (image_buffer == 0) {
          image_buffer = (IplImage**)malloc(N*sizeof(image_buffer[0]));
          memset(image_buffer, 0, N*sizeof(image_buffer[0]));
      }
      
  
      
      for(int i = 0; i < N; i++) {
          image_buffer[i] = cvCreateImage(image_size, IPL_DEPTH_8U, 1);
          cvZero(image_buffer[i]);
      }
      
      mhi = cvCreateImage(image_size, IPL_DEPTH_32F, 1);
      cvZero(mhi); // clear MHI at the beginning
      silhouette = cvCreateImage(image_size, IPL_DEPTH_32F, 1);
      orientation = cvCreateImage(image_size, IPL_DEPTH_32F, 1);
      segment_mask = cvCreateImage(image_size, IPL_DEPTH_32F, 1);
      orientation_mask = cvCreateImage(image_size, IPL_DEPTH_8U, 1);
  }
}
 
// Update Motion History Image: Calculate motion features and orientation.
void
MHI::updateModel(IplImage* image)
{
    double timestamp = (double)clock()/CLOCKS_PER_SEC; // get current time in seconds
    CvSize image_size = cvSize(image->width, image->height); // get current frame image_size
    int previous_frame_index = last_index, current_frame_index;
    
    initialModel(image);
    
    cvCvtColor(image, image_buffer[last_index], CV_BGR2GRAY); // convert frame to grayscale
    
    current_frame_index = (last_index + 1) % N; // index of (last_index - (N-1))th frame
    last_index = current_frame_index;
    
    silhouette = image_buffer[current_frame_index];
    
    cvAbsDiff(image_buffer[previous_frame_index], image_buffer[current_frame_index], silhouette); // Get difference between frames
    cvThreshold(silhouette, silhouette, DIFFERENCE_THRESHOLD, 1, CV_THRESH_BINARY); // Add threshold
    
    cvUpdateMotionHistory(silhouette, mhi, timestamp, MHI_DURATION); // Update MHI
    cvCvtScale(mhi, orientation_mask, 255./MHI_DURATION, (MHI_DURATION - timestamp)*255./MHI_DURATION);
    cvSegmentFGMask(orientation_mask);

	emit
		{
		output(orientation_mask);
		output(orientation_mask, image);
		}
}

void
MHI::input(IplImage* videoFrame)
{
   updateModel(videoFrame);
}