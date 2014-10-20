#include "pid.h"

#include <QTextStream>
#include <QDir>
#include <QFile>

PID::PID(QWidget *parent) : QWidget(parent), mRoot(0)
{
    mPassword = NULL;
    mUpdate = NULL;
    mTorrent = NULL;

    layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
}

PID::~PID()
{
    if (mPassword != NULL)
        delete mPassword;
    if (mUpdate != NULL)
        delete mUpdate;
    if (mTorrent != NULL)
        delete mTorrent;
    //cleanUp();
    mRoot->disconnect(this);
    exit(0);
}

void PID::set_root_object(QObject *root)
{
    if (mRoot != 0)
        mRoot->disconnect(this);
    mRoot = root;

    if (mRoot) connect (mRoot, SIGNAL(passwordHandleSIGNAL_QML(QString, bool, bool)), this, SLOT(password_handle(QString, bool, bool)));
    if (mRoot) connect (mRoot, SIGNAL(findSIGNAL_QML(QString, QString, QString, QString, QString, int, bool)), this, SLOT(find(QString, QString, QString, QString, QString, int, bool)));
    if (mRoot) connect (mRoot, SIGNAL(torrentHandleSIGNAL_QML(QString, int, int, bool)), this, SLOT(torrent_handle(QString, int, int, bool)));
    if (mRoot) connect (mRoot, SIGNAL(quitSIGNAL_QML()), this, SLOT(quit()));

#ifdef _WIN32
    const QString target = "C:/PID/.pid/db.sqlite";
    const QString tmp = "C:/PID/.pid/tmp/";
#else
    const QString target = QDir::homePath()+"/.pid/db.sqlite";
    const QString tmp = QDir::homePath()+"/.pid/tmp/";
#endif
    const QFile file(target);
    if (file.exists()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(target);
        const QDir dir(tmp);
        if (!dir.exists())
            dir.mkdir(tmp);

        mPassword = new Password();
        password_handle("", true, false);
    } else {
        QTimer::singleShot(10, this, SLOT(error_database()));
    }
}

//PASSWORD
void PID::password_handle(QString plain, bool init, bool write)
{
    if (!init && !write) {
        if (mPassword->right(&plain)) {
            mRoot->setProperty("require_password", false);
            update_handle();
        } else {
            mRoot->setProperty("fail_password", true);
        }
    } else if (init) {
        if (mPassword->require()) {
            mRoot->setProperty("require_password", true);
            init = false;
        } else {
            QTimer::singleShot(10, this, SLOT(update_handle()));
            init = false;
        }
    } else if (write) {
        if (mPassword->write(&plain)) {
            mRoot->setProperty("ok_password", true);
        } else {
            mRoot->setProperty("fail_password", true);
        }
    }
}

//UPDATE
void PID::update_handle()
{
    emit showUpdateSIGNAL();

    mUpdate = new Update();
    mUpdate->db = &db;
    mUpdate->_root = mRoot;
    mUpdate->check();

    connect (mUpdate, SIGNAL(forwardSIGNAL()), this, SLOT(start()));
    connect (mUpdate, SIGNAL(errorDatabaseSIGNAL()), this, SLOT(error_database()));
    connect (mRoot, SIGNAL(skipSIGNAL_QML()), this, SLOT(start()));
    connect (mRoot, SIGNAL(getFilesSIGNAL_QML()), mUpdate, SLOT(get_files()));
}

//START
void PID::start()
{
    delete mUpdate;
    mUpdate = NULL;

    if (db.open()) {
        QSqlQuery qry;
        qry.prepare("SELECT DatabaseVersion, BinaryVersion, Release, Category, NCategory, Director, NDirector FROM PidData, FiltersData");
        if (!qry.exec()) {
            db.close();
            error_database();
        } else {
            qry.next();
            const int currentDatabaseVersion = qry.value(0).toInt();
            const int currentBinaryVersion = qry.value(1).toInt();
            const int currentRelease = qry.value(2).toInt();
            QStringList categoryList = qry.value(3).toString().split(",");
            const QStringList numberCategoryList = qry.value(4).toString().split(",");
            QStringList directorList = qry.value(5).toString().split(",");
            const QStringList nDirectorListList = qry.value(6).toString().split(",");
            db.close();

            const QString strCurrentDatabaseVersion = QString::number(currentDatabaseVersion);
            const QString strCurrentBinaryVersion = QString::number(currentBinaryVersion);
            const QString strCurrentRelease= QString::number(currentRelease);

            categoryList.prepend(QString::number(categoryList.count()));
            directorList.prepend(QString::number(directorList.count()));

            mRoot->setProperty("databaseVersion", strCurrentDatabaseVersion);
            mRoot->setProperty("binaryVersion", strCurrentBinaryVersion);
            mRoot->setProperty("release", strCurrentRelease);
            mRoot->setProperty("categoryList", categoryList);
            mRoot->setProperty("numberCategoryList", numberCategoryList);
            mRoot->setProperty("directorList", directorList);
            mRoot->setProperty("nDirectorListList", nDirectorListList);

            mTorrent = new Torrent();
            mTorrent->_pid = this;
            mTorrent->_root = mRoot;
        }
    } else {
        error_database();
    }

#ifdef _WIN32
    const QString init = "C:/PID/.pid/.init";
    const QString target = "C:/PID/.pid/news.txt";
#else
    const QString init = QDir::homePath()+"/.pid/.init";
    const QString target = QDir::homePath()+"/.pid/news";
#endif
    QFile file(init);
    if (file.exists()) {
        file.remove();
        mRoot->setProperty("welcome", true);
    }
    file.setFileName(target);
    if (file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        bool head = true;
        QString binary_news;
        QString database_news;
        QTextStream in(&file);
        while (!in.atEnd()) {
            const QString line = in.readLine();
            if (line.isEmpty())
                head = false;
            if (head) {
                binary_news.append(line+"\n");
            } else {
                if(!line.isEmpty())
                    database_news.append(line+"\n");
            }
        }
        file.remove();

        mRoot->setProperty("binaryNews", binary_news);
        mRoot->setProperty("databaseNews", database_news);
        mRoot->setProperty("news", true);
    }

    emit startSIGNAL();
}

//FIND
void PID::find(QString input, QString director, QString category, QString quality, QString full, int offset, bool init)
{
    QStringList _list;
    int row = 0;

    if (!db.open()) {
        error_database();
    } else {
        _list.clear();
        const QString strOffset = QString::number(offset);
        QSqlQuery qry;
            qry.prepare("SELECT Title, Cas, Category, Quality, Full, UrlPoster, UrlCover, UrlScreens, Torrent, Fit FROM Films WHERE Title LIKE '%"+input+"%' AND Cas LIKE '%"+director+"%' AND Category LIKE '%"+category+"%' AND Quality LIKE '%"+quality+"%' AND Full LIKE '%"+full+"%' ORDER BY Title ASC LIMIT 1000 OFFSET '"+strOffset+"'");
        if (!qry.exec()) {
            db.close();
            error_database();
        } else {
            if (init) {
                qry.last();
                mRoot->setProperty("totalFilms", qry.at()+1);
                qry.first();
                qry.previous();
            }
            for (row=0; qry.next() && row<5; row++) {
                const QString _title = qry.value(0).toString();
                const QString _cast = qry.value(1).toString();
                const QString _category = qry.value(2).toString();
                const QString _quality = qry.value(3).toString();
                const QString _full = qry.value(4).toString();
                const QString _urlPoster = qry.value(5).toString();
                const QString _urlCover = qry.value(6).toString();
                const QString _urlScreens = qry.value(7).toString();
                const QString _torrent = qry.value(8).toString();
                const QString _fit = qry.value(9).toString();
                _list << _title << _cast << _category << _quality << _full << _urlPoster << _urlCover << _urlScreens << _torrent << _fit;
            }
            db.close();

            if (!qry.last() && init) {
                emit noResultSIGNAL();
            } else {
                if (init) {
                    mRoot->setProperty("n", row);
                    mRoot->setProperty("list", _list);
                    emit showOutputSIGNAL();
                } else {
                    mRoot->setProperty("n", row);
                    mRoot->setProperty("list", _list);
                    emit listUpdatedSIGNAL();
                }
            }
        }
    }
}

//TORRENT
void PID::torrent_handle(QString magnet, int scene, int fit, bool abort)
{
    //cleanUp();
    if (!abort) {
        mTorrent->scene = scene;
        mTorrent->fit = fit;
        mTorrent->doConnect(&magnet);
    } else {
        mTorrent->stop();
    }
}

//PLAYER
void PID::player_handle(const QString absoluteFilePath, bool init, bool sandbox, bool fileReady, bool abort)
{
    if (!abort) {
        if (init) {
            mPlayer = new VideoPlayer();
            mPlayer->_torrent = mTorrent;
            mPlayer->_pid = this;
            mTorrent->_player = mPlayer;
        }
        if (sandbox) {
            mPlayer->sandbox(&absoluteFilePath);
            emit checkingFileSIGNAL();
        }
        if (fileReady) {
            mTorrent->toPlayer = true;
            mPlayer->showFullScreen();
            this->hide();
            emit fileReadySIGNAL();
        }
    } else {
        this->show();
        emit abortTorrentSIGNAL();
        mPlayer->close();
        delete mPlayer;
    }
}

//CLEANUP
void PID::cleanUp()
{
    #ifdef _WIN32
        const QString target = "C:/PID/.pid/tmp/";
    #else
        const QString target = QDir::homePath()+"/.pid/tmp/";
    #endif
        QDir tmp(target);
        tmp.setFilter(QDir::NoDotAndDotDot | QDir::Files);
        foreach(QString tmpItem, tmp.entryList())
            tmp.remove(tmpItem);

        tmp.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
        foreach(QString tmpItem, tmp.entryList()) {
            QDir subDir(tmp.absoluteFilePath(tmpItem));
            subDir.removeRecursively();
        }
}

//ERROR_DB
void PID::error_database()
{
    emit showErrorDatabaseSIGNAL();
}

void PID::quit()
{
    this->~PID();
}
