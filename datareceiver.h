#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>

class DataReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float rps READ rps NOTIFY rpsChanged FINAL)
    Q_PROPERTY(double battery READ battery NOTIFY batteryChanged FINAL)
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged FINAL)
    Q_PROPERTY(QString indicator READ indicator NOTIFY indicatorChanged FINAL)
    Q_PROPERTY(QString themeColor READ themeColor NOTIFY themeColorChanged FINAL)
public:
    explicit DataReceiver(QObject *parent = nullptr);
    Q_INVOKABLE float receiveRPSData();
    Q_INVOKABLE double receiveBatteryData();
    Q_INVOKABLE QString receiveGearInformation();
    Q_INVOKABLE QString receiveIndicatorInformation();
    Q_INVOKABLE QString receiveThemeColorInformation();

public slots:
    float rps();
    double battery();
    QString gear();
    QString indicator();
    QString themeColor();

signals:
    void rpsChanged();
    void batteryChanged();
    void gearChanged();
    void indicatorChanged();
    void themeColorChanged();

private:
    float m_rps;
    double m_battery;
    QString m_gear;
    QString m_indicator;
    QString m_themeColor;
};

#endif // DATARECEIVER_H
