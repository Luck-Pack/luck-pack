#pragma once
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "src/ui/components/section/section.hpp"

class FileRepository : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(Section* rootSection READ rootSection NOTIFY rootSectionChanged FINAL)

public:
  explicit FileRepository(QObject *parent = nullptr);

  Section* rootSection() const { return m_rootSection.get(); }

public slots:
  void openStorage(const QString& path);
  void openNextSection(Section* currentSection, Node* node);

signals:
  void rootSectionChanged(Section* section);
  void nextSectionOpened();

private:
  std::vector<std::unique_ptr<Section>> m_sections{};
  std::unique_ptr<Section> m_rootSection{};
};