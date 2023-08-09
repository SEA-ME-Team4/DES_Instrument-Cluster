import QtQuick 2.0

Image {
    id: centercar
    x: 0
    y: 0
    fillMode: Image.PreserveAspectFit
    source: "images/field.png"

    property bool redlight: parent.brake
    property bool whitelight: (!redlight && (parent.speed!==0.0))

    Image {
        id: brakelight
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        source: "images/car-highlights.png"
        visible: centercar.redlight

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

    Rectangle {
        x: 137
        y: 142
        visible: centercar.whitelight
        Image {
            id: l_line1
            x: 0
            y: 0
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-left.png"
        }

        Image {
            id: r_line3
            x: 146
            y: 61
            source: "images/white-line-right.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: straight_arrow
            x: 63
            y: -63
            source: "images/arrow-0.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: r_line1
            x: 127
            y: 0
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-right.png"
        }

        Image {
            id: r_line2
            x: 108
            y: -57
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-right.png"
        }

        Image {
            id: l_line2
            x: 19
            y: -57
            fillMode: Image.PreserveAspectFit
            source: "images/white-line-left.png"
        }

        Image {
            id: l_line3
            x: -20
            y: 62
            source: "images/white-line-left.png"
            fillMode: Image.PreserveAspectFit
        }
    }
}
