#include "password.h"

#include <QTextStream>
#include <QDir>
#include <QFile>

Password::Password(QObject *parent) : QObject(parent)
{
}

Password::~Password()
{
}

bool Password::require()
{
    #ifdef _WIN32
        QFile file("C:/PID/.pid/pd.txt");
    #else
        QFile file(QDir::homePath()+"/.pid/.pd");
    #endif
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        while (!file.atEnd()) {
            const QByteArray line = file.readLine();
            pd = QString(line).toUtf8();
            if (pd != "") {
                file.close();
                return true;
                break;
            }
        }
    }
    return false;
}

bool Password::write(QString *plain)
{
    const QString digest = calculate(&plain);

    #ifdef _WIN32
        QFile file("C:/PID/.pid/pd.txt");
    #else
        QFile file(QDir::homePath()+"/.pid/.pd");
    #endif
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream write(&file);
        write << digest;
        file.close();
        return true;
    }
    return false;
}

bool Password::right(QString *plain)
{
    const QString digest = calculate(&plain);
    if (digest == pd)
        return true;
    else
        return false;
}

const QString Password::calculate(QString **plain)
{
    const QByteArray _plain = QString(**plain).toUtf8();
    const QString digest = QString(QCryptographicHash::hash(_plain,QCryptographicHash::Md5).toHex());
    return digest;
}
