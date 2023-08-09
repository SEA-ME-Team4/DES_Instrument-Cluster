import QtQuick 2.0

Image {
    id: leftcluster
    x: 0
    y: 0
    fillMode: Image.PreserveAspectFit
    source: "images/left.png"

    property color textcolor: "#f7f2f2"
    property int y_offset: 16
    property int left_angle_offset: -140
    property int left_angle: parent.speed + left_angle_offset


    Image {
        id: leftneedle
        x: 152
        y: -16
        fillMode: Image.PreserveAspectFit
        source: "images/needle-standard-sport.png"
        transform: [
            Rotation {
                origin.x: leftneedle.width/2
                origin.y: leftcluster.height/2 + leftcluster.y_offset
                angle: leftcluster.left_angle
            }
        ]
    }
    Image {
        id: lefthightlight
        x: 120
        y: -16
        fillMode: Image.PreserveAspectFit
        source: "images/highlight-standard-sport.png"
        transform: [
            Rotation {
                origin.x: lefthightlight.width/2
                origin.y: leftcluster.height/2 + leftcluster.y_offset
                angle: leftcluster.left_angle
            }
        ]
    }

    Text {
        x: 10  //156
        y: 131  //131
        color: leftcluster.textcolor
        text: parent.parent.speed
        font.pixelSize: 45
        font.family: "Sarabun"
        font.bold: false
        width: leftcluster.width
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
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
