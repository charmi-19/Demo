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
    title: "Instrument Cluster"


    Item {
        id: container
        width: 1280
        height: 400
        anchors.centerIn: parent
        rotation: -90

        Image {
            source: "qrc:/assets/image.png"
            anchors.fill: parent
        }

        //background of application
        Rectangle {
            anchors.fill: parent
            width: parent.width
            height: parent.height
            color: "black"
            RadialGradient {
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "gray" }
                    GradientStop { position: 0.05; color: "gray" }
                    GradientStop { position: 0.4; color: "transparent" }
                    GradientStop { position: 1.0; color: "black" }
                }
            }
        }

        // Speedometer
        CircularGauge {
            id:speedometer
            style: CircularGaugeStyle {
                background: Rectangle {
                    implicitHeight: speedometer.height
                    implicitWidth: speedometer.width
                    color: "#000"
                    radius: implicitWidth / 2
                    border.color: "#fff"
                    border.width: 2
                }
                foreground: Item {
                    clip: true
                    Rectangle {
                        width: 360 * 0.5
                        height: width
                        radius: width * 0.5
                        color: "black"
                        anchors.centerIn: parent
                        border.color: "#fff"
                        border.width: 3
                        anchors.bottomMargin: -border.width
                        Text {
                            id: speed
                            text: parseInt(Instrument_Cluster.rps * 3.14 * 2.5) // need to change
                            color: "#fff"
                            font.pointSize: 40
                            anchors.centerIn: parent
                        }
                        Text {
                            text: "cm/s"
                            color: "#fff"
                            font.pointSize: 14
                            anchors.top: speed.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }
            value: Instrument_Cluster.rps * 3.14 * 2.5
            stepSize: 0.5
            maximumValue: 100
            minimumValue: 0
            width: 370
            height: 370
            anchors.left: battery.right
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 15
        }

        Image {
            id: leftIndicator
            anchors {
                right: battery.left
                top: parent.top
                topMargin: 15
            }
            source: "qrc:/assets/left.svg"
            width: 40
            height: 40
            fillMode: Image.PreserveAspectFit
            opacity: 0.5
        }

        // Battery
        Rectangle{
            id: battery
            rotation: -90
            anchors.centerIn: parent
            width:280
            height:130
            color: "transparent"
            Rectangle {
                id: batteryfill
                anchors.bottom: parent.bottom
                width: Instrument_Cluster.battery * 2.6
                height: 120
                color: "green"
            }
            Image {
                width:320
                height:160
                anchors.centerIn: parent
                id: batteryImage
                source: "qrc:/assets/battery2.png"
            }
            Text {
                anchors.centerIn: batteryfill
                font.pixelSize: 24
                color: "white"
                text: Instrument_Cluster.battery + "%"
                rotation: -270
            }
        }

        Image {
            id: rightIndicator
            anchors {
                left: battery.right
                top: parent.top
                topMargin: 15
            }
            source: "qrc:/assets/right.svg"
            width: 40
            height: 40
            fillMode: Image.PreserveAspectFit
            rotation: 180
            opacity: 0.5
        }

        Timer {
            interval: 500
            running: true
            repeat: true
            onTriggered: {
                console.log("==================",Instrument_Cluster.indicator, "==================")
                if(Instrument_Cluster.indicator === "L") {
                    leftIndicator.visible = !leftIndicator.visible;
                    leftIndicator.opacity = 1;
                    rightIndicator.opacity = 0.5
                }
                else if(Instrument_Cluster.indicator === "R") {
                    rightIndicator.visible = !rightIndicator.visible;
                    rightIndicator.opacity = 1;
                    leftIndicator.opacity = 0.5;
                }
                else{
                    leftIndicator.visible = false;
                    leftIndicator.opacity = 0.5;
                    rightIndicator.visible = false;
                    rightIndicator.opacity = 0.5;
                }
            }

        }

        // RPS Guage
        CircularGauge {
            id:rpsguage
            property real rpsValue: Instrument_Cluster.rps
            NumberAnimation {
                id: rpsAnimation
                target: rpsguage
                property: "value"
                duration: 100
                easing.type: Easing.Linear
            }
            onRpsValueChanged: {
                rpsAnimation.from = rpsguage.value
                rpsAnimation.to = rpsValue
                rpsAnimation.start()
            }
            style: CircularGaugeStyle {
                background: Rectangle {
                    implicitHeight: speedometer.height
                    implicitWidth: speedometer.width
                    color: "#000"
                    radius: implicitWidth / 2
                    border.color: "#fff"
                    border.width: 2
                }
                foreground: Item {
                    Rectangle {
                        width: 360 * 0.5
                        height: width
                        radius: width * 0.5
                        color: "black"
                        anchors.centerIn: parent
                        border.color: "#fff"
                        border.width: 3
                        anchors.bottomMargin: -border.width
                        Text {
                            id: rps
                            text: Instrument_Cluster.gear // need to change
                            color: "#fff"
                            font.pointSize: 50
                            anchors.centerIn: parent
                        }
                    }
                }
                labelStepSize: 1
            }
            // value: Instrument_Cluster.rps
            maximumValue: 10
            stepSize: 0.5
            width: 370
            height: 370
            anchors.right: battery.left
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 15
        }
    }
}
