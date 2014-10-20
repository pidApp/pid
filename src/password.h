#ifndef PASSWORD_H
#define PASSWORD_H

#include <QObject>
#include <QCryptographicHash>
#include <QString>

class Password : public QObject
{
    Q_OBJECT

public:
    explicit Password(QObject *parent = 0);
    ~Password();

    bool require();
    bool write(QString *plain);
    bool right(QString *plain);

private:
    QString pd;

private slots:
    const QString calculate(QString **plain);
};

#endif
