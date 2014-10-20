#ifndef PID_H
#define PID_H

#include "password.h"
#include "update.h"
#include "torrent.h"
#include "videoplayer.h"

#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QtSql>
#include <QKeyEvent>
#include <QVBoxLayout>

class PID : public QWidget
{
    Q_OBJECT

public:
    PID(QWidget *parent=0);
    ~PID();

    Q_INVOKABLE void player_handle(const QString absoluteFilePath, bool init, bool sandbox, bool fileReady, bool abort);
    Q_INVOKABLE void quit();

    QWidget *container;
    QVBoxLayout *layout;

public slots:
    void set_root_object(QObject *root);

signals:
    void showUpdateSIGNAL();
    void startSIGNAL();
    void showOutputSIGNAL();
    void listUpdatedSIGNAL();
    void noResultSIGNAL();
    void abortTorrentSIGNAL();
    void checkingFileSIGNAL();
    void fileReadySIGNAL();
    void showErrorDatabaseSIGNAL();

private:
    QObject *mRoot;
    Password *mPassword;
    Update *mUpdate;
    Torrent *mTorrent;
    VideoPlayer *mPlayer;

    QSqlDatabase db;

private slots:
    void password_handle(QString pass, bool init, bool write);
    void update_handle();
    void start();
    void find(QString inputText, QString director, QString category, QString quality, QString full, int offset, bool init);
    void torrent_handle(QString magnet, int scene, int fit, bool abort);
    void cleanUp();
    void error_database();
};

#endif
