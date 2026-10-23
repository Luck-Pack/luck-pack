#pragma once
#include <QtQml/qqmlregistration.h>
#include <QObject>

class Section;

class SectionBaseItem {
  Q_GADGET
  QML_ELEMENT

public:
  SectionBaseItem() = default;
  SectionBaseItem(QString path);

  QString title() const;
  QString path() const { return m_path; }

  void setPath(QString path);

protected:
  QString m_path{};
};

class Node : public SectionBaseItem {
  Q_GADGET
  QML_ELEMENT
  QML_VALUE_TYPE(node)

public:
  Q_PROPERTY(QString title READ title FINAL)
  Q_PROPERTY(QString path READ path WRITE setPath FINAL)
  Q_PROPERTY(QString extension READ extension FINAL)

  Node() = default;
  Node(QString path);

  QString extension() const;

  Section* nextSection() const { return m_nextSection; }
  void setNextSection(Section* section);

private:
  Section* m_nextSection{nullptr};
};

class Section : public QObject, public SectionBaseItem {
  Q_OBJECT
  QML_ELEMENT
  QML_VALUE_TYPE(section)

public:
  enum class Mode { STRICT, EXPANDED, ACCUMULATIVE };
  Q_ENUM(Mode)

  Q_PROPERTY(QList<Node> nodes READ nodes NOTIFY nodesChanged FINAL)
  Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged FINAL)
  Q_PROPERTY(QString title READ title NOTIFY pathChanged FINAL)
  Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged FINAL)
  Q_PROPERTY(bool isLeafSection READ isLeafSection NOTIFY isLeafSectionChanged FINAL)

  Section(QString path, QList<Node> nodes, Mode mode, Section* prevSection = nullptr, QObject* parent = nullptr);

  Mode mode() const { return m_mode; }
  bool isLeafSection() const;

  const QList<Node>& nodes() { return m_nodes; }

  Section* prevSection() { return m_prevSection; }
  const Section* prevSection() const { return m_prevSection; }

  void setPath(QString path);
  void setMode(Mode mode);

public slots:
  void openNode(int index);

signals:
  void nodesChanged();
  void pathChanged();
  void modeChanged();
  void isLeafSectionChanged();

  void openNextSectionRequested(Section* currentSection, Node* node);
  void setCurrentSectionRequested(Section* section);

private:
  QList<Node> m_nodes{};
  Section* m_prevSection{nullptr};
  Mode m_mode{};
};