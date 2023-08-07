import QtQuick 2.12
import QtQuick.Window 2.12
//import testinfo 1.0

Window {
    id: instrumentcluster
    visible: true
    width: 1280
    height: 400
    color: "black"
    title: qsTr("Instrument Cluster")
//    property int speed: 100
//    property int battery_percentage: 100
    property color gearoff: "#808080"
    property color gearon: "#f7f2f2"
    property int y_offset: 16
    property int left_angle: -140
    property int right_angle: 180
    property int counter: 0
    //    carstatus = 0:accel / 1:brake / 2:stop
    property int carstatus: 0
    property bool redlight: true
    property bool whitelight: true

    //    GUI UPDATE (Need to be Modify)
    function gui_update(){
        //  counter (for test)
        instrumentcluster.counter++
        //  angle (example)
        instrumentcluster.left_angle++
        instrumentcluster.right_angle--
        //  Situation Control
        if (instrumentcluster.carstatus==0){
            instrumentcluster.redlight=false
            instrumentcluster.whitelight=true
        }
        else if(instrumentcluster.carstatus===1){
            instrumentcluster.redlight=true
            instrumentcluster.whitelight=false
        }
        else{
            instrumentcluster.redlight=false
            instrumentcluster.whitelight=false
        }

        //  Example for Test
        if (counter<=10){
            instrumentcluster.carstatus=0
        }
        else if (counter<=20){
            instrumentcluster.carstatus=1
        }
        else{
            instrumentcluster.carstatus=2
        }
        if (instrumentcluster.counter==30){
            instrumentcluster.counter = 0
        }

        if (instrumentcluster.left_angle==0) {instrumentcluster.left_angle=-140}
        if (instrumentcluster.right_angle==0) {instrumentcluster.right_angle=180}
    }

    Image {
        id: left_cluster
        x: 0
        y: 43
        fillMode: Image.PreserveAspectFit
        source: "images/left.png"

        Image {
            id: left_needle
            x: 152
            y: -16
            fillMode: Image.PreserveAspectFit
            source: "images/needle-standard-sport.png"
            transform: [
                Rotation {
                    origin.x: left_needle.width/2
                    origin.y: right_cluster.height/2 + y_offset
                    angle: instrumentcluster.left_angle
                }
            ]
        }
        Image {
            id: left_hightlight
            x: 120
            y: -16
            fillMode: Image.PreserveAspectFit
            source: "images/highlight-standard-sport.png"
            transform: [
                Rotation {
                    origin.x: left_hightlight.width/2
                    origin.y: left_cluster.height/2 + y_offset
                    angle: instrumentcluster.left_angle
                }
            ]
        }

        Text {
            x: 156
            y: 131
            color: "#f7f2f2"
            text: 140+instrumentcluster.left_angle
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
        }
        Text {
            x: 190
            y: 276
            color: "gray"
            text: "mm/s"
            font.pixelSize: 13
            font.family: "Sarabun"
            font.bold: false
        }
    }

    Image {
        id: right_cluster
        x: 920
        y: 43
        fillMode: Image.PreserveAspectFit
        source: "images/right.png"

        Image {
            id: right_needle
            x: 152
            y: -16
            fillMode: Image.PreserveAspectFit
            source: "images/needle-standard-sport.png"
            transform: [
                Rotation {
                    origin.x: right_needle.width/2
                    origin.y: right_cluster.height/2+y_offset
                    angle: instrumentcluster.right_angle
                }
            ]
        }

        Image {
            id: right_hightlight
            x: 120
            y: -16
            fillMode: Image.PreserveAspectFit
            source: "images/highlight-standard-sport.png"
            transform: [
                Rotation {
                    origin.x: right_hightlight.width/2
                    origin.y: right_cluster.height/2+y_offset
                    angle: instrumentcluster.right_angle
                }
            ]
        }

        Text {
            x: 123
            y: 131
            color: "#f7f2f2"
            text: Math.round((180-instrumentcluster.right_angle)/180*100)
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
        }

        Text {
            x: 133
            y: 276
            color: "#808080"
            text: "%"
            font.pixelSize: 13
            font.family: "Sarabun"
            font.bold: false
        }
    }

    Image {
        id: carimage
        x: 430
        y: 160
        fillMode: Image.PreserveAspectFit
        source: "images/field.png"
        Image {
            id: brakelight
            x: 0
            y: 0
            fillMode: Image.PreserveAspectFit
            source: "images/car-highlights.png"
            visible: instrumentcluster.redlight
            Image {
                id: brakelineL
                x: 116
                y: 40
                source: "images/red-border-left.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: brakelineR
                x: 235
                y: 40
                source: "images/red-border-right.png"
                fillMode: Image.PreserveAspectFit
            }
        }
        Image {
            id: l_line1
            x: 137
            y: 142
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-left.png"
            visible: instrumentcluster.whitelight
        }

        Image {
            id: r_line3
            x: 283
            y: 203
            source: "images/white-line-right.png"
            fillMode: Image.PreserveAspectFit
            visible: instrumentcluster.whitelight
        }

        Image {
            id: r_line1
            x: 264
            y: 142
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-right.png"
            visible: instrumentcluster.whitelight
        }

        Image {
            id: r_line2
            x: 245
            y: 85
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-right.png"
            visible: instrumentcluster.whitelight
        }

        Image {
            id: l_line2
            x: 156
            y: 85
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-left.png"
            visible: instrumentcluster.whitelight
        }

        Image {
            id: l_line3
            x: 117
            y: 204
            source: "images/white-line-left.png"
            fillMode: Image.PreserveAspectFit
            visible: instrumentcluster.whitelight
        }

    }

    Image {
        id: topline
        x: 512
        y: 43
        source: "images/top-line.png"
        fillMode: Image.PreserveAspectFit

        Text {
            x: 213
            y: 5
            color: instrumentcluster.gearoff
            text: "P"
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
        }

        Text {
            x: 147
            y: 5
            color: instrumentcluster.gearoff
            text: "R"
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
        }

        Text {
            x: 81
            y: 5
            color: instrumentcluster.gearoff
            text: "N"
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
        }

        Text {
            x: 15
            y: 5
            text: "D"
            color: instrumentcluster.gearon
            font.pixelSize: 45
            font.bold: false
            font.family: "Sarabun"
        }



    }

    Timer {
        interval: 50; running: true; repeat: true
        onTriggered: instrumentcluster.gui_update()
    }
}
