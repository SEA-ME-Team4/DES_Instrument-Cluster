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

    property bool speed_timeout: false
    property bool battery_timeout: false
    property bool temp_timeout: false
    property bool brake_timeout: false

    function gui_update(){
        carinfo.updateVariables()

        instrumentcluster.speed = carinfo.speed
        instrumentcluster.battery = carinfo.battery
        instrumentcluster.temp = carinfo.temp
        instrumentcluster.brake = carinfo.brake

        instrumentcluster.speed_timeout = carinfo.speedstatus
        instrumentcluster.battery_timeout = carinfo.batterystatus
        instrumentcluster.temp_timeout = carinfo.tempstatus
        instrumentcluster.brake_timeout = carinfo.brakestatus
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
    }
}
