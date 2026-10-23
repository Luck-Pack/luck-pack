#include "SectionModel.hpp"

SectionModel::SectionModel(QObject* parent) : QObject(parent) {}

void SectionModel::setCurrentSection(Section* section) {
  if (m_currentSection == section) return;

  m_currentSection = section;
  emit currentSectionChanged(m_currentSection);
}