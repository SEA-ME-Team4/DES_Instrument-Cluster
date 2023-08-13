import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: statusindicator
    property color dbusstatuscolor: (!parent.dbus_timeout)? "#FFFFFF" : "#ff0000"
    property double speedopacity: (!parent.speed_timeout || parent.dbus_timeout)? 0.7 : 0.3
    property double brakeopacity: (!parent.brake_timeout || parent.dbus_timeout)? 0.7 : 0.3
    property double batteryopacity: (!parent.battery_timeout || parent.dbus_timeout)? 0.7 : 0.3
    property double tempopacity: (!parent.temp_timeout || parent.dbus_timeout)? 0.7 : 0.3
    color: "black"

    Image {
    source: "images/top-line.png"
    fillMode: Image.PreserveAspectFit

    }

    Image {
        id: speedstatusimage
        x: 0
        y: 12
        source: "images/speedstatus.png"
        fillMode: Image.PreserveAspectFit
        ColorOverlay {
            anchors.fill : speedstatusimage
            source: speedstatusimage
            color: statusindicator.dbusstatuscolor
            opacity: 1
        }
        opacity: statusindicator.speedopacity
    }

    Image {
        id: brakestatusimage
        x: 75
        y: 12
        source: "images/brakestatus.png"
        fillMode: Image.PreserveAspectFit
        ColorOverlay {
            anchors.fill : brakestatusimage
            source: brakestatusimage
            color: statusindicator.dbusstatuscolor
            opacity: 1
        }
        opacity: statusindicator.brakeopacity
    }

    Image {
        id: batterystatusimage
        x: 146
        y: 12
        source: "images/batterystatus.png"
        fillMode: Image.PreserveAspectFit
        ColorOverlay {
            anchors.fill : batterystatusimage
            source: batterystatusimage
            color: statusindicator.dbusstatuscolor
            opacity: 1
        }
        opacity: statusindicator.batteryopacity
    }

    Image {
        id: tempstatusimage
        x: 224
        y: 12
        source: "images/tempstatus.png"
        fillMode: Image.PreserveAspectFit
        ColorOverlay {
            anchors.fill : tempstatusimage
            source: tempstatusimage
            color: statusindicator.dbusstatuscolor
            opacity: 1
        }
        opacity: statusindicator.tempopacity
    }

}
