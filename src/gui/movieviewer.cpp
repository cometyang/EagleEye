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
   
    createControls();
    createButtons();

   
	mainLayout = new QVBoxLayout;
    mainLayout->addWidget(movieLabel);
	mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);
	
}
 
 void
 MovieViewer::setIplImage(IplImage *BGRImage)
 {
	IplImage* RGBImage=cvCreateImage(cvGetSize(BGRImage), BGRImage->depth, BGRImage->nChannels);
    cvCvtColor(BGRImage, RGBImage, CV_BGR2RGB);
    QImage qimage((uchar *)RGBImage->imageData, RGBImage->width, RGBImage->height, RGBImage->widthStep, QImage::Format_RGB888);
    movieLabel->setPixmap(QPixmap::fromImage(qimage));
    cvReleaseImage(&RGBImage);
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

void MovieViewer::createButtons()
{
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
  //  connect(playButton, SIGNAL(clicked()), movie, SLOT(start()));

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
}

void MovieViewer::createControls()
{
   
    frameSlider = new QSlider(Qt::Horizontal);
    frameSlider->setTickPosition(QSlider::TicksBelow);
    frameSlider->setTickInterval(5);

    controlsLayout = new QGridLayout;
    controlsLayout->addWidget(frameSlider, 1, 0, 1, 6);
   
}

