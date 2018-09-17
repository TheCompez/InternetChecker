import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.11
import QtQuick.Extras 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    DynamicObject {
        id: dynamicObject
    }

    QtObject {
        id: objectTimer
        property bool isOnline: false
    }

    Timer {
        id: checkeTimer
        interval: 3000
        running: true
        repeat: true
        onTriggered: {
            Internet.checkInternet("http://google.com")
            objectTimer.isOnline = Internet.getStatus() ? true : false
            statusIndicator.color = objectTimer.isOnline ? "green" : "red"
            textStatus.text = objectTimer.isOnline ? "You are connected!" : "You are no connected!"
        }
    }

    Column {
        id: column
        anchors.centerIn: parent
        width: parent.width
        spacing: 5

        Image {
            id: modem
            source: objectTimer.isOnline ? dynamicObject.onlineModem : dynamicObject.offlineModem
            width: 96
            height: 96
            anchors.horizontalCenter: parent.horizontalCenter
            sourceSize.width: 256
            sourceSize.height: 256
            scale: 0.9
        }

        Text {
            id: textStatus
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "Please wait..."
        }

        StatusIndicator {
            width: 32
            height: 32
            id: statusIndicator
            active: true
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
}
