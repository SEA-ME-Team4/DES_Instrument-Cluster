import QtQuick 2.0

Rectangle {
    id: statusindicator
    property double dbusopacity: (parent.dbus_timeout)? 1 : 0
    property double speedopacity: (!parent.speed_timeout || parent.dbus_timeout)? 1 : 0.3
    property double brakeopacity: (!parent.brake_timeout || parent.dbus_timeout)? 1 : 0.3
    property double batteryopacity: (!parent.battery_timeout || parent.dbus_timeout)? 1 : 0.3
    property double tempopacity: (!parent.temp_timeout || parent.dbus_timeout)? 1 : 0.3
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
        opacity: statusindicator.speedopacity
    }

    Image {
        id: speedstatusimage_dbuscheck
        x: 0
        y: 12
        source: "images/speedometercheck.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.dbusopacity
    }

    Image {
        id: brakestatusimage
        x: 75
        y: 12
        source: "images/brakestatus.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.brakeopacity
    }

    Image {
        id: brakestatusimage_dbuscheck
        x: 75
        y: 12
        source: "images/brakecheck.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.dbusopacity
    }

    Image {
        id: batterystatusimage
        x: 146
        y: 12
        source: "images/batterystatus.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.batteryopacity
    }

    Image {
        id: batterystatusimage_dbuscheck
        x: 146
        y: 12
        source: "images/batterycheck.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.dbusopacity
    }

    Image {
        id: tempstatusimage
        x: 224
        y: 12
        source: "images/tempstatus.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.tempopacity
    }

    Image {
        id: tempstatusimage_dbuscheck
        x: 224
        y: 12
        source: "images/temperaturecheck.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.dbusopacity
    }
}
