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

    property bool speed_timeout: true
    property bool battery_timeout: true
    property bool temp_timeout: true
    property bool brake_timeout: true

    function gui_update(){
        carinfo.updateVariables()

        instrumentcluster.speed = carinfo.speed
        instrumentcluster.battery = carinfo.battery
        instrumentcluster.temp = carinfo.temp
        instrumentcluster.brake = carinfo.brake
    }

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

    Timer {
        interval: instrumentcluster.timer_interval; running: true; repeat: true
        onTriggered: instrumentcluster.gui_update()
    }

    Car2Qml{
        id: carinfo
        onSpeedstatusChanged: {instrumentcluster.speed_timeout = status}
        onBatterystatusChanged: {instrumentcluster.battery_timeout = status}
        onTempstatusChanged: {instrumentcluster.temp_timeout = status}
        onBrakestatusChanged: {instrumentcluster.brake_timeout = status}
    }
}
