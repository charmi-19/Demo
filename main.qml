import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
Window {
    id:root
    width: 400
    height: 1280
    visible: true
    title: "INSTRUMENT CLUSTER"


    Item {
        id: container
        width: 1280
        height: 400
        anchors.centerIn: parent
        rotation: -90


        //background of application

        Rectangle {
            width: parent.width
            height: parent.height

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#000080" } // Dark Blue
                GradientStop { position: 1.0; color: "#000000" } // Black
            }

        }

        CircularGauge {
            id:speedometer
            style: CircularGaugeStyle {
                needle: Rectangle {
                    y: outerRadius * 0.15
                    implicitWidth: outerRadius * 0.03
                    implicitHeight: outerRadius * 0.9
                    antialiasing: true
                    color: "white"
                }
            }
            value: 50
            maximumValue: 150
            width: 250
            height: 250
            anchors.centerIn: parent
        }

        CircularGauge {
            id:battery
            style: CircularGaugeStyle {
                needle: Rectangle {
                    y: outerRadius * 0.15
                    implicitWidth: outerRadius * 0.03
                    implicitHeight: outerRadius * 0.9
                    antialiasing: true
                    color: "white"
                }
            }
            value: 50
            maximumValue: 150
            width: 250
            height: 250
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 200
        }

        CircularGauge {
            id:rpmgauge
            style: CircularGaugeStyle {
                needle: Rectangle {
                    y: outerRadius * 0.15
                    implicitWidth: outerRadius * 0.03
                    implicitHeight: outerRadius * 0.9
                    antialiasing: true
                    color: "white"
                }
                labelStepSize: 10
                labelInset: outerRadius / 2.2
                tickmarkInset: outerRadius / 4.2
                minorTickmarkInset: outerRadius / 4.2
                minimumValueAngle: -144
                maximumValueAngle: 144
            }
            value: 50
            maximumValue: 50
            width: 250
            height: 250
            anchors.left:parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 200
        }
    }
}
