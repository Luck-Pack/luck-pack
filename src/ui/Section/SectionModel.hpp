#pragma once
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "src/ui/components/section/section.hpp"

class SectionModel : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

public:
  Q_PROPERTY(Section* currentSection READ currentSection WRITE setCurrentSection NOTIFY currentSectionChanged FINAL)

  explicit SectionModel(QObject* parent = nullptr);

  Section* currentSection() const { return m_currentSection; }

public slots:
  void setCurrentSection(Section* section);

signals:
  void currentSectionChanged(Section* section);

private:
  Section* m_currentSection{nullptr};
};