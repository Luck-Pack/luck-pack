pragma ComponentBehavior: Bound
import QtQuick
import LuckPack
import "../js/event_utils.js" as EventUtils

GridModelView {
  id: root
  function fieldByCount(c, big, middle, small) {
    if (c <= 5) return big;
    if (c <= 10) return middle;
    return small;
  }

  gridModel: SectionModel.currentSection?.nodes ?? []
  count: gridModel?.length ?? 0

  columns:    count <= 5 ? Math.max(1, count) : 5
  itemWidth:  fieldByCount(count, 200, 175, 150)
  itemHeight: fieldByCount(count, 200, 150, 100)
  fontSize:   fieldByCount(count, 20, 18, 16)
  spacing:    fieldByCount(count, 20, 16, 12)
  itemColor:  SectionModel.currentSection?.isLeafSection ? "#C05454" : "#4B4263"
  caretIndex: 0

  onItemSelected: (index, node) => SectionModel.currentSection?.openNode(index);
  onCountChanged: () => caretIndex = 0;

  contentDelegate: Component {
    Item {
      id: nodeType
      anchors.fill: parent
      visible: SectionModel.currentSection?.isLeafSection

      property var modelItem: null

      Rectangle {
        anchors {
          bottom: parent.bottom
          right: parent.right

          bottomMargin: 10
          rightMargin: 15
        }

        width: typeText.implicitWidth + 10
        height: typeText.implicitHeight + 4
        color: "#FFCC00"
        radius: 3

        Text {
          id: typeText
          anchors.centerIn: parent
          font.pixelSize: Math.floor(root.fontSize / 1.5)
          font.bold: Font.Bold
          text: nodeType.modelItem?.extension
        }
      }
    }
  }

  Keys.onPressed: (event) => {
    if      (EventUtils.canMoveUp(event, caretIndex, columns)) { caretIndex -= columns; event.accepted = true; }
    else if (EventUtils.canMoveDown(event, caretIndex, columns, count)) { caretIndex += columns; event.accepted = true; }
    else if (EventUtils.canMoveLeft(event, caretIndex)) { --caretIndex; event.accepted = true; }
    else if (EventUtils.canMoveRight(event, caretIndex, count)) { ++caretIndex; event.accepted = true; }

    if (event.key === Qt.Key_Return || event.key === Qt.Key_E) {
      if (gridModel) {
        itemSelected(caretIndex, gridModel[caretIndex]);
        event.accepted = true;
      }
    }
  }
}