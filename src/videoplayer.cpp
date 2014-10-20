#include "videoplayer.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QFont>
#include <QDebug>

#include <QFile>

VideoPlayer::VideoPlayer(QVideoWidget *parent) : QVideoWidget(parent)
{    
    player = new QMediaPlayer();
    player->setVideoOutput(this);
    volume = 70;
    player->setVolume(volume);

    QRect rec = QApplication::desktop()->screenGeometry();
    screenWidth = rec.width();
    screenHeight = rec.height();

    QFont font(":/resources/font/pid.ttf", screenHeight/46.95);

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    boxLayout->setSpacing(screenHeight/108);
    box = new QWidget(this);
    box->setGeometry(screenWidth-(screenWidth/12.03), (screenHeight/2)-(screenHeight/8.3), screenWidth/12, screenHeight/4.15);
    box->setStyleSheet("background: black; border: none");
    box->setLayout(boxLayout);
    box->hide();

    pauseLabel = new QLabel();
    pauseLabel->setStyleSheet("color: #181818; background: black; border: none");
    pauseLabel->setFont(font);
    pauseLabel->hide();
    pauseLabel->setText("PAUSE");

    QHBoxLayout *bufferLayout = new QHBoxLayout;
    bufferLayout->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    bufferLayout->setSpacing(screenWidth/384);
    bufferLabel = new QLabel();
    bufferLabel->setStyleSheet("color: black; background: black; border: none");
    bufferLabel->setFont(font);
    bufferLabel->hide();
    bufferLabel->setText("∙");
    bufferLayout->addWidget(bufferLabel);

    skipBar = new QProgressBar();
    skipBar->setFixedWidth(screenWidth/13.71);
    skipBar->setFixedHeight(3);
    skipBar->setStyleSheet (
                 "QProgressBar { background: #181818; border: none }"
                 "QProgressBar::chunk { background: white }"
             );
    skipBar->setTextVisible(false);
    skipBar->setMinimum(0);
    skipBar->setMaximum(15);
    skipBar->hide();

    QVBoxLayout *loopTimeLayout = new QVBoxLayout;
    loopTimeLayout->setSpacing(0);
    startLoopTimeLabel = new QLabel();
    startLoopTimeLabel->setStyleSheet("color: black; background: white; border: none");
    startLoopTimeLabel->setFont(font);
    startLoopTimeLabel->hide();
    stopLoopTimeLabel = new QLabel();
    stopLoopTimeLabel->setStyleSheet("color: black; background: white; border: none");
    stopLoopTimeLabel->setFont(font);
    stopLoopTimeLabel->hide();
    loopTimeLayout->addWidget(startLoopTimeLabel);
    loopTimeLayout->addWidget(stopLoopTimeLabel);

    QVBoxLayout *timeLayout = new QVBoxLayout;
    timeLayout->setSpacing(0);
    currentTimeLabel = new QLabel();
    currentTimeLabel->setStyleSheet("color: black; background: white; border: none");
    currentTimeLabel->setFont(font);
    currentTimeLabel->hide();
    totalTimeLabel = new QLabel();
    totalTimeLabel->setStyleSheet("color: black; background: white; border: none");
    totalTimeLabel->setFont(font);
    totalTimeLabel->hide();
    timeLayout->addWidget(currentTimeLabel);
    timeLayout->addWidget(totalTimeLabel);

    QHBoxLayout *volumeLayout = new QHBoxLayout;
    volumeLayout->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    volumeLayout->setSpacing(screenHeight/216);
    volumeIcon = new QLabel();
    volumeIcon->setStyleSheet("color: white; background: black; border: none");
    volumeIcon->setFont(font);
    volumeIcon->hide();
    volumeIcon->setText("♫");
    volumeLabel = new QLabel();
    volumeLabel->setStyleSheet("color: white; background: black; border: none");
    volumeLabel->setFont(font);
    volumeLabel->hide();
    volumeLabel->setText(QString::number(volume));
    volumeLayout->addWidget(volumeIcon);
    volumeLayout->addWidget(volumeLabel);

    QVBoxLayout *rateLayout = new QVBoxLayout;
    rateLayout->setSpacing(0);
    bitRateLabel = new QLabel();
    bitRateLabel->setStyleSheet("color: white; background: black; border: none");
    bitRateLabel->setFont(font);
    bitRateLabel->hide();
    peersLabel = new QLabel();
    peersLabel->setStyleSheet("color: white; background: black; border: none");
    peersLabel->setFont(font);
    peersLabel->hide();
    rateLayout->addWidget(bitRateLabel);
    rateLayout->addWidget(peersLabel);

    boxLayout->addWidget(pauseLabel);
    boxLayout->addLayout(bufferLayout);
    boxLayout->addWidget(skipBar);
    boxLayout->addLayout(loopTimeLayout);
    boxLayout->addLayout(timeLayout);
    boxLayout->addLayout(volumeLayout);
    boxLayout->addLayout(rateLayout);

    sliderStartLoop = new QSlider(Qt::Horizontal);
    sliderStartLoop->setStyleSheet (
                        "QSlider::groove:horizontal { background: #141414; border: none }"
                        "QSlider::sub-page:horizontal { background: white }"
                        "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                     );
    sliderStartLoop->setMinimum(0);
    sliderStartLoop->setTracking(true);
    sliderStartLoop->setEnabled(false);
    sliderStartLoop->setParent(this);
    sliderStartLoop->hide();

    sliderStopLoop = new QSlider(Qt::Horizontal);
    sliderStopLoop->setStyleSheet (
                        "QSlider::groove:horizontal { background: #141414; border: none }"
                        "QSlider::sub-page:horizontal { background: white }"
                        "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                    );
    sliderStopLoop->setMinimum(0);
    sliderStopLoop->setTracking(true);
    sliderStopLoop->setEnabled(false);
    sliderStopLoop->setParent(this);
    sliderStopLoop->hide();
    
    slider = new QSlider(Qt::Horizontal);
    slider->setGeometry(0, screenHeight-15, screenWidth, 5);
    slider->setStyleSheet (
                "QSlider::groove:horizontal { background: #141414; border: none }"
                "QSlider::sub-page:horizontal { background: white }"
                "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
            );
    slider->setMinimum(0);
    slider->setTracking(true);
    slider->setEnabled(false);
    slider->setParent(this);
    slider->hide();

    progressBar = new QProgressBar();
    progressBar->setGeometry(0, screenHeight-8, screenWidth, 3);
    progressBar->setStyleSheet (
            "QProgressBar { background: #000000; border: none }"
            "QProgressBar::chunk { background: #9c9c9c }"
         );
    progressBar->setTextVisible(false);
    progressBar->setMinimum(0);
    progressBar->setParent(this);
    progressBar->hide();

    connect (sliderStartLoop, SIGNAL(sliderPressed()), this, SLOT(slider_startLoop_pressed()));
    connect (sliderStartLoop, SIGNAL(sliderMoved(int)), this, SLOT(slider_startLoop_moved(int)));
    connect (sliderStartLoop, SIGNAL(sliderMoved(int)), this, SLOT(set_sliderLoop_time(int)));
    connect (sliderStartLoop, SIGNAL(sliderReleased()), this, SLOT(slider_startLoop_released()));
    connect (sliderStopLoop, SIGNAL(sliderPressed()), this, SLOT(slider_stopLoop_pressed()));
    connect (sliderStopLoop, SIGNAL(sliderMoved(int)), this, SLOT(slider_stopLoop_moved(int)));
    connect (sliderStopLoop, SIGNAL(sliderMoved(int)), this, SLOT(set_sliderLoop_time(int)));
    connect (sliderStopLoop, SIGNAL(sliderReleased()), this, SLOT(slider_stopLoop_released()));
    connect (player, SIGNAL(positionChanged(qint64)), this, SLOT(set_currentTime(qint64)));
    connect (player, SIGNAL(durationChanged(qint64)), this, SLOT(set_totalTime(qint64)));
    connect (player, SIGNAL(positionChanged(qint64)), this, SLOT(set_slider_position(qint64)));
    connect (slider, SIGNAL(sliderPressed()), this, SLOT(slider_pressed()));
    connect (slider, SIGNAL(sliderMoved(int)), this, SLOT(slider_moved(int)));
    connect (slider, SIGNAL(sliderReleased()), this, SLOT(slider_released()));
    connect (player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(status_change(QMediaPlayer::MediaStatus)));
    connect (player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(error(QMediaPlayer::Error)));

    loadingStateDelay = new QTimer(this);
    loadingStateDelay->setSingleShot(true);
    loadingStateDelay->setInterval(5000);
    connect (loadingStateDelay, SIGNAL(timeout()), this, SLOT(play_pause_stop()));

    hideControlsDelay = new QTimer(this);
    hideControlsDelay->setSingleShot(true);
    connect (hideControlsDelay, SIGNAL(timeout()), this, SLOT(hide_controls()));
}

VideoPlayer::~VideoPlayer()
{
    _pid->disconnect(this);
    _torrent->disconnect(this);
    player->stop();
    delete player;
}

void VideoPlayer::sandbox(const QString *absoluteFilePath)
{
    onSandbox = true;
    buffering = false;
    skip = false;
    loop = false;
    paused = false;
    skip_key_value = 0;
    update_msec = 0;

    player->setMedia(QUrl::fromLocalFile(*absoluteFilePath));
    player->play();
}

void VideoPlayer::play_pause_stop()
{
    if (!loop) {
        if (player->state() == QMediaPlayer::PlayingState && !buffering) {
            player->pause();
            paused = true;
            pauseLabel->show();
        } else if (player->state() == QMediaPlayer::PausedState && !buffering) {
            player->play();
            paused = false;
            pauseLabel->hide();
        } else if (player->state() == QMediaPlayer::StoppedState) {
            if (update_msec == 0) {
                player->setPosition(0);
                player->play();
            } else {
                slider->setEnabled(true);
                update_msec = update_msec+5000;
                player->setPosition(update_msec);
                player->play();
            }
        } 
    }
}

void VideoPlayer::onBuffering()
{
    static int i = 0;
    if (i%2 == 0)
        bufferLabel->setStyleSheet("color: white; background: black; border: none");
    else
        bufferLabel->setStyleSheet("color: black; background: black; border: none");

    if (buffering) {
        if (i == 0) {
            player->pause();
            slider->setEnabled(false);
            show_controls();
            bufferLabel->show();
        }
        ++i;
        QTimer::singleShot(500, this, SLOT(onBuffering()));
    } else {
        i = 0;
        slider->setEnabled(true);
        bufferLabel->hide();
        hideControlsDelay->start();
        player->play();
    }
}

void VideoPlayer::set_loop()
{
    if (!buffering) {
        if (sliderStartLoop->isHidden()) {
            loop = true;
            paused = true;
            slider->setEnabled(false);
            slider->hide();
            pauseLabel->hide();
            player->pause();
            box->setGeometry(screenWidth-(screenWidth/12.03), (screenHeight/2)-(screenHeight/6.34), screenWidth/12, screenHeight/3.17);
            sliderStartLoop->setGeometry(0, screenHeight-23, screenWidth, 5);
            sliderStartLoop->setMaximum(player->duration());
            sliderStartLoop->setValue(0);
            sliderStopLoop->setGeometry(0, screenHeight-15, screenWidth, 5);
            sliderStopLoop->setMaximum(player->duration());
            sliderStopLoop->setValue(0);
            startLoop_msec = 0;
            stopLoop_msec = 0;
            set_sliderLoop_time(0);
            startLoopTimeLabel->show();
            stopLoopTimeLabel->show();
            sliderStartLoop->setEnabled(true);
            sliderStartLoop->show();
            sliderStopLoop->show();
        } else {
            loop = false;
            paused = false;
            sliderStartLoop->setEnabled(false);
            sliderStopLoop->setEnabled(false);
            slider->setEnabled(true);
            slider->show();
            startLoopTimeLabel->hide();
            stopLoopTimeLabel->hide();
            sliderStartLoop->hide();
            sliderStopLoop->hide();
            box->setGeometry(screenWidth-(screenWidth/12.03), (screenHeight/2)-(screenHeight/8.3), screenWidth/12, screenHeight/4.15);
            player->play();
        }
    }
}

void VideoPlayer::slider_startLoop_pressed()
{
    sliderStopLoop->setEnabled(false);
    hideControlsDelay->stop();
}

void VideoPlayer::slider_startLoop_moved(int position)
{
    sliderStartLoop->setValue(position);
    if(position < readyToRead_msec)
        player->setPosition(position);
    
    if (sliderStartLoop->value() > readyToRead_msec || (sliderStartLoop->value() > sliderStopLoop->value() && stopLoop_msec != 0)) {
        sliderStartLoop->setStyleSheet (
                            "QSlider::groove:horizontal { background: #141414; border: none }"
                            "QSlider::sub-page:horizontal { background: red }"
                            "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                         );
    } else {
        sliderStartLoop->setStyleSheet (
                            "QSlider::groove:horizontal { background: #141414; border: none }"
                            "QSlider::sub-page:horizontal { background: white }"
                            "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                         );
    }
}

void VideoPlayer::slider_startLoop_released()
{
    startLoop_msec = sliderStartLoop->value();

    if (startLoop_msec >= readyToRead_msec) {
         if (stopLoop_msec == 0) {
             startLoop_msec = readyToRead_msec-1500;
             sliderStartLoop->setValue(startLoop_msec);
         }
    } 
    if (startLoop_msec >= stopLoop_msec && stopLoop_msec != 0) {
         startLoop_msec = stopLoop_msec-1000;
         sliderStartLoop->setValue(startLoop_msec);
    }

    if (stopLoop_msec == 0) {
        sliderStartLoop->setEnabled(false);
        sliderStopLoop->setEnabled(true);
    } else {
        sliderStopLoop->setEnabled(true);
        player->setPosition(startLoop_msec);
        hideControlsDelay->start();
    }
    sliderStartLoop->setStyleSheet (
                        "QSlider::groove:horizontal { background: #141414; border: none }"
                        "QSlider::sub-page:horizontal { background: white }"
                        "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                     );
}

void VideoPlayer::slider_stopLoop_pressed()
{
    if (sliderStopLoop->isEnabled()) {
        hideControlsDelay->stop();
        sliderStartLoop->setEnabled(false);
    }
}

void VideoPlayer::slider_stopLoop_moved(int position)
{
    sliderStopLoop->setValue(position);
    if (position < readyToRead_msec)
        player->setPosition(position);

    if (sliderStopLoop->value() > readyToRead_msec || (sliderStopLoop->value() < sliderStartLoop->value())) {
        sliderStopLoop->setStyleSheet (
                            "QSlider::groove:horizontal { background: #141414; border: none }"
                            "QSlider::sub-page:horizontal { background: red }"
                            "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                        );
    } else {
        sliderStopLoop->setStyleSheet (
                            "QSlider::groove:horizontal { background: #141414; border: none }"
                            "QSlider::sub-page:horizontal { background: white }"
                            "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                        );
    }
}

void VideoPlayer::slider_stopLoop_released()
{
    stopLoop_msec = sliderStopLoop->value();

    if (stopLoop_msec > readyToRead_msec) {
        stopLoop_msec = readyToRead_msec-1500;
        sliderStopLoop->setValue(stopLoop_msec);
    }
    if (stopLoop_msec <= startLoop_msec) {
        stopLoop_msec = startLoop_msec+1000;
        sliderStopLoop->setValue(stopLoop_msec);
    }
    sliderStartLoop->setGeometry(0, screenHeight-38, screenWidth, 5);
    sliderStopLoop->setGeometry(0, screenHeight-30, screenWidth, 5);
    player->setPosition(startLoop_msec);
    player->play();
    slider->show();
    paused = false;
    sliderStartLoop->setEnabled(true);
    hideControlsDelay->start();
    sliderStopLoop->setStyleSheet (
                        "QSlider::groove:horizontal { background: #141414; border: none }"
                        "QSlider::sub-page:horizontal { background: white }"
                        "QSlider::handle:horizontal { background: black; border: 1px solid white; width: 13px }"
                    );
}

void VideoPlayer::set_sliderLoop_time(int msecs)
{
    const int hours = msecs/(1000*60*60);
    const int minutes = (msecs-(hours*1000*60*60))/(1000*60);
    const int seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;

    QString formattedTime;
    formattedTime.append(QString("%1").arg(hours, 2, 10, QLatin1Char('0'))+":"+
                         QString("%1").arg(minutes, 2, 10, QLatin1Char('0'))+":"+
                         QString("%1").arg(seconds, 2, 10, QLatin1Char('0')));

    if (sliderStartLoop->value() == 0 && sliderStopLoop->value() == 0) {
        startLoopTimeLabel->setText(formattedTime);
        stopLoopTimeLabel->setText(formattedTime);
    } else if (sliderStartLoop->isEnabled()) {
        startLoopTimeLabel->setText(formattedTime);
    } else if (!sliderStartLoop->isEnabled()) {
        stopLoopTimeLabel->setText(formattedTime);
    }
}

void VideoPlayer::set_currentTime(qint64 msecs)
{
    const int hours = msecs/(1000*60*60);
    const int minutes = (msecs-(hours*1000*60*60))/(1000*60);
    const int seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;

    QString formattedTime;
    formattedTime.append(QString("%1").arg(hours, 2, 10, QLatin1Char('0'))+":"+
                         QString("%1").arg(minutes, 2, 10, QLatin1Char('0'))+":"+
                         QString("%1").arg(seconds, 2, 10, QLatin1Char('0')));

    currentTimeLabel->setText(formattedTime);
}

void VideoPlayer::set_totalTime(qint64 msecs)
{
    progressBar->setMaximum(msecs);
    slider->setRange(0, msecs);

    const int hours = msecs/(1000*60*60);
    const int minutes = (msecs-(hours*1000*60*60))/(1000*60);
    const int seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;

    QString formattedTime;
    formattedTime.append(QString("%1").arg(hours, 2, 10, QLatin1Char('0'))+":"+
                         QString("%1").arg(minutes, 2, 10, QLatin1Char('0'))+":"+
                         QString("%1").arg(seconds, 2, 10, QLatin1Char('0')));

    totalTimeLabel->setText(formattedTime);
}

void VideoPlayer::set_volume(int volume_key_value)
{
    if ((volume > 0 && volume < 100) || (volume == 0 && volume_key_value > 0) || (volume == 100 && volume_key_value < 0)) {
        volume = volume+volume_key_value;
        player->setVolume(volume);
        volumeLabel->setText(QString::number(volume));
        if (volume > 0) {
            volumeIcon->setStyleSheet("background: black; border: none; color: white");
            volumeLabel->setStyleSheet("background: black; border: none; color: white");
        } else {
            volumeIcon->setStyleSheet("background: black; border: none; color: #181818");
            volumeLabel->setStyleSheet("background: black; border: none; color: #181818");
        }
    }
}

void VideoPlayer::download_Information(int bitRate, int peers)
{
    bitRateLabel->setText(QString::number(bitRate)+" KB/s");
    peersLabel->setText(QString::number(peers)+" PRS");
}

void VideoPlayer::set_slider_position(qint64 position)
{
    slider->setValue(position);
}

void VideoPlayer::slider_pressed()
{
    skip = true;
    hideControlsDelay->stop();
    player->pause();
}

void VideoPlayer::slider_moved(int position)
{
    slider->setValue(position);
    set_currentTime(qint64(slider->value()));
    if (slider->value() > progressBar->value()) {
        slider->setStyleSheet (
                    "QSlider::groove:horizontal { background: #141414; border: none }"
                    "QSlider::sub-page:horizontal { background: red }"
                    "QSlider::handle:horizontal { background: black; border: 1px solid #ffffff; width: 13px }"
                );
    } else {
        slider->setStyleSheet (
                    "QSlider::groove:horizontal { background: #141414; border: none }"
                    "QSlider::sub-page:horizontal { background: white }"
                    "QSlider::handle:horizontal { background: black; border: 1px solid #ffffff; width: 13px }"
                );
    }
}

void VideoPlayer::slider_released()
{
    const qint64 total_msec = player->duration();
    const qint64 offset_msec = slider->value()+skip_key_value;
    bool available = false;                               

    if (!loop) {
        QMetaObject::invokeMethod (_torrent, "piece_is_available", Qt::DirectConnection, Q_RETURN_ARG(bool, available), Q_ARG(qint64, total_msec), Q_ARG(qint64, offset_msec));
        if ((slider->value() < progressBar->value()) && (offset_msec < readyToRead_msec) && available) {
            if (skip_key_value != 0) {
                player->setPosition(offset_msec);
            } else {
                skip = false;
                player->setPosition(qint64(slider->value()));
                player->play();
                hideControlsDelay->start();
            }
        } else if (skip_key_value == 0 && !available) {
            pauseLabel->hide();
            progressBar->hide();
            progressBar->setValue(slider->value()+20000);
            skipBar->show();
            slider->setEnabled(false);
            slider->setStyleSheet (
                        "QSlider::groove:horizontal { background: #141414; border: none }"
                        "QSlider::sub-page:horizontal { background: #9c9c9c }"
                        "QSlider::handle:horizontal { background: black; border: 1px solid #ffffff; width: 13px }"
                    );
            QMetaObject::invokeMethod (_torrent, "piece_update", Qt::DirectConnection, Q_ARG(qint64, total_msec), Q_ARG(qint64, offset_msec));
        } 
    }
    skip_key_value = 0;
    buffering = false;
    this->setFocus();
}

void VideoPlayer::progress(qint64 total_kb=0, qint64 downloaded_kb=0, int downloadedSkip_mb=0)
{
    if (!skip && !onSandbox) {
        readyToRead_msec = ((downloaded_kb*player->duration())/total_kb)-60000;
        if (readyToRead_msec >= (player->duration()-70000))
            readyToRead_msec = player->duration();
        progressBar->setValue(readyToRead_msec+40000);
        //progressBar->setValue(readyToRead_msec);

        if (!paused) {
            if (slider->value() < readyToRead_msec) {
                if (player->state() == QMediaPlayer::PausedState)
                    buffering = false;
            } else {
                if (player->state() == QMediaPlayer::PlayingState) {
                    buffering = true;
                    onBuffering();
                }
            }
        }

        if (loop && player->state() == 1)
            if (slider->value() >= stopLoop_msec)
                player->setPosition(startLoop_msec);

    } else if (!onSandbox) {
        skipBar->setValue(downloadedSkip_mb);
    }
}

void VideoPlayer::update_player()
{
    skipBar->hide();
    skipBar->setValue(0);
    slider->setEnabled(true);
    hideControlsDelay->start();

    update_msec = slider->value();
    player->setPosition(update_msec);
    player->play();
    slider->setStyleSheet (
                "QSlider::groove:horizontal { background: #141414; border: none }"
                "QSlider::sub-page:horizontal { background: white }"
                "QSlider::handle:horizontal { background: black; border: 1px solid #ffffff; width: 13px }"
            );
    skip = false;
}

void VideoPlayer::show_controls()
{
    hideControlsDelay->stop();

    box->show();
    if (buffering) 
        bufferLabel->show();
    if (loop) {
        startLoopTimeLabel->show();
        stopLoopTimeLabel->show();
        sliderStartLoop->show();
        sliderStopLoop->show();
    }
    currentTimeLabel->show();
    totalTimeLabel->show();
    volumeIcon->show();
    volumeLabel->show();
    bitRateLabel->show();
    peersLabel->show();
    slider->show();
    progressBar->show();
}

void VideoPlayer::hide_controls()
{
    if ((!loop && !paused) || (loop && player->state() == 1)) {
        box->hide();
        pauseLabel->hide();
        bufferLabel->hide();
        startLoopTimeLabel->hide();
        stopLoopTimeLabel->hide();
        currentTimeLabel->hide();
        totalTimeLabel->hide();
        volumeIcon->hide();
        volumeLabel->hide();
        bitRateLabel->hide();
        peersLabel->hide();
        sliderStartLoop->hide();
        sliderStopLoop->hide();
        slider->hide();
        progressBar->hide();
    }
}

void VideoPlayer::keyPressEvent(QKeyEvent *event)
{
    if (!skip) {
        show_controls();
        if (!buffering)
            hideControlsDelay->start();

        if (event->key() == Qt::Key_Space) {
            play_pause_stop();
        } else if (event->key() == Qt::Key_Left) {
            skip_key_value = -10000;
            slider_released();
        } else if (event->key() == Qt::Key_Right) {
            skip_key_value = 10000;
            slider_released();
        } else if (event->key() == Qt::Key_Up) {
            set_volume(5);
        } else if (event->key() == Qt::Key_Down) {
            set_volume(-5);
        } else if ((event->key() == Qt::Key_L) && (event->modifiers() & Qt::ControlModifier)) {
            set_loop();
        }
    }
    if (!onSandbox) {
        if ((event->key() == (Qt::Key_Escape))) {
            QMetaObject::invokeMethod (_pid, "player_handle", Qt::QueuedConnection, Q_ARG(QString, ""), Q_ARG(bool, false), Q_ARG(bool, false), Q_ARG(bool, false), Q_ARG(bool, true));
        } else if ((event->key() == (Qt::Key_Q)) && (event->modifiers() & Qt::ControlModifier)) {
            this->~VideoPlayer();
            QMetaObject::invokeMethod (_pid, "quit", Qt::QueuedConnection);
        }
    }
    event->accept();
}

void VideoPlayer::mousePressEvent(QMouseEvent *event)
{
    if (!skip) {
        show_controls();
        if (!buffering)
            hideControlsDelay->start();
        this->setFocus();
        event->accept();
    }
}

void VideoPlayer::status_change(QMediaPlayer::MediaStatus status)
{
    qDebug() << "-- STATUS: " << status;

    if (status == QMediaPlayer::LoadingMedia) {
        if (onSandbox)
            loadingStateDelay->start();
    } else if (status == QMediaPlayer::BufferedMedia) {
        if (onSandbox) {
            loadingStateDelay->stop();
            onSandbox = false;
            slider->setEnabled(true);
            QMetaObject::invokeMethod (_pid, "player_handle", Qt::QueuedConnection, Q_ARG(QString, ""), Q_ARG(bool, false), Q_ARG(bool, false), Q_ARG(bool, true), Q_ARG(bool, false));
            this->setFocus();
            box->show();
            currentTimeLabel->show();
            totalTimeLabel->show();
            volumeIcon->show();
            volumeLabel->show();
            bitRateLabel->show();
            peersLabel->show();
            slider->show();
            progressBar->show();
            hideControlsDelay->start(3000);
        } else if (skip) {
            skip = false;
            hideControlsDelay->start();
        }
    } else if (status == QMediaPlayer::UnknownMediaStatus || status == QMediaPlayer::NoMedia || status == QMediaPlayer::InvalidMedia || status == QMediaPlayer::EndOfMedia) {
        if (update_msec == 0) {
            loadingStateDelay->stop();
            QTimer::singleShot(5000, this, SLOT(play_pause_stop()));
        } else {
            skip = true;
            slider->setEnabled(false);
            show_controls();
            QTimer::singleShot(1000, this, SLOT(play_pause_stop()));
        }
    }
}

void VideoPlayer::error(QMediaPlayer::Error)
{
    qDebug() << "-- ERROR: " << player->QMediaPlayer::error();
}
