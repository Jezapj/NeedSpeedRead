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
            text: controller.title || "No document loaded yet i guess"
            font.pixelSize: 20
            color: "#ffffff"
        }

        Button {
            text: "Open Example File"
            onClicked: {
                controller.openFile("example.pdf")
            }
        }

        Rectangle {
            width: parent.width - 20
            height: parent.height - 20
            color: "#2fffff"
            radius: 16

            Text {
                anchors.centerIn: parent
                text: controller.content
                wrapMode: Text.Wrap
                color :"#000000"
            }
        }
    }
}
