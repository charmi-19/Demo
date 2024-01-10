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
    timer->start(1000);
}

// Receiver function

double DataReceiver::receiveRPMData() {
    qDebug() << "Trying to connect D-Bus...";
    QDBusInterface dbusInterface("net.lew21.pydbus.ClientServerExample111", "/net/lew21/pydbus/ClientServerExample111", "net.lew21.pydbus.ClientServerExample111", QDBusConnection::sessionBus());

    // Show error if connection is failed
    if(!dbusInterface.isValid()) {
        qDebug() << "Failed to create DBusInterface ";
    }

    QDBusReply<QString> rpm = dbusInterface.call("RPM");

    if(!rpm.isValid()) {
        qWarning() << "Failed to call method:" << rpm.error().message();
        qDebug() << "Error printing rpm";
    } else {
        m_rpm = rpm.value().toDouble();
        qDebug() << "RPM: " << rpm.value().toDouble();
    }

    emit rpmChanged();
    return rpm.value().toDouble();
}

double DataReceiver::receiveBatteryData() {
    qDebug() << "Trying to connect D-Bus...";
    QDBusInterface dbusInterface("com.dbus.batteryService", "/com/dbus/batteryService", "com.dbus.batteryService", QDBusConnection::sessionBus());

    // Show error if connection is failed
    if(!dbusInterface.isValid()) {
        qDebug() << "Failed to create DBusInterface ";
    }

    QDBusReply<QString> battery = dbusInterface.call("getBatteryLevel");

    if(!battery.isValid()) {
        qWarning() << "Failed to call method:" << battery.error().message();
        qDebug() << "Error printing battery data";
    } else {
        m_battery = battery.value().toDouble();
        qDebug() << "Battery Data: " << battery.value();
    }

    emit batteryChanged();
    return battery.value().toDouble();
}

double DataReceiver::rpm()
{
    return m_rpm;
}

double DataReceiver::battery()
{
    return m_battery;
}
