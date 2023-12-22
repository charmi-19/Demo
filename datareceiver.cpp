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
    connect(timer, &QTimer::timeout, this, &DataReceiver::receiveData);
    timer->start(1000);
}

// Receiver function

double DataReceiver::receiveData() {
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
        qDebug() << "Output: " << rpm.value().toDouble();
    }

    emit rpmChanged();
    return rpm.value().toDouble();
}

double DataReceiver::rpm()
{
    return m_rpm;
}
