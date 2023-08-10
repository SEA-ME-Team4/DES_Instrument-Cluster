import QtQuick 2.0

Rectangle{
    id: statusindicator
    width: 176
    height: 20
    color: "black"
    property double speedopacity: (!parent.speed_timeout)? 1 : 0.5
    property double batteryopacity: (!parent.battery_timeout)? 1 : 0.5
    property double tempopacity: (!parent.temp_timeout)? 1 : 0.5
    property double brakeopacity: (!parent.brake_timeout)? 1 : 0.5
    Image {
        id: image
        x: 0
        y: 0
        source: "images/battery.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.speedopacity
    }

    Image {
        id: image2
        x: 52
        y: 0
        source: "images/battery.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.batteryopacity
    }

    Image {
        id: image6
        x: 104
        y: 0
        source: "images/battery.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.tempopacity
    }

    Image {
        id: image7
        x: 156
        y: 0
        source: "images/battery.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.brakeopacity
    }
}
