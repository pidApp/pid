#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>

class VideoPlayer : public QVideoWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QVideoWidget *parent = 0);
    ~VideoPlayer();

    Q_INVOKABLE void download_Information(int bitRate, int peers);
    Q_INVOKABLE void progress(qint64 total_kb, qint64 downloaded_kb, int downloadedSkip_mb);
    Q_INVOKABLE void update_player();

    QObject *_pid;
    QObject *_torrent;

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void sandbox(const QString *absoluteFilePath);

private:
    QMediaPlayer *player;
    QWidget *box;
    QLabel *pauseLabel;
    QLabel *bufferLabel;
    QProgressBar *skipBar;
    QLabel *startLoopTimeLabel;
    QLabel *stopLoopTimeLabel;
    QLabel *currentTimeLabel;
    QLabel *totalTimeLabel;
    QLabel *volumeIcon;
    QLabel *volumeLabel;
    QLabel *bitRateLabel;
    QLabel *peersLabel;
    QSlider *sliderStartLoop;
    QSlider *sliderStopLoop;
    QSlider *slider;
    QProgressBar *progressBar;
    QTimer *loadingStateDelay;
    QTimer *hideControlsDelay;

    bool onSandbox, buffering, skip, paused, loop;
    int skip_key_value, volume, screenWidth, screenHeight;
    qint64 readyToRead_msec, update_msec, startLoop_msec, stopLoop_msec;

private slots:
    void play_pause_stop();
    void onBuffering();
    void set_loop();
    void slider_startLoop_pressed();
    void slider_startLoop_moved(int position);
    void slider_startLoop_released();
    void slider_stopLoop_pressed();
    void slider_stopLoop_moved(int position);
    void slider_stopLoop_released();
    void set_sliderLoop_time(int msec);
    void set_currentTime(qint64 msecs);
    void set_totalTime(qint64 msecs);
    void set_volume(int volume_key_value);
    void set_slider_position(qint64 position);
    void slider_pressed();
    void slider_moved(int position);
    void slider_released();
    void show_controls();
    void hide_controls();
    void status_change(QMediaPlayer::MediaStatus status);
    void error(QMediaPlayer::Error);
};

#endif
