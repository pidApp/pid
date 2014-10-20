#include "tcpSocket.h"

#include <QDataStream>
#include <QDir>
#include <QFile>

TcpSocket::TcpSocket(QTcpSocket *parent) : QTcpSocket(parent)
{
    connect (this, SIGNAL(connected()), this, SLOT(connected()));
    connect (this, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect (this, SIGNAL(readyRead()), this, SLOT(ready_to_read()));
}

TcpSocket::~TcpSocket()
{
    this->abort();
}

void TcpSocket::doConnect()
{
    data.clear();
    this->connectToHost(host, 80);

    timeOut = new QTimer(this);
    timeOut->setSingleShot(true);
    connect (timeOut, SIGNAL(timeout()), this, SLOT(error()));
    timeOut->start(25000);
}

void TcpSocket::connected()
{
    const QString get = "GET "+url+" HTTP/1.1\r\nConnection: Close\r\nHost: "+host+"\r\n\r\n\r\n";
    const QByteArray ba = get.toUtf8();
    const char *request = ba.constData(); 
    this->writeData(request, ba.size());
}

void TcpSocket::disconnected()
{
    write();
}

void TcpSocket::ready_to_read()
{
    timeOut->stop();
    
    while (!this->atEnd())
        data.append(this->read(100));
}

void TcpSocket::write()
{    
#ifdef _WIN32
    const QString path = "C:/PID/.pid/tmp/";
#else
    const QString path = QDir::homePath()+"/.pid/tmp/";
#endif
    bool endHeader = false;
    QByteArray startPayload;
    const QDataStream in(data);
    while (!in.atEnd()) {
        const QByteArray line = in.device()->readLine();
        if (endHeader) {
            startPayload = line;
            break;
        }
        if (line.toHex() == "0d0a")
            endHeader = true;
    }
    const int header = data.indexOf(startPayload);
    data.remove(0, header);

    if (order == "getVersion") {
        const QByteArray dataFromBase = QByteArray::fromBase64(data);
        const QString version(dataFromBase);
        emit version_ready(version);
    } else {
        QFile target(path+file);
        target.open(QIODevice::WriteOnly);
        if (file == "news.txt") {
            const QByteArray dataFromBase = QByteArray::fromBase64(data);
            target.write(dataFromBase);
        } else {
            target.write(data);
        }
        target.close();
        emit file_ready(path, file);
    }
}

void TcpSocket::error()
{
    emit error_socket();
}
