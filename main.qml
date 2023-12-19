import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Extras 1.4

Window {
    width: 1280
    height: 400
    visible: true
    title: qsTr("Instrument Cluster")
    color: "black"

    Image {
        id: speedometer
        height: 380
        width: 380
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 70
        source: "qrc:/Images/speeedgauge.png"
        fillMode: Image.PreserveAspectCrop

        Rectangle {

        }

        Image {
            id: speedNeedle
            source: "qrc:/Images/needle.png"
            // height: parent.height / 2
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: 145
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: rpmGauge
        height: 380
        width: 380
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 70
        source: "qrc:/Images/rpmgauge.png"
        fillMode: Image.PreserveAspectCrop
    }

    CircularGauge {
        maximumValue: 220
        minimumValue: 0
        stepSize: 20
        tickmarksVisible: true
        value: 40
        anchors.centerIn: parent
        height: 360
        width: 360
    }
}
