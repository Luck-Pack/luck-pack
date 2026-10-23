import QtQuick
import LuckPack

Window {
  id: window
  visible: true
  width: 1280
  height: 720
  title: qsTr("Luck Pack")
  color: "#615978"

  FocusScope {
    id: viewScope
    anchors.fill: parent

    focus: true
    Component.onCompleted: forceActiveFocus()

    Connections {
      target: SectionModel.currentSection

      function onOpenNextSectionRequested(currentSection, node) {
        FileRepository.openNextSection(currentSection, node);
      }

      function onSetCurrentSectionRequested(section) {
        SectionModel.setCurrentSection(section);
        BreadcrumbsModel.appendSection(section);
      }
    }

    Connections {
      target: FileRepository

      function onRootSectionChanged(section) {
        SectionModel.setCurrentSection(section);
        BreadcrumbsModel.appendSection(section);
      }
    }

    property bool isShift: false

    Keys.onPressed: (event) => {
      let shiftActive = ((event.modifiers & Qt.ShiftModifier) !== 0) || (event.key === Qt.Key_Shift);

      isShift = shiftActive;
    }

    Keys.onReleased: (event) => {
      if (event.key === Qt.Key_Shift) {
        isShift = false;
        event.accepted = true;
      }
    }

    BreadcrumbsView {
      anchors {
        top: parent.top
        horizontalCenter: parent.horizontalCenter
        topMargin: 50
      }
      focus: viewScope.isShift
    }

    SectionView {
      anchors {
        top: parent.top
        horizontalCenter: parent.horizontalCenter
        topMargin: 150
      }
      focus: !viewScope.isShift
    }
  }
}