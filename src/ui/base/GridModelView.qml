pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts

Item {
  id: root
  property var gridModel
  property int count
  property int columns: 0
  property int itemWidth: 0
  property int itemHeight: 0
  property int fontSize: 0
  property int spacing: 0
  property color itemColor
  property int caretIndex: 0
  property Component contentDelegate: null

  implicitWidth: grid.implicitWidth
  implicitHeight: grid.implicitHeight

  signal itemSelected(int index, var item)

  Rectangle {
    id: caret
    z: 10

    x: (root.caretIndex % root.columns) * (root.itemWidth + root.spacing)
    y: Math.floor(root.caretIndex / root.columns) * (root.itemHeight + root.spacing)
    width: root.itemWidth
    height: root.itemHeight

    color: "transparent"
    border.color: "#8F8A9D"
    border.width: 2
    radius: 10
    visible: true

    Behavior on x { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
    Behavior on y { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
    Behavior on width { NumberAnimation { duration: 150 } }
    Behavior on height { NumberAnimation { duration: 150 } }
  }

  GridLayout {
    id: grid
    anchors.centerIn: parent
    columns: root.columns
    columnSpacing: root.spacing
    rowSpacing: columnSpacing

    Repeater {
      model: root.gridModel

      delegate: Rectangle {
        id: itemDelegate
        implicitWidth: root.itemWidth
        implicitHeight: root.itemHeight
        color: root.itemColor
        radius: root.itemHeight > 40 ? 10 : 6

        required property int index
        required property var modelData

        Text {
          anchors.fill: parent
          text: itemDelegate.modelData ? itemDelegate.modelData.title : ""
          color: "white"
          font.pixelSize: root.fontSize
          wrapMode: Text.WordWrap
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
        }

        Loader {
          id: loader
          anchors.fill: parent
          sourceComponent: root.contentDelegate

          Binding {
            target: loader.item
            property: "modelItem"
            value: itemDelegate.modelData
          }
        }

        TapHandler {
          onTapped: {
            if (itemDelegate.modelData) {
              root.itemSelected(itemDelegate.index, itemDelegate.modelData)
            }
          }
        }
      }
    }
  }
}