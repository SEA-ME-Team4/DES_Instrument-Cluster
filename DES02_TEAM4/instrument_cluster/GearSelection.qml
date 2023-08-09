import QtQuick 2.0

Rectangle {
    Image {
        x: 0
        y: 0
        source: "images/top-line.png"
        fillMode: Image.PreserveAspectFit
    }
    Text {
        x: 213
        y: 5
        color: instrumentcluster.gearP
        text: "P"
        font.pixelSize: 45
        font.family: "Sarabun"
        font.bold: false
    }

    Text {
        x: 147
        y: 5
        color: instrumentcluster.gearR
        text: "R"
        font.pixelSize: 45
        font.family: "Sarabun"
        font.bold: false
    }

    Text {
        x: 81
        y: 5
        color: instrumentcluster.gearN
        text: "N"
        font.pixelSize: 45
        font.family: "Sarabun"
        font.bold: false
    }

    Text {
        x: 15
        y: 5
        text: "D"
        color: instrumentcluster.gearD
        font.pixelSize: 45
        font.bold: false
        font.family: "Sarabun"
    }

}
