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
    QDBusInterface dbusInterface("net.lew21.pydbus.ClientServerExample11", "/net/lew21/pydbus/ClientServerExample11", "net.lew21.pydbus.ClientServerExample11", QDBusConnection::sessionBus());

    // Show error if connection is failed
    if(!dbusInterface.isValid()) {
        qDebug() << "Failed to create DBusInterface ";
    }

    QDBusReply<double> rpm = dbusInterface.call("RPM");

    if(!rpm.isValid()) {
        qWarning() << "Failed to call method:" << rpm.error().message();
        qDebug() << "Error printing random number";
    } else {
        m_rpm = rpm.value();
        qDebug() << "Output: " << rpm.value();
    }

    emit rpmChanged();
    return rpm.value();
}

double DataReceiver::rpm()
{
    return m_rpm;
}
