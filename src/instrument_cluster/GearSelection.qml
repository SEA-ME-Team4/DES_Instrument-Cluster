import QtQuick 2.0

Rectangle {
    id: gearselection
    property color color: "#f7f2f2"
    property int update_interval: 100
    property double gearP: (parent.speed===0 && parent.brake)? 1 : 0.5
    property double gearR: (parent.speed<0)? 1 : 0.5
    property double gearN: (parent.speed===0 && !parent.brake)? 1 : 0.5
    property double gearD: (parent.speed>0)? 1 : 0.5

    Image {
        x: 0
        y: 0
        source: "images/top-line.png"
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        x: 0
        y: 0
        Text {
            x: 213
            y: 5
            color: gearselection.color
            text: "P"
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
            opacity: gearselection.gearP
            Behavior on opacity { NumberAnimation { duration: gearselection.update_interval} }
        }

        Text {
            x: 147
            y: 5
            color: gearselection.color
            text: "R"
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
            opacity: gearselection.gearR
            Behavior on opacity { NumberAnimation { duration: gearselection.update_interval} }
        }

        Text {
            x: 81
            y: 5
            color: gearselection.color
            text: "N"
            font.pixelSize: 45
            font.family: "Sarabun"
            font.bold: false
            opacity: gearselection.gearN
            Behavior on opacity { NumberAnimation { duration: gearselection.update_interval} }
        }

        Text {
            x: 15
            y: 5
            text: "D"
            color: gearselection.color
            font.pixelSize: 45
            font.bold: false
            font.family: "Sarabun"
            opacity: gearselection.gearD
            Behavior on opacity { NumberAnimation { duration: gearselection.update_interval} }
        }
    }
}
