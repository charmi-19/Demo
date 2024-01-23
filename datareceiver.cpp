#include "datareceiver.h"
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusReply>
#include <QTimer>

DataReceiver::DataReceiver(QObject *parent)
    : QObject{parent}
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DataReceiver::receiveRPMData);
    timer->start(100);

    QTimer *timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &DataReceiver::receiveBatteryData);
    timer1->start(10000);
}

// Receiver function

float DataReceiver::receiveRPMData() {
    qDebug() << "Trying to connect D-Bus...";
    QDBusInterface dbusInterface("net.lew21.pydbus.ClientServerExample111", "/net/lew21/pydbus/ClientServerExample111", "net.lew21.pydbus.ClientServerExample111", QDBusConnection::sessionBus());

    // Show error if connection is failed
    if(!dbusInterface.isValid()) {
        qDebug() << "Failed to create DBusInterface ";
    }

    QDBusReply<QString> rpm = dbusInterface.call("RPM");

    if(!rpm.isValid()) {
        qWarning() << "Failed to call method for rps:" << rpm.error().message();
        qDebug() << "Error printing rpm";
    } else {
        m_rpm = rpm.value().toFloat();
        qDebug() << "RPS: " << rpm.value().toFloat();
    }

    emit rpmChanged();
    return rpm.value().toFloat();
}

double DataReceiver::receiveBatteryData() {
    qDebug() << "Trying to connect D-Bus for Battery...";
    QDBusInterface dbusInterface("com.dbus.batteryService", "/com/dbus/batteryService", "com.dbus.batteryService", QDBusConnection::sessionBus());

    // Show error if connection is failed
    if(!dbusInterface.isValid()) {
        qDebug() << "Failed to create DBusInterface ";
    }

    QDBusReply<QString> battery = dbusInterface.call("getBatteryLevel");

    if(!battery.isValid()) {
        qWarning() << "Failed to call method for battery:" << battery.error().message();
        qDebug() << "Error printing battery data";
    } else {
        m_battery = battery.value().toDouble();
        qDebug() << "Battery Data: " << battery.value();
    }

    emit batteryChanged();
    return battery.value().toDouble();
}

float DataReceiver::rpm()
{
    return m_rpm;
}

double DataReceiver::battery()
{
    return m_battery;
}
