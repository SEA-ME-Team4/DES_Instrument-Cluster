import QtQuick 2.0
import Car2Qml 1.0

Rectangle {
    id: instrumentcluster
    color: "black"
    width: 1280
    height: 400

    property int timer_interval: 1000/120

    property int speed: 0
    property int battery: 0
    property int temp: 0
    property bool brake: false

    property bool speed_timeout: carinfo.speedstatus
    property bool battery_timeout: carinfo.batterystatus
    property bool temp_timeout: carinfo.tempstatus
    property bool brake_timeout: carinfo.brakestatus

    property bool dbus_timeout: carinfo.dbusstatus

    LeftCluster {
        x: 146
        y: 43
    }

    RightCluster {
        x: 774
        y: 43
    }

    GearSelection {
        x: 512
        y: 43
    }

    CenterCar {
        id: centerCar
        x: 430
        y: 54
    }

    StatusIndicator
    {
        x: 512
        y: 346
    }

    Car2Qml{
        id: carinfo

        onSpeedChanged: {instrumentcluster.speed = carinfo.speed}
        onBatteryChanged: {instrumentcluster.battery = carinfo.battery}
        onTempChanged: {instrumentcluster.temp = carinfo.temp}
        onBrakeChanged: {instrumentcluster.brake = carinfo.brake}

        onSpeedstatusChanged: {instrumentcluster.speed_timeout = status}
        onBatterystatusChanged: {instrumentcluster.battery_timeout = status}
        onTempstatusChanged: {instrumentcluster.temp_timeout = status}
        onBrakestatusChanged: {instrumentcluster.brake_timeout = status}

        onDbusstatusChanged: {instrumentcluster.dbus_timeout = status}

    }
}
