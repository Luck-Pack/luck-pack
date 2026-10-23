pragma ComponentBehavior: Bound
import QtQuick
import LuckPack
import "../js/event_utils.js" as EventUtils

GridModelView {
  id: root
  gridModel: BreadcrumbsModel.breadcrumbs
  count: gridModel?.length ?? 0

  columns: count
  itemWidth: 180
  itemHeight: 40
  fontSize: 16
  spacing: 6
  itemColor: "#4B4263"
  caretIndex: 0

  onItemSelected: (index, section) => {
    SectionModel.setCurrentSection(section);
    BreadcrumbsModel.rewindToSection(section);
  }

  onCountChanged: () => caretIndex = count - 1;

  Keys.onPressed: (event) => {
    if (EventUtils.canMoveLeft(event, caretIndex)) { --caretIndex; event.accepted = true; }
    else if (EventUtils.canMoveRight(event, caretIndex, count)) { ++caretIndex; event.accepted = true; }

    if (event.key === Qt.Key_Return || event.key === Qt.Key_E) {
      if (gridModel) {
        itemSelected(caretIndex, gridModel[caretIndex]);
        event.accepted = true;
      }
    }
  }
}