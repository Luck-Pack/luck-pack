#pragma once
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "src/ui/components/section/section.hpp"

class BreadcrumbsModel : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

public:
  Q_PROPERTY(QList<Section*> breadcrumbs READ breadcrumbs NOTIFY breadcrumbsChanged FINAL)

  explicit BreadcrumbsModel(QObject* parent = nullptr);

  const QList<Section*>& breadcrumbs() const { return m_breadcrumbs; }

public slots:
  void appendSection(Section* section);
  void rewindToSection(Section* section);

signals:
  void breadcrumbsChanged();

private:
  QList<Section*> m_breadcrumbs{};
};