import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    Material.theme: Material.Dark
    Material.accent: Material.Indigo

    width: 800
    height: 600
    visible: true
    title: "NeedSpeedRead"

    Column {
        anchors.fill: parent
        spacing: 12
        padding: 12

        Text {
            text: controller.title || "A Speed Reading Tool"
            font.pixelSize: 20
            color: "#ffffff"
        }

        Row {
            spacing: 8
            width: parent.width - 24

            TextField {
                id: filePathField
                placeholderText: "Enter file path..."
                width: parent.width - openButton.width - 8
                color: "#ffffff"
            }

            Button {
                id: openButton
                text: "Open File"
                onClicked: {
                    if (filePathField.text.length > 0) {
                        controller.openFile(filePathField.text)
                    }
                }
            }
        }

        Rectangle {
            width: parent.width - 24
            height: parent.height - 125
            color: "#4e0244"
            radius: 16

            Text {
                anchors.centerIn: parent
                text: controller.content
                height: 400
                font.pixelSize: 120
                wrapMode: Text.Wrap
                color: "#000000"
            }
        }
    }
}