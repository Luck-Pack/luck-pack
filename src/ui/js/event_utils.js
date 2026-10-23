.pragma library

function canMoveUp(event, index, line) {
  return (event.key === Qt.Key_Up || event.key === Qt.Key_K || event.key === Qt.Key_W) && index - line >= 0;
}
function canMoveDown(event, index, line, limit) {
  return (event.key === Qt.Key_Down || event.key === Qt.Key_J || event.key === Qt.Key_S) && index + line < limit;
}
function canMoveLeft(event, index) {
  return (event.key === Qt.Key_Left || event.key === Qt.Key_A || event.key === Qt.Key_H) && index - 1 >= 0;
}
function canMoveRight(event, index, limit) {
  return (event.key === Qt.Key_Right || event.key === Qt.Key_D || event.key === Qt.Key_L) && index + 1 < limit;
}