#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>

class DataReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged FINAL)
public:
    explicit DataReceiver(QObject *parent = nullptr);
    Q_INVOKABLE double receiveData();

public slots:
    double rpm();

signals:
    void rpmChanged();

private:
    double m_rpm;
};

#endif // DATARECEIVER_H
