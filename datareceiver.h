#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>

class DataReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged FINAL)
    Q_PROPERTY(double battery READ battery NOTIFY batteryChanged FINAL)
public:
    explicit DataReceiver(QObject *parent = nullptr);
    Q_INVOKABLE double receiveRPMData();
    Q_INVOKABLE double receiveBatteryData();

public slots:
    double rpm();
    double battery();

signals:
    void rpmChanged();
    void batteryChanged();

private:
    double m_rpm;
    double m_battery;
};

#endif // DATARECEIVER_H
