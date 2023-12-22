#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>

class DataReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString rpm READ rpm NOTIFY rpmChanged FINAL)
public:
    explicit DataReceiver(QObject *parent = nullptr);
    Q_INVOKABLE QString receiveData();

public slots:
    QString rpm();

signals:
    void rpmChanged();

private:
    QString m_rpm;
};

#endif // DATARECEIVER_H
