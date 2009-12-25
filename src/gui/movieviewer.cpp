#include <QtGui>
#include "movieviewer.h"

MovieViewer::MovieViewer(QWidget* parent)
    : QWidget(parent)
{
	movieLabel = new QLabel(tr("No movie loaded"));
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
   
	currentState=MovieViewer::NotRunning;
	
	viewerTimer = new QTimer(this);
    viewerTimer->setSingleShot(true);
	

	createControls();
    
	mainLayout = new QVBoxLayout;
    mainLayout->addWidget(movieLabel);
	mainLayout->addLayout(controlsLayout);
	setLayout(mainLayout);
	
}
 
void
MovieViewer::showFrame(const QPixmap& showQPixmap)
{
	movieLabel->setPixmap(showQPixmap);
}

void
MovieViewer::setSource(IFrameSource* source)
{
	viewerSource=source;
	connect(viewerSource, SIGNAL(updated(const QPixmap&)), this, SLOT(showFrame(const QPixmap&)));
}
void
MovieViewer::setSource(const QString& filename)
{
	CvCapture * camera = cvCaptureFromAVI(filename.toUtf8());
    assert(camera);
    viewerSource =new CvFrameSource(camera);
	connect(viewerSource, SIGNAL(updated(const QPixmap&)), this, SLOT(showFrame(const QPixmap&)));
}

void 
MovieViewer::setState(ViewerState newState) 
{
	if (newState != currentState) 
	{
		currentState = newState;
		emit stateChanged(newState);
	}
} 

void 
MovieViewer::setPaused(bool paused)
{  
     if (paused) 
	 {
		 if (currentState == MovieViewer::NotRunning)
            return;
        setState(Paused);
        viewerTimer->stop();
	 } else 
	 {
        if (currentState == MovieViewer::Running)
            return;
        setState(MovieViewer::Running);
        viewerTimer->start(10);
     }
}  

void 
MovieViewer::start()
{ 
  	connect(viewerTimer, SIGNAL(timeout()), this, SLOT(queryNextFrame()));
	if (currentState == MovieViewer::NotRunning) 
	{
		viewerTimer->start(10);

    } else if (currentState == MovieViewer::Paused) 
	{
        setPaused(false);
    }
} 

void
MovieViewer::queryNextFrame()
{
	viewerSource->next();
    viewerTimer->start(10);
}
void 
MovieViewer::updateViewer(bool updating)
{ 
	//if (next()) {
	//	if (updating && viewerState == MovieViewer::NotRunning) {
      //      enterState(CvMovie::Running);
            // emit started();
        // }

       // /* if (frameRect.size() != currentPixmap.rect().size()) {
            // frameRect = currentPixmap.rect();
            // emit resized(frameRect.size());
        // }
            // */
        // emit updated(currentPixmap);
     //   emit updated(frameRect);
	// emit frameChanged(getCurrentFrameNumber());

        // if (movieState == CvMovie::Running)
            // nextImageTimer->start(10);
    // } else {
       
       // Graceful finish
        // if (movieState != CvMovie::Paused) {
            // enterState(CvMovie::NotRunning);
            // cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, 0);
	    // emit finished();
        // }
    // }
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
  //  connect(pauseButton, SIGNAL(clicked(bool)), movie, SLOT(setPaused(bool)));

    stopButton = new QToolButton;
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setIconSize(iconSize);
    stopButton->setToolTip(tr("Stop"));
   // connect(stopButton, SIGNAL(clicked()), movie, SLOT(stop()));

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