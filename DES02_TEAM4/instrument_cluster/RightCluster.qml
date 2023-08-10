import QtQuick 2.0

Rectangle {
    id: rightcluster
    color: "black"

    property int update_interval: 100
    property color textcolor: "#f7f2f2"
    property int y_offset: 16
    property int right_angle_offset: 180
    property int right_angle: -Math.round((parent.battery/100)*180)+right_angle_offset

    Rectangle {
        x: 0
        y: 0

        Text {
            x: 301
            y: 195
            color: "white"
            text: "40"
            font.bold: false
            font.family: "Sarabun"
            font.pixelSize: 13
        }

        Text {
            x: 253
            y: 37
            color: "white"
            text: "80"
            font.bold: false
            font.family: "Sarabun"
            font.pixelSize: 13
        }

        Text {
            x: 252
            y: 261
            color: "white"
            text: "20"
            font.bold: false
            font.family: "Sarabun"
            font.pixelSize: 13
        }


        Text {
            x: 301
            y: 106
            color: "white"
            text: "60"
            font.bold: false
            font.family: "Sarabun"
            font.pixelSize: 13
        }

        Text {
            x: 176
            y: 289
            color: "white"
            text: "0"
            font.bold: false
            font.family: "Sarabun"
            font.pixelSize: 13
        }


        Text {
            x: 168
            y: 9
            color: "white"
            text: "100"
            font.bold: false
            font.family: "Sarabun"
            font.pixelSize: 13
        }
    }

    Image {
        id: rightshadow
        x: -60
        y: -83
        width: 480
        height: 480
        source: "images/shadow.png"
        fillMode: Image.PreserveAspectFit
        transform: [
            Rotation {
                origin.x: rightshadow.width/2
                origin.y: rightshadow.height/2
                angle: rightcluster.right_angle
                Behavior on angle { RotationAnimation { duration: rightcluster.update_interval} }
            }
        ]
    }

    Image {
        id: rightneedle
        x: 152
        y: -16
        fillMode: Image.PreserveAspectFit
        source: "images/needle-standard-sport.png"
        transform: [
            Rotation {
                origin.x: rightneedle.width/2
                origin.y: rightcluster_image.height/2 + rightcluster.y_offset
                angle: rightcluster.right_angle
                Behavior on angle { RotationAnimation { duration: rightcluster.update_interval} }
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
                origin.y: rightcluster_image.height/2 + rightcluster.y_offset
                angle: rightcluster.right_angle
                Behavior on angle { RotationAnimation { duration: rightcluster.update_interval} }
            }
        ]
    }

    Text {
        x: 166
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

    Image {
        id: rightcluster_image
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        source: "images/right.png"
    }
}
