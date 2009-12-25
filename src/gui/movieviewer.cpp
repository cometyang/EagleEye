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
MovieViewer::updateViewer(bool updating)
{ 
    // if (next()) {
	// if (updating && viewerState == MovieViewer::NotRunning) {
            // enterState(CvMovie::Running);
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
MovieViewer::setState(ViewerState newState) 
{
	if (newState != currentState) 
	{
		currentState = newState;
		emit stateChanged(newState);
	}
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
  //  connect(playButton, SIGNAL(clicked()), this, SLOT(start()));

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