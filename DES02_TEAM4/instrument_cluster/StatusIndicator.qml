import QtQuick 2.0


Rectangle {
    id: statusindicator
    property double speedopacity: (!(parent.speed_timeout))? 1 : 0.5
    property double batteryopacity: (!parent.battery_timeout)? 1 : 0.5
    property double tempopacity: (!parent.temp_timeout)? 1 : 0.5
    property double brakeopacity: (!parent.brake_timeout)? 1 : 0.5
    color: "black"

    Image {
    source: "images/top-line.png"
    fillMode: Image.PreserveAspectFit

    }
    Image {
        id: image
        x: 0
        y: 12
        source: "images/speedstatus.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.speedopacity
    }

    Image {
        id: image2
        x: 146
        y: 12
        source: "images/batterystatus.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.batteryopacity
    }

    Image {
        id: image6
        x: 224
        y: 12
        source: "images/tempstatus.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.tempopacity
    }

    Image {
        id: image7
        x: 75
        y: 12
        source: "images/brakestatus.png"
        fillMode: Image.PreserveAspectFit
        opacity: statusindicator.brakeopacity
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
