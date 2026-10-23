#include "BreadcrumbsModel.hpp"

BreadcrumbsModel::BreadcrumbsModel(QObject* parent)
  : QObject(parent)
{}

void BreadcrumbsModel::appendSection(Section* section) {
  m_breadcrumbs.append(section);
  emit breadcrumbsChanged();
}

void BreadcrumbsModel::rewindToSection(Section* section) {
  if (m_breadcrumbs.empty()) return;
  int index = m_breadcrumbs.indexOf(section);

  if (index != -1) {
    m_breadcrumbs.resize(index + 1);
    emit breadcrumbsChanged();
  }
}