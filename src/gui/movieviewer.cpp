#include <QtGui>
#include "movieviewer.h"

MovieViewer::MovieViewer(QWidget* parent)
    : QWidget(parent)
{
	viewerSource=NULL;

	movieLabel = new QLabel(tr("No movie loaded"));
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
  
	viewerTimer = new QTimer(this);
    viewerTimer->setSingleShot(true);
	connect(viewerTimer, SIGNAL(timeout()), this, SLOT(queryNextFrame()));

	createControls();
    connect(this, SIGNAL(stateChanged(ViewerState)), this, SLOT(updateControls()));
	connect(frameSlider, SIGNAL(valueChanged(int)), this, SLOT(goToFrame(int)));
	

	mainLayout = new QVBoxLayout;
    mainLayout->addWidget(movieLabel);
	mainLayout->addLayout(controlsLayout);
	setLayout(mainLayout);
    setState(NotRunning);
}
 
void
MovieViewer::setSource(IFrameSource* source)
{
	viewerSource=source;
	connect(viewerSource, SIGNAL(updated(IplImage*)), this, SLOT(setIplImage(IplImage*)));
	connect(viewerSource, SIGNAL(frameChanged(int)), frameSlider, SLOT(setValue(int)));
    setState(NotRunning);
}

void
MovieViewer::setSource(const QString& filename)
{
	CvCapture * camera = cvCaptureFromAVI(filename.toUtf8());
    assert(camera);
	setSource(new CvFrameSource(camera));
}

void 
MovieViewer::setState(ViewerState newState) 
{
	if (currentState)
	{
		if(newState != currentState) 
		{
		currentState = newState;
		emit stateChanged(newState);
		}
	}
	else
	{
		currentState = newState;
		emit stateChanged(newState);
	}
} 

void
MovieViewer::goToFrame(int pos)
{
	viewerSource->setFramePosition(pos);
}

void 
MovieViewer::pause()
{  
    if (currentState == Running) 
	{
		setState(Paused);
		viewerTimer->stop();
    }
	else
	{
		setState(Running);
		viewerTimer->start(10);
	}
}  

void 
MovieViewer::start()
{ 
  	
	if (currentState == NotRunning) 
	{
		setState(Running);
		viewerTimer->start(10);
    } 
} 

void 
MovieViewer::stop()
{   
    if (currentState != NotRunning)
      {
	      setState(NotRunning);
          viewerTimer->stop(); 
          viewerSource->reset();
       }    
} 

void
MovieViewer::queryNextFrame()
{
	if (viewerSource->hasNext())
	{
		viewerSource->nextFrame();
//		this->setIplImage(((this->parent)->codebookModel)->ImaskCodeBook);
		viewerTimer->start(10);
	}
	else
	{
		stop();
	}
}

void
MovieViewer::setIplImage(IplImage *BGRImage)
{
	
	IplImage* RGBImage=cvCloneImage(BGRImage);
	if (RGBImage->nChannels ==3)
	{
	cvCvtColor(BGRImage, RGBImage, CV_BGR2RGB);
	//cvConvertImage(BGRImage, RGBImage, CV_CVTIMG_SWAP_RB);
    frameQImage=new QImage((uchar *)RGBImage->imageData, RGBImage->width, RGBImage->height, RGBImage->widthStep, QImage::Format_RGB888);
	}
	else if (RGBImage->nChannels ==1)
	{
		frameQImage=new QImage((uchar *)RGBImage->imageData, RGBImage->width, RGBImage->height, RGBImage->widthStep, QImage::Format_Indexed8);
	}
	movieLabel->setPixmap(QPixmap::fromImage(*frameQImage));
	cvReleaseImage(&RGBImage);
}

void 
MovieViewer::createControls()
{
    frameSlider = new QSlider(Qt::Horizontal);
    frameSlider->setTickPosition(QSlider::TicksBelow);
    frameSlider->setTickInterval(5);

    frameSliderLayout = new QHBoxLayout;
    frameSliderLayout->addWidget(frameSlider);
	
	QSize iconSize(16, 16);

    openButton = new QToolButton;
    openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    openButton->setIconSize(iconSize);
    openButton->setToolTip(tr("Open File"));
  //  connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

    playButton = new QToolButton;
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton->setIconSize(iconSize);
    playButton->setToolTip(tr("Play"));
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));

    pauseButton = new QToolButton;
    pauseButton->setCheckable(true);
    pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    pauseButton->setIconSize(iconSize);
    pauseButton->setToolTip(tr("Pause"));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));

    stopButton = new QToolButton;
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setIconSize(iconSize);
    stopButton->setToolTip(tr("Stop"));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));

    quitButton = new QToolButton;
    quitButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    quitButton->setIconSize(iconSize);
    quitButton->setToolTip(tr("Quit"));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(openButton);
    buttonsLayout->addWidget(playButton);
    buttonsLayout->addWidget(pauseButton);
    buttonsLayout->addWidget(stopButton);
    buttonsLayout->addWidget(quitButton);
    buttonsLayout->addStretch();

	controlsLayout = new QVBoxLayout;
	controlsLayout->addLayout(frameSliderLayout);
	controlsLayout->addLayout(buttonsLayout);
}

void MovieViewer::updateControls()
{ 
    playButton->setEnabled(viewerSource && viewerSource->isValid() && viewerSource->getFrameCount() != 1 && currentState == NotRunning);
    pauseButton->setEnabled(currentState != NotRunning);
    pauseButton->setChecked(currentState == Paused);
    stopButton->setEnabled(currentState != NotRunning);
    
	if (viewerSource && viewerSource->isValid())
	{
		if (currentState == NotRunning)
		{
		frameSlider->setMaximum(viewerSource->getFrameCount() - 1);
		frameSlider->setValue(0);
		}
    } 
	else 
	{
        frameSlider->setMaximum(0);
    }
    frameSlider->setEnabled(viewerSource);
} 

