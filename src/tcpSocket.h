#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    explicit TcpSocket(QTcpSocket *parent = 0);
    ~TcpSocket();

    QString host;
    QString url;
    QString file;
    QString order;

public slots:
    void doConnect();

signals:
    void version_ready(const QString version);
    void file_ready(QString path, QString file);
    void error_socket();

private:
    QByteArray data;
    QTimer *timeOut;

private slots:
    void connected();
    void disconnected();
    void ready_to_read();
    void write();
    void error();
};

#endif
