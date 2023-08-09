import QtQuick 2.0

Image {
    id: rightcluster
    x: 0
    y: 0
    fillMode: Image.PreserveAspectFit
    source: "images/right.png"

    property color textcolor: "#f7f2f2"
    property int y_offset: 16
    property int right_angle_offset: 180
    property int right_angle: -Math.round((parent.battery/100)*180)+right_angle_offset

    Image {
        id: rightneedle
        x: 152
        y: -16
        fillMode: Image.PreserveAspectFit
        source: "images/needle-standard-sport.png"
        transform: [
            Rotation {
                origin.x: rightneedle.width/2
                origin.y: rightcluster.height/2 + rightcluster.y_offset
                angle: rightcluster.right_angle
            }
        ]
    }

    Image {
        id: righthightlight
        x: 120
        y: -16
        fillMode: Image.PreserveAspectFit
        source: "images/highlight-standard-sport.png"
        transform: [
            Rotation {
                origin.x: righthightlight.width/2
                origin.y: rightcluster.height/2 + rightcluster.y_offset
                angle: rightcluster.right_angle
            }
        ]
    }

    Text {
        x: 10
        y: 131
        color: rightcluster.textcolor
        text: parent.parent.battery
        font.pixelSize: 45
        font.family: "Sarabun"
        font.bold: false
        width: rightcluster.width
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
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
