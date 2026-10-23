#include "section.hpp"
#include <QFileInfo>
#include <QSet>

SectionBaseItem::SectionBaseItem(QString path)
  : m_path(std::move(path))
{}

QString SectionBaseItem::title() const {
  return QFileInfo{m_path}.fileName().split('.')[0];
}

void SectionBaseItem::setPath(QString path) {
  if (m_path != path) {
    m_path = std::move(path);
  }
}

Node::Node(QString path)
  : SectionBaseItem(std::move(path))
{}

QString Node::extension() const {
  return QFileInfo{m_path}.suffix();
}

void Node::setNextSection(Section* section) {
  if (m_nextSection != section) {
    m_nextSection = section;
  }
}

Section::Section(QString path, QList<Node> nodes, Mode mode, Section* prevSection, QObject* parent)
  : SectionBaseItem(std::move(path)), m_nodes(std::move(nodes)), m_mode(mode), m_prevSection(prevSection), QObject(parent)
{}

bool Section::isLeafSection() const {
  return m_nodes.empty() || m_nodes.first().extension() != "";
}

void Section::setPath(QString path) {
  if (m_path != path) {
    m_path = std::move(path);
    emit pathChanged();
  }
}

void Section::setMode(Mode mode) {
  if (m_mode != mode) {
    m_mode = mode;
    emit modeChanged();
  }
}

void Section::openNode(int index) {
  if (int size = m_nodes.size(); index >= 0 || index < size)
  {
    Node& node = m_nodes[index];

    if (!node.nextSection()) {
      emit openNextSectionRequested(this, &node);
    }

    if (node.nextSection()) {
      emit setCurrentSectionRequested(node.nextSection());
    }
  }
}
